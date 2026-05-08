#include <gtest/gtest.h>

#include <boost/asio.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/redis/connection.hpp>

#include <stdexcept>
#include <stdlib.h>
#include <thread>

#include <runtime/reactor/common/helpers.hpp>
#include <runtime/reactor/common/type_system.hpp>
#include <runtime/reactor/distributed/config.hpp>
#include <runtime/reactor/distributed/redis_client.hpp>

using reactor::Pointer;
using reactor::redis::KeyToAttrsMap;
using boost::asio::awaitable;
using boost::asio::use_awaitable;

using HashSet = std::map<std::string, std::string>;

namespace asio = boost::asio;

class RedisClientTest : public testing::Test {
protected:
    asio::io_context ctx;
    asio::executor_work_guard<asio::io_context::executor_type> work_guard;
    std::thread io_thread;

    Pointer<boost::redis::connection> conn;
    Pointer<reactor::redis::RedisClient> client;

    RedisClientTest()
        : work_guard(asio::make_work_guard(ctx))
        , conn(std::make_shared<boost::redis::connection>(ctx.get_executor()))
        , client(std::make_shared<reactor::redis::RedisClient>(conn))
    {}

    void SetUp() override {
        io_thread = std::thread([this]() {
            ctx.run();
        });

        boost::redis::config cfg;
        cfg.addr.host = "127.0.0.1";
        cfg.addr.port = "6379";
        cfg.database_index = 1;

        conn->async_run(cfg, asio::detached);
    }

    void TearDown() override {
        conn->cancel();
        work_guard.reset();
        ctx.stop();

        if (io_thread.joinable())
            io_thread.join();
    }

    asio::awaitable<HashSet> HGetAll(const std::string& key) {
        using asio::use_awaitable;

        boost::redis::request req;
        req.push("HGETALL", key);

        boost::redis::response<std::vector<std::string>> resp;

        boost::system::error_code ec;
        co_await conn->async_exec(req, resp,
            asio::redirect_error(use_awaitable, ec));

        if (ec) {
            co_return HashSet{}; // or throw if you prefer
        }

        std::map<std::string, std::string> result;

        const auto& opt = std::get<0>(resp);
        if (!opt.has_value()) {
            co_return result;
        }

        const auto& arr = *opt;

        for (std::size_t i = 0; i + 1 < arr.size(); i += 2) {
            result[arr[i]] = arr[i + 1];
        }

        co_return result;
    }
};

TEST_F(RedisClientTest, TestCreateChannel) {
    std::promise<KeyToAttrsMap> results;
    auto fut = results.get_future();

    asio::co_spawn(ctx,
        [this, &results]() -> awaitable<void> {
            co_await client->NewChannel("test_create_channel");
            results.set_value(co_await client->GetAttributes({"test_create_channel"}, {"head", "tail"}));
            co_return;
        },
        asio::detached);

    auto key_to_attrs = fut.get();
    ASSERT_EQ(key_to_attrs["test_create_channel"][0], "test_create_channel:node:0");
    ASSERT_EQ(key_to_attrs["test_create_channel"][1], "test_create_channel:node:0");
}

TEST_F(RedisClientTest, TestCreateExecQueue) {
    std::promise<KeyToAttrsMap> results;
    auto fut = results.get_future();

    asio::co_spawn(ctx,
        [this, &results]() -> awaitable<void> {
            co_await client->NewExecQueue("test_exec_queue");
            results.set_value(co_await client->GetAttributes({"test_exec_queue"}, {"head", "tail"}));
            co_return;
        },
        asio::detached);

    auto key_to_attrs = fut.get();
    ASSERT_EQ(key_to_attrs["test_exec_queue"][0], "test_exec_queue:node:1");
    ASSERT_EQ(key_to_attrs["test_exec_queue"][1], "test_exec_queue:node:1");
}

TEST_F(RedisClientTest, TestSendMsg) {
    std::promise<KeyToAttrsMap> channel_results;
    std::promise<KeyToAttrsMap> nodes_results;
    auto channel_fut = channel_results.get_future();
    auto nodes_fut = nodes_results.get_future();

    asio::co_spawn(ctx,
        [this, &channel_results, &nodes_results]() -> awaitable<void> {
            co_await client->NewChannel("test_send_channel");
            co_await client->PushToChannel("test_send_channel", reactor::Object::String("test_payload"));
            auto kta = co_await client->GetAttributes({"test_send_channel"}, {"head", "tail"});
            channel_results.set_value(kta);
            nodes_results.set_value(co_await client->GetAttributes({kta["test_send_channel"][0], kta["test_send_channel"][1]}, {"next", "msg"}));
            co_return;
        },
        asio::detached);

    auto channel_key_to_attrs = channel_fut.get();
    auto head_key = channel_key_to_attrs["test_send_channel"][0];
    auto tail_key = channel_key_to_attrs["test_send_channel"][1];
    ASSERT_NE(head_key, tail_key);

    auto node_key_to_attrs = nodes_fut.get();
    ASSERT_EQ(node_key_to_attrs[head_key][0], tail_key);
    ASSERT_EQ(reactor::Object::Deserialize(node_key_to_attrs[head_key][1]), reactor::Object::String("test_payload"));
    ASSERT_EQ(node_key_to_attrs[tail_key][0], "");
    ASSERT_EQ(node_key_to_attrs[tail_key][1], "");
}

TEST_F(RedisClientTest, ScheduleExecution) {
    std::promise<reactor::Objects> objects_results;
    std::promise<KeyToAttrsMap> channels_results;
    auto objects_fut = objects_results.get_future();
    auto channels_fut = channels_results.get_future();

    asio::co_spawn(ctx,
        [this, &objects_results, &channels_results]() -> awaitable<void> {
            co_await client->NewChannel("test_exec_channel_1");
            co_await client->NewChannel("test_exec_channel_2");
            co_await client->NewExecQueue("test_schedule_exec");
            co_await client->PushToChannel("test_exec_channel_1", reactor::Object::String("test_param_1"));
            co_await client->PushToChannel("test_exec_channel_2", reactor::Object::String("test_param_2"));
            co_await client->PushToChannel("test_exec_channel_2", reactor::Object::String("unused"));
            objects_results.set_value(co_await client->ScheduleExecution("test_schedule_exec", {"test_exec_channel_1", "test_exec_channel_2"}));
            channels_results.set_value(co_await client->GetAttributes({"test_exec_channel_1", "test_exec_channel_2"}, {"head", "tail"}));
            co_return;
        },
        asio::detached);

    auto objects = objects_fut.get();
    ASSERT_EQ(objects[0], reactor::Object::String("test_param_1"));
    ASSERT_EQ(objects[1], reactor::Object::String("test_param_2"));

    auto channel_key_to_attrs = channels_fut.get();
    ASSERT_EQ(channel_key_to_attrs["test_exec_channel_1"][0], channel_key_to_attrs["test_exec_channel_1"][1]);
    ASSERT_NE(channel_key_to_attrs["test_exec_channel_2"][0], channel_key_to_attrs["test_exec_channel_2"][1]);
}

TEST_F(RedisClientTest, Commit) {
    std::promise<KeyToAttrsMap> channels_results;
    std::promise<KeyToAttrsMap> nodes_results;
    auto channels_fut = channels_results.get_future();
    auto nodes_fut = nodes_results.get_future();

    asio::co_spawn(ctx,
        [this, &channels_results, &nodes_results]() -> awaitable<void> {
            co_await client->NewChannel("test_commit_in_channel");
            co_await client->NewChannel("test_commit_out_channel");
            co_await client->NewExecQueue("test_commit_exec");
            co_await client->PushToChannel("test_commit_in_channel", reactor::Object::String("test_param"));
            co_await client->ScheduleExecution("test_commit_exec", {"test_commit_in_channel"});

            std::map<std::string, reactor::Objects> execution_results;
            execution_results["test_commit_out_channel"].push_back(reactor::Object::String("test_result"));
            co_await client->CommitExecution("test_commit_exec", execution_results);

            auto kta = co_await client->GetAttributes({"test_commit_in_channel", "test_commit_out_channel"}, {"head", "tail"});
            channels_results.set_value(kta);
            nodes_results.set_value(co_await client->GetAttributes(
                {kta["test_commit_out_channel"][0], kta["test_commit_out_channel"][1]}, {"next", "msg"}));
            co_return;
        },
        asio::detached);

    auto channel_key_to_attrs = channels_fut.get();
    auto out_head = channel_key_to_attrs["test_commit_out_channel"][0];
    auto out_tail = channel_key_to_attrs["test_commit_out_channel"][1];
    ASSERT_EQ(channel_key_to_attrs["test_commit_in_channel"][0], channel_key_to_attrs["test_commit_in_channel"][1]);
    ASSERT_NE(out_head, out_tail);

    auto node_key_to_attrs = nodes_fut.get();
    ASSERT_EQ(node_key_to_attrs[out_head][0], out_tail);
    ASSERT_EQ(reactor::Object::Deserialize(node_key_to_attrs[out_head][1]), reactor::Object::String("test_result"));
    ASSERT_EQ(node_key_to_attrs[out_tail][0], "");
    ASSERT_EQ(node_key_to_attrs[out_tail][1], "");

}
