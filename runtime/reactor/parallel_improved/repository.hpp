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
#include <runtime/reactor/common/lifecycle.hpp>
#include <runtime/reactor/common/firing.hpp>
#include <runtime/reactor/common/event_emitter.hpp>
#include <runtime/reactor/common/error_handler.hpp>

namespace reactor {

constexpr std::ptrdiff_t max_runner_threads = 8;
constexpr size_t calls_queue_node_size = 4096;
constexpr size_t calls_queue_batch_size = 4;
constexpr size_t calls_queue_batch_threshold = 16;
constexpr size_t semaphore_mult = 64;

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
    mutable std::binary_semaphore lock;

    Objects inputs;
    Objects context;
    Runnable* runnable;

    SchedulledCall();
};

struct CallQueueNode: public Lockable {
    std::atomic_uint64_t next_write_pos;
    std::atomic_uint64_t next_read_pos;

    std::shared_ptr<CallQueueNode> next;
    std::array<SchedulledCall, calls_queue_node_size> calls;

    CallQueueNode();
    std::shared_ptr<CallQueueNode> AllocateNext();
};

struct CallQueueWriteIterator {
    std::shared_ptr<CallQueueNode> node;
    size_t global_offset = 0;

    void ScheduleCall(Objects inputs, Objects context, Runnable* runnable);
    size_t GetLastPos();
};

struct CallQueueReadIterator {
    std::shared_ptr<CallQueueNode> node;
    size_t global_offset = 0;

    std::tuple<SchedulledCall*, size_t> GetNextCall();
    size_t GetLastPos();
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

    void NotifyQueueEmpty() noexcept;
    void NotifyLastReference() noexcept;

    ChannelDataPointer channel_data_;
};

class ImprovedRepository : public Repository, public Lockable {
public:
    ImprovedRepository();
    static ImprovedRepository& GetRepository();
    void RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) override;
    Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, Type payload_type = Type::Unit()) override;
    void Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) override;

    void Shutdown() noexcept;
    void WaitForCompletion() noexcept;
    RepositoryState GetState() const noexcept;
    bool IsRunning() const noexcept;

    void SetEventLogger(Pointer<EventLogger> logger);
    Pointer<EventLogger> GetEventLogger() const;
    Pointer<EventEmitter> GetEventEmitter() const;

    ErrorHandler& GetErrorHandler();
    const ErrorHandler& GetErrorHandler() const;

private:
    using QueuesMap = std::map<uint64_t, QueuePointer>;

    void RunRoutine(size_t thread_index, std::shared_ptr<CallQueueNode> node) noexcept;
    void ScheduleCall(Objects inputs, Objects context, uint64_t runnable_id) noexcept;

    std::atomic_uint64_t next_id;
    std::atomic_uint64_t next_join_case_id_;

    std::atomic<bool> is_complete;
    std::unordered_map<uint64_t, Runnable*> runnable_map_;

    RepositoryLifecycle lifecycle_;
    Pointer<EventEmitter> event_emitter_;
    ErrorHandler error_handler_;

    friend struct ChannelReference;
};

}  // namespace reactor
