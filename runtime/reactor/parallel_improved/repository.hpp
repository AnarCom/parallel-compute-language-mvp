#pragma once

#include <atomic>
#include <deque>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <semaphore>

#include <runtime/reactor/common/helpers.hpp>
#include <runtime/reactor/common/interface.hpp>

namespace reactor {

constexpr std::ptrdiff_t max_runner_threads = 1;
constexpr std::ptrdiff_t max_schedulled_calls = 1024;

class Lockable {
public:
    void Lock() const noexcept;
    void Unlock() const noexcept;
    std::lock_guard<std::mutex> Guard() const noexcept;

private:
    mutable std::mutex lock_;
};

struct MessageQueue : public Lockable {
    std::queue<Object> values;

    void Push(const Object& value);
    [[nodiscard]] bool Empty() const;
    [[nodiscard]] Object PopFront();
};

using QueuePointer = Pointer<MessageQueue>;
using IDs = std::vector<uint64_t>;

class ImprovedRepository;
struct ChannelData;
struct ChannelReference;

using ChannelDataPointer = std::shared_ptr<ChannelData>;

struct Reaction : public Lockable {
    Reaction(std::vector<ChannelDataPointer> inputs, Objects context, uint64_t runnable_id) noexcept;

    std::vector<ChannelDataPointer> inputs_;
    Objects context_;
    uint64_t runnable_id_;
};

class ReactionPointer {
public:
    explicit ReactionPointer(std::shared_ptr<Reaction> reaction, size_t index) noexcept;
    std::shared_ptr<Reaction> operator->() noexcept;
    size_t index() const noexcept;

private:
    std::shared_ptr<Reaction> reaction_;
    const size_t index_;
};

using Reactions = std::list<ReactionPointer>;

struct SchedulledCall {
    Objects inputs;
    Objects context;
    Runnable* runnable;
};

struct ChannelData : public Lockable {
    ChannelData(uint64_t id) noexcept;

    uint64_t id_;
    MessageQueue queue_;
    Reactions dependent_reactions_;
};

struct ChannelReference: public ChannelBase {
    ChannelReference(ChannelMode mode, Type payload_type, uint64_t id) noexcept;
    ~ChannelReference() noexcept;

    void Push(const Object& message) override;
    uint64_t GetID() const noexcept override;

    ChannelDataPointer channel_data_;
};

class ImprovedRepository : public Repository, public Lockable {
public:
    ImprovedRepository();   
    static ImprovedRepository& GetRepository();
    void RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) override;
    Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, Type payload_type = Type::Unit()) override;
    void Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) override;

    std::atomic_uint64_t total_calls;
    std::vector<std::atomic_uint64_t> calls_per_thread;

private:
    using QueuesMap = std::map<uint64_t, QueuePointer>;

    void RunRoutine(size_t thread_index) noexcept;
    void ScheduleCall(Objects inputs, Objects context, uint64_t runnable_id) noexcept;

    std::deque<SchedulledCall> calls;
    std::atomic_uint64_t next_id;

    std::atomic<bool> is_complete;
    std::atomic<std::ptrdiff_t> active_threads;
    std::counting_semaphore<max_schedulled_calls> calls_semaphore;
    std::unordered_map<uint64_t, Runnable*> runnable_map_;

    friend struct ChannelReference;
};

}  // namespace reactor
