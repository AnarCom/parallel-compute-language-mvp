#pragma once

#include <atomic>
#include <deque>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <semaphore>

#include <boost/asio.hpp>

#include <runtime/reactor/common/interface.hpp>

namespace reactor {

constexpr std::ptrdiff_t max_runner_threads = 8;
constexpr std::ptrdiff_t max_schedulled_calls = 128;

using IDs = std::vector<uint64_t>;

class RedisRepository;

struct JoinCase {
    IDs input_ids;
    Objects context;
    uint64_t runnable_id;
};

struct SchedulledCall {
    Objects inputs;
    Objects context;
    Runnable* runnable;
};

struct RunResult {
    // TODO: This class contains changes that must be atomically commited
};

class RedisChannel : public ChannelBase {
public:
    RedisChannel(ChannelMode mode, Type payload_type) noexcept;

    void Push(const Object& message) override;
    uint64_t GetID() const noexcept override;

private:
    friend RedisRepository;
};

class RedisRepository : public Repository {
public:
    static RedisRepository& GetRepository();
    void RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) override;
    Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, Type payload_type = Type::Unit()) override;
    void Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) override;

private:
    RedisRepository();
    boost::asio::awaitable<void> RunScheduller();
    boost::asio::awaitable<void> ReceiveJoinCase();
    boost::asio::awaitable<void> RunSchedulledCall();
    RunResult RunByID(uint64_t runnable_id, Objects inputs, Objects context);

    boost::asio::io_context ioc;

    std::list<JoinCase> cases_;
    std::deque<SchedulledCall> calls_;
    std::unordered_map<uint64_t, Runnable*> runnable_map_;

    std::recursive_mutex lock_;
    std::counting_semaphore<max_schedulled_calls> calls_semaphore_;
};

}  // namespace reactor
