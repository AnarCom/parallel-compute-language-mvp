#include "cycle_impl.hpp"

#include "logging.hpp"

#include <iterator>

namespace reactor {

CycleChannel::CycleChannel() noexcept {
    CycleRepository::GetRepository().RegisterChannel(this);
}

CycleCallback::CycleCallback(uint64_t expected_id_, QueuePointer queue_) noexcept: expected_id(expected_id_), queue(queue_) {}

void CycleCallback::OnMessage(uint64_t id, Object message) noexcept {
    debug::runtime_assert(id == expected_id, "received id does not match expected_id");
    queue->push(message);
}

CycleRepository& CycleRepository::GetRepository() {
    static CycleRepository instance;
    return instance;
}

void CycleRepository::RegisterChannel(CycleChannel* channel_raw_ptr) noexcept {
    auto guard = std::lock_guard(this->lock);

    debug::runtime_assert(!channel_raw_ptr->GetID().has_value(), "cannot register channel twice (ID is already set)");
    QueuePointer queue_ptr = std::make_shared<std::queue<Object>>();
    channel_raw_ptr->SetID(this->next_id);
    channel_raw_ptr->SetCallback( std::make_shared<CycleCallback>(this->next_id, queue_ptr) );
    this->queues[this->next_id] = queue_ptr;
    ++(this->next_id);
}

void CycleRepository::RegisterJoinCase(Channels inputs, Channels outputs, Pointer<Runnable> reaction) noexcept {
    auto guard = std::lock_guard(this->lock);

    IDs input_ids;
    input_ids.reserve(inputs.size());
    for (auto& input : inputs) {
        debug::runtime_assert(input.use_count() > 0, "case inputs cannot be null when registering case");
        debug::runtime_assert(input->GetID().has_value(), "case inputs must be registered");
        input_ids.push_back(input->GetID().value());
    }
    for (auto& output : outputs) {
        debug::runtime_assert(output.use_count() > 0, "case outputs cannot be null");
    }
    this->cases.push_back({.input_ids = input_ids, .outputs = outputs, .reaction = reaction});
}

void CycleRepository::CheckCases() noexcept {
    auto guard = std::lock_guard(this->lock);

    auto total_cases = this->cases.size();
    auto current_case = this->cases.begin();
    std::advance(current_case, cycle_offset);
    for (size_t i = 0; i < total_cases; ++i) {
        if (current_case == this->cases.end()) {
            current_case = this->cases.begin();
        }
        bool will_destroy_case = this->CheckCase(*current_case);
        if (will_destroy_case) {
            current_case = this->cases.erase(current_case);
        } else {
            std::advance(current_case, 1);
        }
    }
    CleanUpQueues();
}

bool CycleRepository::CheckCase(JoinCase& current_case) noexcept {
    bool is_ready = std::all_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) { return CheckQueueReadyById(channel_id); }
    );
    bool will_destroy_case = false;
    if (is_ready) {
        Objects objects;
        for (auto& channel_id : current_case.input_ids) {
            auto queue_it = GetQueueById(channel_id);
            objects.push_back(queue_it->second->front());
            queue_it->second->pop();
            
            if (!CheckQueueAliveById(channel_id)) {
                will_destroy_case = true;
            }
        }
        current_case.reaction->Run(objects, current_case.outputs);
    }
    return will_destroy_case;
}

void CycleRepository::CleanUpQueues() noexcept {
    auto queue_it = queues.begin();
    while (queue_it != queues.end()) {
        if (!CheckQueueAliveById(queue_it->first)) {
            queue_it = queues.erase(queue_it);
        } else {
            ++queue_it;
        }
    }
}

bool CycleRepository::CheckQueueAliveById(uint64_t channel_id) noexcept {
    auto queue_it = queues.find(channel_id);
    debug::runtime_assert(queue_it == queues.end() || queue_it->second.use_count() > 0, "If queue is found it cannot be null");
    // Check that queue is pointed to by at least one callback (in addition to queue)
    return queue_it != queues.end() && (queue_it->second.use_count() > 1 || !queue_it->second->empty());
}

bool CycleRepository::CheckQueueReadyById(uint64_t channel_id) noexcept {
    auto queue_it = queues.find(channel_id);
    debug::runtime_assert(queue_it == queues.end() || queue_it->second.use_count() > 0, "If queue is found it cannot be null");
    return queue_it != queues.end() && !queue_it->second->empty();
}

CycleRepository::QueuesMap::iterator CycleRepository::GetQueueById(uint64_t channel_id) noexcept {
    auto queue_it = queues.find(channel_id);
    debug::runtime_assert(queue_it != queues.end(), "registered channel has no queue");
    debug::runtime_assert(queue_it->second.use_count() > 0, "registered channel has empty queue");
    return queue_it;
}

CycleRepository::CycleRepository(): cases(), queues(), next_id(0), cycle_offset(0) {}
    

}  // namespace reactor
