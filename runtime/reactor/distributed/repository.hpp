#pragma once

#include <atomic>
#include <deque>
#include <future>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <semaphore>
#include <unordered_map>

#include <boost/asio.hpp>

#include <runtime/reactor/common/interface.hpp>

namespace boost::redis {
class connection;
}

namespace reactor {

namespace redis {
class RedisClient;
}

constexpr std::ptrdiff_t max_runner_threads = 8;
constexpr std::ptrdiff_t max_schedulled_calls = 128;

using IDs = std::vector<uint64_t>;

class RedisRepository;

struct JoinCase {
    IDs input_ids;
    Objects context;
    uint64_t runnable_id;
};

struct DistributedReaction {
    IDs input_ids;
    Objects context;
    uint64_t runnable_id;
};

using DistributedReactions = std::vector<DistributedReaction>;

struct ReactionAttributes {
    uint64_t reaction_id;
    std::string head;
    std::string tail;
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
    RedisChannel(ChannelMode mode, Type payload_type, uint64_t id) noexcept;

    void Push(const Object& message) override;
    uint64_t GetID() const noexcept override;

private:
    uint64_t id_;

    friend RedisRepository;
};

class RedisRepository : public Repository {
public:
    static RedisRepository& GetRepository();
    void RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) override;
    Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, Type payload_type = Type::Unit()) override;
    void Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) override;
    void Stop() noexcept;
    void PushMessage(uint64_t channel_id, const Object& message);

private:
    RedisRepository();
    boost::asio::awaitable<void> ReceiveChannelNotifications(Pointer<std::promise<void>> subscribed);
    boost::asio::awaitable<void> ReceiveReactionNotifications();
    boost::asio::awaitable<void> ReceiveJoinCase();
    boost::asio::awaitable<void> RunSchedulledCall();
    RunResult RunByID(uint64_t runnable_id, Objects inputs, Objects context);
    boost::asio::awaitable<void> TryScheduleReaction(const DistributedReaction& reaction);
    DistributedReactions GetReactionsDependentOnChannel(uint64_t channel_id);
    bool IsReactionAssignedToThisProcess(uint64_t reaction_id) const;

    void ScheduleCall(Objects inputs, Objects context, uint64_t runnable_id) noexcept;
    std::string ChannelKey(uint64_t channel_id) const;
    std::string ExecQueueKey(uint64_t runnable_id) const;

    boost::asio::io_context ioc;
    Pointer<boost::redis::connection> conn_;
    Pointer<boost::redis::connection> command_conn_;
    Pointer<redis::RedisClient> redis_client_;
    Pointer<boost::redis::connection> reaction_conn_;
    Pointer<boost::redis::connection> reaction_command_conn_;
    Pointer<redis::RedisClient> reaction_redis_client_;

    std::list<JoinCase> cases_;
    std::unordered_map<uint64_t, DistributedReactions> dependent_reactions_;
    std::deque<ReactionAttributes> reaction_attributes_;
    std::deque<SchedulledCall> calls_;
    std::unordered_map<uint64_t, Runnable*> runnable_map_;
    std::atomic_uint64_t next_id_;
    std::atomic<bool> is_complete_;

    std::recursive_mutex lock_;
    std::counting_semaphore<max_schedulled_calls> calls_semaphore_;
};

}  // namespace reactor
