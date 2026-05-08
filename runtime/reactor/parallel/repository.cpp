#include "repository.hpp"

#include <algorithm>
// #include <format>
#include <iterator>
#include <thread>
#include <vector>

#include <logging.hpp>

namespace reactor {

void MessageQueue::Push(const Object& value) {
    auto guard = std::lock_guard(lock);
    values.push(value);
}

bool MessageQueue::Empty() const {
    auto guard = std::lock_guard(lock);
    return values.empty();
}

Object MessageQueue::PopFront() {
    auto guard = std::lock_guard(lock);
    debug::runtime_assert(!values.empty(), "cannot pop from empty queue");
    auto value = values.front();
    values.pop();
    return value;
}

CycleChannel::CycleChannel(ChannelMode mode, Type payload_type) noexcept
    : ChannelBase(mode, std::move(payload_type)) {}

void CycleChannel::Push(const Object& message) {
    auto maybe_id = GetID();
    auto maybe_callback = GetCallback();
    debug::runtime_assert(maybe_id.has_value(), "channel is not registered in repository");
    debug::runtime_assert(bool(maybe_callback), "channel callback is not installed");
    // debug::runtime_assert(Accepts(message), std::format(
    //     "message of type '{}' cannot be pushed into channel '{}'",
    //     message.GetType().ToString(), GetType().ToString()));
    maybe_callback->OnMessage(maybe_id.value(), message);
}

Maybe<uint64_t> CycleChannel::GetID() const noexcept {
    return id;
}

void CycleChannel::SetID(uint64_t channel_id) noexcept {
    id = channel_id;
}

void CycleChannel::SetCallback(Pointer<Callback> new_callback) noexcept {
    callback = std::move(new_callback);
}

Pointer<Callback> CycleChannel::GetCallback() const noexcept {
    return callback;
}

Callback::Callback(uint64_t expected_id_, QueuePointer queue_) noexcept
    : expected_id(expected_id_), queue(std::move(queue_)) {}

void Callback::OnMessage(uint64_t id, const Object& message) noexcept {
    debug::runtime_assert(id == expected_id, "received id does not match expected channel id");
    queue->Push(message);
}

CycleRepository& CycleRepository::GetRepository() {
    static CycleRepository instance;
    return instance;
}

void CycleRepository::RegisterJoinCase(Channels inputs, Channels outputs, Pointer<RunnableOrLambda> reaction) {
    auto guard = std::lock_guard(lock);

    IDs input_ids;
    input_ids.reserve(inputs.size());
    for (const auto& input : inputs) {
        debug::runtime_assert(input.use_count() > 0, "case inputs cannot be null when registering case");
        debug::runtime_assert(input->GetID().has_value(), "case inputs must be registered");
        input_ids.push_back(input->GetID().value());
    }
    for (const auto& output : outputs) {
        debug::runtime_assert(output.use_count() > 0, "case outputs cannot be null");
    }
    debug::runtime_assert(bool(reaction), "join case reaction cannot be null");
    cases.push_back({.input_ids = std::move(input_ids), .outputs = std::move(outputs), .reaction = std::move(reaction)});
}

Pointer<ChannelBase> CycleRepository::NewChannel(ChannelMode mode, Type payload_type) {
    auto guard = std::lock_guard(lock);

    auto channel = std::make_shared<CycleChannel>(mode, std::move(payload_type));

    debug::runtime_assert(!channel->GetID().has_value(), "cannot register channel twice (ID is already set)");
    QueuePointer queue_ptr = std::make_shared<MessageQueue>();
    channel->SetID(next_id);
    channel->SetCallback(std::make_shared<Callback>(next_id, queue_ptr));
    queues[next_id] = std::move(queue_ptr);
    ++next_id;

    return channel;
}

void CycleRepository::Run(Pointer<RunnableOrLambda> entrypoint) {
    debug::runtime_assert(bool(entrypoint), "repository entrypoint cannot be null");

    is_complete.store(false);
    cycle_offset = 0;

    std::vector<std::thread> runner_threads;
    runner_threads.reserve(max_runner_threads);

    {
        auto guard = std::lock_guard(lock);
        for (auto i = 0; i < max_runner_threads; ++i) {
            runner_threads.emplace_back(std::bind(&CycleRepository::RunRoutine, this));
        }

        calls.push_back({Objects{}, std::move(entrypoint)});
        calls_semaphore.release();
    }

    while (CheckCases()) {
    }

    // debug::runtime_assert(cases.empty(), std::format("cases not empty: found {}", cases.size()));
    // debug::runtime_assert(calls.empty(), std::format("calls not empty: found {}", calls.size()));

    is_complete.store(true);
    for (auto i = 0; i < max_runner_threads; ++i) {
        calls_semaphore.release();
    }
    for (auto& runner_thread : runner_threads) {
        runner_thread.join();
    }
}

CycleRepository::CycleRepository()
    : cases(), calls(), queues(), cycle_offset(0), next_id(0), is_complete(false), active_threads(0), lock(), calls_semaphore(0) {}

void CycleRepository::RunRoutine() noexcept {
    while (true) {
        calls_semaphore.acquire();
        if (is_complete.load()) {
            return;
        }

        SchedulledCall call;
        {
            auto guard = std::lock_guard(lock);
            debug::runtime_assert(!calls.empty(), "scheduled routine queue is empty");
            call = std::move(calls.front());
            calls.pop_front();
            ++active_threads;
        }
        call.callee->operator()(call.inputs);
        --active_threads;
    }
}

bool CycleRepository::CheckCases() noexcept {
    auto guard = std::lock_guard(lock);

    const auto total_cases = cases.size();
    auto current_case = cases.begin();
    std::advance(current_case, std::min(cycle_offset, total_cases));
    for (size_t i = 0; i < total_cases; ++i) {
        if (current_case == cases.end()) {
            current_case = cases.begin();
        }
        bool will_destroy_case = CheckCase(*current_case);
        if (will_destroy_case) {
            current_case = cases.erase(current_case);
        } else {
            std::advance(current_case, 1);
        }
    }
    if (total_cases != 0) {
        cycle_offset = (cycle_offset + 1) % total_cases;
    }
    CleanUpQueues();
    return !(cases.empty() && calls.empty() && active_threads.load() == 0);
}

bool CycleRepository::CheckCase(JoinCase& current_case) noexcept {
    bool is_ready = std::all_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) { return CheckQueueReadyById(channel_id); });
    bool will_destroy_case = std::any_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) { return !CheckQueueAliveById(channel_id); });

    if (is_ready && !will_destroy_case) {
        Objects inputs;
        inputs.reserve(current_case.input_ids.size());
        for (const auto& channel_id : current_case.input_ids) {
            auto queue_it = GetQueueById(channel_id);
            inputs.push_back(queue_it->second->PopFront());
            if (!CheckQueueAliveById(channel_id)) {
                will_destroy_case = true;
            }
        }
        calls.push_back({std::move(inputs), current_case.reaction});
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
    return queue_it != queues.end() && (queue_it->second.use_count() > 1 || !queue_it->second->Empty());
}

bool CycleRepository::CheckQueueReadyById(uint64_t channel_id) noexcept {
    auto queue_it = queues.find(channel_id);
    debug::runtime_assert(queue_it == queues.end() || queue_it->second.use_count() > 0, "If queue is found it cannot be null");
    return queue_it != queues.end() && !queue_it->second->Empty();
}

CycleRepository::QueuesMap::iterator CycleRepository::GetQueueById(uint64_t channel_id) noexcept {
    auto queue_it = queues.find(channel_id);
    debug::runtime_assert(queue_it != queues.end(), "registered channel has no queue");
    debug::runtime_assert(queue_it->second.use_count() > 0, "registered channel has empty queue");
    return queue_it;
}

}  // namespace reactor
