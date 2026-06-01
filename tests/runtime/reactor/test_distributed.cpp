#include <gtest/gtest.h>

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/redis/connection.hpp>

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <future>
#include <optional>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

#include <sys/wait.h>
#include <unistd.h>

#include <runtime/reactor/distributed/repository.hpp>
#include <runtime/reactor/distributed/redis_client.hpp>

namespace {

std::string g_executable_path;

class CallbackRunnable : public reactor::Runnable {
public:
    explicit CallbackRunnable(std::promise<void>& called) noexcept
        : called_(called) {}

    CallbackRunnable(std::promise<void>& called, std::string marker_path) noexcept
        : called_(called), marker_path_(std::move(marker_path)) {}

    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        EXPECT_TRUE(inputs.empty());
        EXPECT_TRUE(context.empty());
        if (!marker_path_.empty()) {
            auto marker = std::ofstream(marker_path_, std::ios::app);
            marker << "called\n";
        }
        called_.set_value();
        reactor::RedisRepository::GetRepository().Stop();
    }

    uint64_t GetID() const noexcept override {
        return 0;
    }

private:
    std::promise<void>& called_;
    std::string marker_path_;
};

class DependentRunnable : public reactor::Runnable {
public:
    explicit DependentRunnable(std::promise<void>& called) noexcept
        : called_(called) {}

    DependentRunnable(std::promise<void>& called, std::string marker_path) noexcept
        : called_(called), marker_path_(std::move(marker_path)) {}

    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        EXPECT_TRUE(context.empty());
        ASSERT_EQ(inputs.size(), 1u);
        EXPECT_EQ(inputs[0], reactor::Object::String("payload"));
        if (!marker_path_.empty()) {
            auto marker = std::ofstream(marker_path_, std::ios::app);
            marker << "called\n";
        }
        called_.set_value();
        reactor::RedisRepository::GetRepository().Stop();
    }

    uint64_t GetID() const noexcept override {
        return 1;
    }

private:
    std::promise<void>& called_;
    std::string marker_path_;
};

class MainRegistersReaction : public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        EXPECT_TRUE(inputs.empty());
        EXPECT_TRUE(context.empty());

        auto channel = reactor::RedisRepository::GetRepository().NewChannel(
            reactor::ChannelMode::Async,
            reactor::Type::String());
        reactor::RedisRepository::GetRepository().RegisterJoinCase({channel}, {}, 1);
        channel->Push(reactor::Object::String("payload"));
    }

    uint64_t GetID() const noexcept override {
        return 0;
    }
};

class CrashAfterBarrier : public reactor::Runnable {
public:
    explicit CrashAfterBarrier(std::string crash_marker_path) noexcept
        : crash_marker_path_(std::move(crash_marker_path)) {}

    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        EXPECT_TRUE(inputs.empty());
        EXPECT_TRUE(context.empty());

        auto marker = std::ofstream(crash_marker_path_, std::ios::app);
        marker << "crashed\n";
        marker.close();
        std::_Exit(0);
    }

    uint64_t GetID() const noexcept override {
        return 0;
    }

private:
    std::string crash_marker_path_;
};

void ConfigureDistributedTestEnv(uint64_t programs_count, uint64_t node_id, uint64_t redis_db) {
    setenv("REDIS_HOST", "127.0.0.1", 1);
    setenv("REDIS_PORT", "6379", 1);
    setenv("REDIS_USER", "default", 1);
    setenv("REDIS_PASSWORD", "", 1);
    setenv("REDIS_DB", std::to_string(redis_db).c_str(), 1);
    setenv("PROGRAMS_COUNT", std::to_string(programs_count).c_str(), 1);
    setenv("NODE_ID", std::to_string(node_id).c_str(), 1);
}

boost::redis::config MakeRedisTestConfig(uint64_t redis_db) {
    boost::redis::config config;
    config.addr.host = "127.0.0.1";
    config.addr.port = "6379";
    config.database_index = static_cast<int>(redis_db);
    return config;
}

void FlushRedisDB(uint64_t redis_db) {
    boost::asio::io_context ioc;
    auto conn = std::make_shared<boost::redis::connection>(ioc.get_executor());
    auto result = std::promise<void>{};
    auto done = result.get_future();

    conn->async_run(MakeRedisTestConfig(redis_db), boost::asio::detached);
    boost::asio::co_spawn(
        ioc.get_executor(),
        [conn, &result]() -> boost::asio::awaitable<void> {
            boost::redis::request req;
            req.push("FLUSHDB");
            boost::redis::response<std::string> resp;
            co_await conn->async_exec(req, resp);
            result.set_value();
            conn->cancel();
            co_return;
        },
        boost::asio::detached);

    ioc.run();
    done.get();
}

template <typename Operation>
void RunRedisTestOperation(uint64_t redis_db, Operation&& operation) {
    boost::asio::io_context ioc;
    auto conn = std::make_shared<boost::redis::connection>(ioc.get_executor());
    auto client = std::make_shared<reactor::redis::RedisClient>(conn);
    auto result = std::promise<void>{};
    auto done = result.get_future();

    conn->async_run(MakeRedisTestConfig(redis_db), boost::asio::detached);
    boost::asio::co_spawn(
        ioc.get_executor(),
        [conn, client, operation = std::forward<Operation>(operation), &result]() mutable -> boost::asio::awaitable<void> {
            try {
                co_await operation(*client);
                result.set_value();
            } catch (...) {
                result.set_exception(std::current_exception());
            }
            conn->cancel();
            co_return;
        },
        boost::asio::detached);

    ioc.run();
    done.get();
}

void CreateReadyFaultReaction(uint64_t redis_db) {
    RunRedisTestOperation(redis_db, [](reactor::redis::RedisClient& client) -> boost::asio::awaitable<void> {
        co_await client.NewChannel("0");
        co_await client.RegisterReaction("1", "exec:1", {"0"}, {});
        co_await client.PushToChannel("0", reactor::Object::String("payload"));
        co_return;
    });
}

std::optional<std::string> GetRedisString(uint64_t redis_db, const std::string& key) {
    boost::asio::io_context ioc;
    auto conn = std::make_shared<boost::redis::connection>(ioc.get_executor());
    auto result = std::promise<std::optional<std::string>>{};
    auto done = result.get_future();

    conn->async_run(MakeRedisTestConfig(redis_db), boost::asio::detached);
    boost::asio::co_spawn(
        ioc.get_executor(),
        [conn, key, &result]() -> boost::asio::awaitable<void> {
            boost::redis::request req;
            req.push("GET", key);
            boost::redis::response<std::string> resp;
            boost::system::error_code ec;
            co_await conn->async_exec(
                req,
                resp,
                boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            if (ec || !std::get<0>(resp).has_value()) {
                result.set_value(std::nullopt);
            } else {
                result.set_value(std::get<0>(resp).value());
            }
            conn->cancel();
            co_return;
        },
        boost::asio::detached);

    ioc.run();
    return done.get();
}

void WaitForRedisString(uint64_t redis_db, const std::string& key, const std::string& expected) {
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (std::chrono::steady_clock::now() < deadline) {
        if (GetRedisString(redis_db, key) == expected) {
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    FAIL() << "Timed out waiting for Redis key " << key << " to become " << expected;
}

pid_t SpawnDistributedChild(
    uint64_t node_id,
    uint64_t redis_db,
    const std::filesystem::path& marker_path,
    const std::string& mode = "normal",
    const std::filesystem::path& crash_marker_path = {}) {
    const auto pid = fork();
    if (pid == 0) {
        ConfigureDistributedTestEnv(2, node_id, redis_db);
        setenv("DISTRIBUTED_REPOSITORY_CHILD", "1", 1);
        setenv("DISTRIBUTED_REPOSITORY_CHILD_MODE", mode.c_str(), 1);
        setenv("DISTRIBUTED_REPOSITORY_MARKER", marker_path.c_str(), 1);
        if (!crash_marker_path.empty()) {
            setenv("DISTRIBUTED_REPOSITORY_CRASH_MARKER", crash_marker_path.c_str(), 1);
        }
        execl(
            g_executable_path.c_str(),
            g_executable_path.c_str(),
            "--gtest_filter=DistributedRepository.MultiProcessChildRunsRepository",
            "--gtest_brief=1",
            nullptr);
        _exit(127);
    }
    return pid;
}

pid_t SpawnSingleProcessChild(const std::string& mode, const std::filesystem::path& marker_path) {
    const auto pid = fork();
    if (pid == 0) {
        ConfigureDistributedTestEnv(1, 0, 1);
        setenv("DISTRIBUTED_REPOSITORY_SINGLE_CHILD", mode.c_str(), 1);
        setenv("DISTRIBUTED_REPOSITORY_MARKER", marker_path.c_str(), 1);
        execl(
            g_executable_path.c_str(),
            g_executable_path.c_str(),
            "--gtest_filter=DistributedRepository.SingleProcessChildRunsRepository",
            "--gtest_brief=1",
            nullptr);
        _exit(127);
    }
    return pid;
}

void StopChild(pid_t pid) {
    int status = 0;
    const auto wait_result = waitpid(pid, &status, WNOHANG);
    if (wait_result == pid || wait_result == -1) {
        return;
    }

    kill(pid, SIGTERM);
    waitpid(pid, &status, 0);
}

std::size_t CountMarkerLines(const std::filesystem::path& marker_path) {
    auto marker = std::ifstream(marker_path);
    std::size_t lines = 0;
    std::string line;
    while (std::getline(marker, line)) {
        ++lines;
    }
    return lines;
}

std::size_t WaitForAtLeastOneMarkerLine(const std::filesystem::path& marker_path) {
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    auto executions = CountMarkerLines(marker_path);
    while (executions == 0 && std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
        executions = CountMarkerLines(marker_path);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    return CountMarkerLines(marker_path);
}

bool WaitForMarkerLine(const std::filesystem::path& marker_path) {
    return WaitForAtLeastOneMarkerLine(marker_path) != 0;
}

std::filesystem::path MakeMarkerPath(std::string label) {
    return std::filesystem::temp_directory_path() /
        ("gojo-distributed-" + std::move(label) + "-" + std::to_string(getpid()) + ".txt");
}

} // namespace

TEST(DistributedRepository, SingleProcessStartsInitialReaction) {
    FlushRedisDB(1);
    const auto marker_path = MakeMarkerPath("initial");
    std::filesystem::remove(marker_path);

    const auto child = SpawnSingleProcessChild("initial", marker_path);
    ASSERT_GT(child, 0);

    EXPECT_EQ(WaitForAtLeastOneMarkerLine(marker_path), 1u);
    StopChild(child);
    std::filesystem::remove(marker_path);
}

TEST(DistributedRepository, SingleProcessRunsReactionRegisteredByMainReaction) {
    FlushRedisDB(1);
    const auto marker_path = MakeMarkerPath("dependent");
    std::filesystem::remove(marker_path);

    const auto child = SpawnSingleProcessChild("dependent", marker_path);
    ASSERT_GT(child, 0);

    EXPECT_EQ(WaitForAtLeastOneMarkerLine(marker_path), 1u);
    StopChild(child);
    std::filesystem::remove(marker_path);
}

TEST(DistributedRepository, SingleProcessChildRunsRepository) {
    const auto* child_mode = std::getenv("DISTRIBUTED_REPOSITORY_SINGLE_CHILD");
    if (child_mode == nullptr) {
        GTEST_SKIP() << "child entrypoint for single-process distributed repository tests";
    }

    const auto mode = std::string(child_mode);
    const auto* marker_path = std::getenv("DISTRIBUTED_REPOSITORY_MARKER");
    ASSERT_NE(marker_path, nullptr);

    if (mode == "initial") {
        std::promise<void> callback_called;
        auto callback_future = callback_called.get_future();
        auto runnable = CallbackRunnable(callback_called, marker_path);

        std::unordered_map<uint64_t, reactor::Runnable*> runnable_map;
        runnable_map.emplace(0, &runnable);

        auto run_thread = std::thread([&]() {
            reactor::RedisRepository::GetRepository().Run(0, std::move(runnable_map));
        });

        const auto status = callback_future.wait_for(std::chrono::seconds(5));
        if (status != std::future_status::ready) {
            reactor::RedisRepository::GetRepository().Stop();
        }

        if (run_thread.joinable()) {
            run_thread.join();
        }

        ASSERT_EQ(status, std::future_status::ready);
        return;
    }

    std::promise<void> dependent_called;
    auto dependent_future = dependent_called.get_future();
    auto main = MainRegistersReaction();
    auto dependent = DependentRunnable(dependent_called, marker_path);

    std::unordered_map<uint64_t, reactor::Runnable*> runnable_map;
    runnable_map.emplace(0, &main);
    runnable_map.emplace(1, &dependent);

    auto run_thread = std::thread([&]() {
        reactor::RedisRepository::GetRepository().Run(0, std::move(runnable_map));
    });

    const auto status = dependent_future.wait_for(std::chrono::seconds(5));
    if (status != std::future_status::ready) {
        reactor::RedisRepository::GetRepository().Stop();
    }

    if (run_thread.joinable()) {
        run_thread.join();
    }

    ASSERT_EQ(status, std::future_status::ready);
}

TEST(DistributedRepository, MultiProcessChildRunsRepository) {
    if (std::getenv("DISTRIBUTED_REPOSITORY_CHILD") == nullptr) {
        GTEST_SKIP() << "child entrypoint for MultiProcessRunsReactionOnce";
    }

    const auto* marker_path = std::getenv("DISTRIBUTED_REPOSITORY_MARKER");
    ASSERT_NE(marker_path, nullptr);
    const auto* mode_env = std::getenv("DISTRIBUTED_REPOSITORY_CHILD_MODE");
    const auto mode = mode_env == nullptr ? std::string("normal") : std::string(mode_env);
    const auto* crash_marker_path = std::getenv("DISTRIBUTED_REPOSITORY_CRASH_MARKER");

    std::promise<void> dependent_called;
    auto dependent_future = dependent_called.get_future();
    auto main = MainRegistersReaction();
    auto crashing_main = CrashAfterBarrier(crash_marker_path == nullptr ? "" : crash_marker_path);
    auto dependent = DependentRunnable(dependent_called, marker_path);

    std::unordered_map<uint64_t, reactor::Runnable*> runnable_map;
    runnable_map.emplace(0, mode == "fault_crasher" ? static_cast<reactor::Runnable*>(&crashing_main) : static_cast<reactor::Runnable*>(&main));
    runnable_map.emplace(1, &dependent);

    auto run_thread = std::thread([&]() {
        reactor::RedisRepository::GetRepository().Run(0, std::move(runnable_map));
    });

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    while (
        dependent_future.wait_for(std::chrono::milliseconds(50)) != std::future_status::ready &&
        std::chrono::steady_clock::now() < deadline &&
        CountMarkerLines(marker_path) == 0) {}

    reactor::RedisRepository::GetRepository().Stop();
    if (run_thread.joinable()) {
        run_thread.join();
    }
}

TEST(DistributedRepository, MultiProcessRunsReactionOnce) {
    constexpr auto redis_db = 2u;
    FlushRedisDB(redis_db);

    const auto marker_path = MakeMarkerPath("reaction");
    std::filesystem::remove(marker_path);

    const auto first_child = SpawnDistributedChild(0, redis_db, marker_path);
    ASSERT_GT(first_child, 0);
    WaitForRedisString(redis_db, "gojo:barrier:counter", "1");
    const auto second_child = SpawnDistributedChild(1, redis_db, marker_path);
    ASSERT_GT(second_child, 0);

    auto executions = WaitForAtLeastOneMarkerLine(marker_path);

    StopChild(first_child);
    StopChild(second_child);

    EXPECT_EQ(executions, 1u);

    std::filesystem::remove(marker_path);
}

TEST(DistributedRepository, MultiProcessTakesOverDeadProcessReactionOnce) {
    constexpr auto redis_db = 3u;
    FlushRedisDB(redis_db);

    const auto execution_marker_path = MakeMarkerPath("fault-execution");
    const auto crash_marker_path = MakeMarkerPath("fault-crash");
    std::filesystem::remove(execution_marker_path);
    std::filesystem::remove(crash_marker_path);
    CreateReadyFaultReaction(redis_db);

    const auto survivor_child = SpawnDistributedChild(0, redis_db, execution_marker_path, "fault_survivor");
    ASSERT_GT(survivor_child, 0);
    WaitForRedisString(redis_db, "gojo:barrier:counter", "1");

    const auto crashing_child = SpawnDistributedChild(
        1,
        redis_db,
        execution_marker_path,
        "fault_crasher",
        crash_marker_path);
    ASSERT_GT(crashing_child, 0);

    ASSERT_TRUE(WaitForMarkerLine(crash_marker_path));
    EXPECT_EQ(WaitForAtLeastOneMarkerLine(execution_marker_path), 1u);

    StopChild(survivor_child);
    StopChild(crashing_child);

    std::filesystem::remove(execution_marker_path);
    std::filesystem::remove(crash_marker_path);
}

int main(int argc, char** argv) {
    if (argc > 0) {
        g_executable_path = argv[0];
    }
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
