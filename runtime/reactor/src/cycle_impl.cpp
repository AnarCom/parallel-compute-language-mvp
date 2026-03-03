#include "cycle_impl.hpp"

#include <iterator>
#include <thread>
#include <vector>

#include "logging.hpp"

namespace reactor {

// CycleChannel public methods

CycleChannel::CycleChannel() noexcept {}

void CycleChannel::Push(Object message) {
    auto maybe_id = this->GetID();
    auto maybe_callback = this->GetCallback();
    if (maybe_id.has_value() && bool(maybe_callback)) {
        maybe_callback->OnMessage(maybe_id.value(), message);
    }
}

Maybe<uint64_t> CycleChannel::GetID() const noexcept {
    return this->id;
}

// CycleChannel private methods

void CycleChannel::SetID(uint64_t id) noexcept {
    this->id = id;
}

void CycleChannel::SetCallback(Pointer<Callback> callback) noexcept {
    this->callback = callback;
}

Pointer<Callback> CycleChannel::GetCallback() const noexcept {
    return this->callback;
}

// Callback methods

Callback::Callback(uint64_t expected_id_, QueuePointer queue_) noexcept: expected_id(expected_id_), queue(queue_) {}

void Callback::OnMessage(uint64_t id, Object message) noexcept {
    debug::runtime_assert(id == expected_id, "received id does not match expected_id");
    queue->push(message);
}

// CycleRepository public methods

CycleRepository& CycleRepository::GetRepository() {
    static CycleRepository instance;
    return instance;
}

void CycleRepository::RegisterJoinCase(Channels inputs, Channels outputs, Pointer<RunnableOrLambda> reaction) {
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

Pointer<ChannelBase> CycleRepository::NewChannel() {
    auto guard = std::lock_guard(this->lock);

    auto channel = std::make_shared<CycleChannel>();

    debug::runtime_assert(!channel->GetID().has_value(), "cannot register channel twice (ID is already set)");
    QueuePointer queue_ptr = std::make_shared<std::queue<Object>>();
    channel->SetID(this->next_id);
    channel->SetCallback( std::make_shared<Callback>(this->next_id, queue_ptr) );
    this->queues[this->next_id] = queue_ptr;
    ++(this->next_id);

    return channel;
}

void CycleRepository::Run(Pointer<RunnableOrLambda> entrypoint) {
    std::vector<std::thread> runner_threads;
    runner_threads.reserve(max_runner_threads);

    {
        auto guard = std::lock_guard(this->lock);
        for (auto i = 0; i < max_runner_threads; ++i) {
            runner_threads.emplace_back(std::bind(&CycleRepository::RunRoutine, this));
        }

        this->calls.emplace_back(Objects{}, entrypoint);
        this->calls_semaphore.release();
    }

    while (this->CheckCases());

    debug::runtime_assert(cases.empty(), std::format("cases not empty: found {}", cases.size()));
    debug::runtime_assert(calls.empty(), std::format("calls not empty: found {}", calls.size()));
    
    this->is_complete.store(true);
    for (auto i = 0; i < max_runner_threads; ++i) {
        this->calls_semaphore.release();
    }
    for (auto& runner_thread : runner_threads) {
        runner_thread.join();
    }
}

CycleRepository::CycleRepository()
: cases()
, calls()
, queues()
, next_id(0)
, cycle_offset(0)
, is_complete(false)
, active_threads(0)
, lock()
, calls_semaphore(0) {}

// CycleRepository private methods

void CycleRepository::RunRoutine() noexcept {
    while (true) {
        calls_semaphore.acquire();
        if (is_complete.load()) {
            return;
        }

        SchedulledCall call;
        {
            auto guard = std::lock_guard(lock);
            call = std::move(calls.front());
            calls.pop_front();
            ++active_threads;
        }
        call.callee->operator()(call.inputs);
        --active_threads;
    }
}

bool CycleRepository::CheckCases() noexcept {
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
    return !(this->cases.empty() && this->calls.empty() && this->active_threads.load() == 0);
}

bool CycleRepository::CheckCase(JoinCase& current_case) noexcept {
    bool is_ready = std::all_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) { return CheckQueueReadyById(channel_id); }
    );
    bool will_destroy_case = std::any_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) { return !CheckQueueAliveById(channel_id); }
    );
    if (is_ready && !will_destroy_case) {
        Objects inputs;
        for (auto& channel_id : current_case.input_ids) {
            auto queue_it = GetQueueById(channel_id);
            inputs.push_back(queue_it->second->front());
            queue_it->second->pop();
            
            if (!CheckQueueAliveById(channel_id)) {
                will_destroy_case = true;
            }
        }
        calls.emplace_back(std::move(inputs), current_case.reaction);
        calls_semaphore.release();
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
    

}  // namespace reactor
