#include "repository.hpp"

#include <runtime/reactor/common/logging.hpp>

namespace reactor {

RedisChannel::RedisChannel(ChannelMode mode, Type payload_type) noexcept: ChannelBase(mode, payload_type) {}

void RedisChannel::Push(const Object& message) {
    // Actually stores messages in RunResult
}
uint64_t RedisChannel::GetID() const noexcept {
    // Should not be called from generated code. Maybe should not even be available in public interface
    return 0;
}

RedisRepository& RedisRepository::GetRepository() {
    static RedisRepository instance;
    return instance;
}

void RedisRepository::RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) {
    // Must actually just store information for new join case in RunResult to be commited later
}

Pointer<ChannelBase> RedisRepository::NewChannel(ChannelMode mode, Type payload_type) {
    // Must actually just store information for new channel in RunResult to be commited later
    return std::make_shared<RedisChannel>(mode, payload_type);
}

void RedisRepository::Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) {
    runnable_map_ = std::move(runnable_map);
    auto main_runnable_it = runnable_map_.find(main_runnable_id);

    debug::runtime_assert(main_runnable_it != runnable_map_.end(), "main runnable not found");
    debug::runtime_assert(main_runnable_it->second != nullptr, "main runnable pointer is nullptr");

    {
        auto guard = std::lock_guard(lock_);
        calls_.push_back({Objects{}, Objects{}, main_runnable_it->second});
        calls_semaphore_.release();
    }

    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::RunScheduller(), boost::asio::detached);
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::ReceiveJoinCase(), boost::asio::detached);
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::RunSchedulledCall(), boost::asio::detached);

    std::vector<std::thread> ths;
    ths.reserve(max_runner_threads);
    for (int i = 0; i != max_runner_threads; ++i) {
        ths.emplace_back([this] { /* Create threadlocal redis client */ ioc.run(); });
    }
    for (auto& th : ths) th.join();
}

RedisRepository::RedisRepository(): calls_semaphore_(0) {}

boost::asio::awaitable<void> RedisRepository::RunScheduller() {
    // Run checks for registered join cases
    // Schedule next iteration of RunScheduller
    co_return;
}

boost::asio::awaitable<void> RedisRepository::ReceiveJoinCase() {
    // Receive join cases for this node from redis pub/sub
    // Register join case
    // Schedule next iteration of ReceiveJoinCase
    // Should not call RegisterJoinCase, as it is an interface function for generated code
    co_return;
}

boost::asio::awaitable<void> RedisRepository::RunSchedulledCall() {
    // Take one SchedulledCall, run it and commit result
    // Should call RunByID
    co_return;
}
RunResult RedisRepository::RunByID(uint64_t runnable_id, Objects inputs, Objects context) {
    RunResult result;
    // Run runnable
    return result;
}

}  // namespace reactor
