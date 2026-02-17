#pragma once

#include <list>
#include <map>
#include <mutex>

#include "interface.hpp"

namespace reactor {

using QueuePointer = Pointer<std::queue<Object>>;
using IDs = std::vector<uint64_t>;

struct JoinCase {
    IDs input_ids;
    Channels outputs;
    Pointer<Runnable> reaction;
};

class CycleChannel: public ChannelBase {
public:
    CycleChannel() noexcept;
};

class CycleCallback: public Callback {
public:
    CycleCallback(uint64_t expected_id_, QueuePointer queue_) noexcept;
    void OnMessage(uint64_t id, Object message) noexcept override;

private:
    const uint64_t expected_id;
    QueuePointer queue;
};

class CycleRepository: public Repository {
public:
    static CycleRepository& GetRepository();
    void RegisterJoinCase(Channels inputs, Channels outputs, Pointer<Runnable> reaction) noexcept override;
    void CheckCases() noexcept;

private:
    using QueuesMap = std::map<uint64_t, QueuePointer>;

    std::list<JoinCase> cases;
    QueuesMap queues;
    size_t cycle_offset;
    uint64_t next_id;

    std::recursive_mutex lock;

    CycleRepository();
    void RegisterChannel(CycleChannel* channel_raw_ptr) noexcept;
    bool CheckCase(JoinCase& current_case) noexcept;
    void CleanUpQueues() noexcept;
    bool CheckQueueAliveById(uint64_t channel_id) noexcept;
    bool CheckQueueReadyById(uint64_t channel_id) noexcept;
    QueuesMap::iterator GetQueueById(uint64_t channel_id) noexcept;

    friend CycleChannel;
};

}  // namespace reactor
