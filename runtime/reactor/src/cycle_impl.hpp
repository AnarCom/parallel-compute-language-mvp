#pragma once

#include <atomic>
#include <deque>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <semaphore>

#include "interface.hpp"

namespace reactor {

constexpr std::ptrdiff_t max_runner_threads = 8;
constexpr std::ptrdiff_t max_schedulled_calls = 1024;

struct MessageQueue {
    mutable std::mutex lock;
    std::queue<Object> values;

    void Push(const Object& value);
    [[nodiscard]] bool Empty() const;
    [[nodiscard]] Object PopFront();
};

using QueuePointer = Pointer<MessageQueue>;
using IDs = std::vector<uint64_t>;

class CycleRepository;

struct JoinCase {
    IDs input_ids;
    Channels outputs;
    Pointer<RunnableOrLambda> reaction;
};

struct SchedulledCall {
    Objects inputs;
    Pointer<RunnableOrLambda> callee;
};

class Callback {
public:
    Callback(uint64_t expected_id_, QueuePointer queue_) noexcept;
    void OnMessage(uint64_t id, const Object& message) noexcept;

private:
    const uint64_t expected_id;
    QueuePointer queue;
};

class CycleChannel : public ChannelBase {
public:
    CycleChannel(ChannelMode mode, Type payload_type) noexcept;

    void Push(const Object& message) override;
    Maybe<uint64_t> GetID() const noexcept override;

private:
    void SetID(uint64_t id) noexcept;
    void SetCallback(Pointer<Callback> callback) noexcept;
    Pointer<Callback> GetCallback() const noexcept;

    Maybe<uint64_t> id;
    Pointer<Callback> callback;

    friend CycleRepository;
};

class CycleRepository : public Repository {
public:
    static CycleRepository& GetRepository();
    void RegisterJoinCase(Channels inputs, Channels outputs, Pointer<RunnableOrLambda> reaction) override;
    Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, Type payload_type = Type::Unit()) override;
    void Run(Pointer<RunnableOrLambda> reaction) override;

private:
    using QueuesMap = std::map<uint64_t, QueuePointer>;

    CycleRepository();

    void RunRoutine() noexcept;
    bool CheckCases() noexcept;
    bool CheckCase(JoinCase& current_case) noexcept;
    void CleanUpQueues() noexcept;
    bool CheckQueueAliveById(uint64_t channel_id) noexcept;
    bool CheckQueueReadyById(uint64_t channel_id) noexcept;
    QueuesMap::iterator GetQueueById(uint64_t channel_id) noexcept;

    std::list<JoinCase> cases;
    std::deque<SchedulledCall> calls;
    QueuesMap queues;
    size_t cycle_offset;
    uint64_t next_id;

    std::atomic<bool> is_complete;
    std::atomic<std::ptrdiff_t> active_threads;
    std::recursive_mutex lock;
    std::counting_semaphore<max_schedulled_calls> calls_semaphore;
};

}  // namespace reactor
