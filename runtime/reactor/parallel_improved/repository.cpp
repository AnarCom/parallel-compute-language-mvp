#include "repository.hpp"

#include <algorithm>
#include <format>
#include <iterator>
#include <runtime/reactor/common/logging.hpp>
#include <thread>
#include <vector>

namespace reactor {

void Lockable::Lock() const noexcept {
    lock_.lock();
}

void Lockable::Unlock() const noexcept {
    lock_.unlock();
}

[[nodiscard]] std::lock_guard<std::mutex> Lockable::Guard() const noexcept {
    return std::lock_guard(lock_);
}

void MessageQueue::Push(const Object& value) {
    values.push(value);
}

bool MessageQueue::Empty() const {
    return values.empty();
}

Object MessageQueue::PopFront() {
    debug::runtime_assert(!values.empty(), "cannot pop from empty queue");
    auto value = std::move(values.front());
    values.pop();
    return value;
}

Reaction::Reaction(std::vector<ChannelDataPointer> inputs, Objects context, uint64_t runnable_id) noexcept
    : inputs_(inputs), context_(std::move(context)), runnable_id_(runnable_id) {}

ReactionPointer::ReactionPointer(std::shared_ptr<Reaction> reaction, size_t index) noexcept
    : reaction_(reaction), index_(index) {}

std::shared_ptr<Reaction> ReactionPointer::operator->() noexcept {
    return reaction_;
}

size_t ReactionPointer::index() const noexcept {
    return index_;
}

ChannelData::ChannelData(uint64_t id) noexcept
    : id_(id), queue_(), dependent_reactions_() {}

ChannelReference::ChannelReference(ChannelMode mode, Type payload_type, uint64_t id) noexcept
    : ChannelBase(mode, std::move(payload_type)), channel_data_(std::make_shared<ChannelData>(id)) {}

ChannelReference::~ChannelReference() noexcept {
}

void ChannelReference::Push(const Object& message) {
    auto channel_lock_guard = channel_data_->Guard();

    {
        auto queue_lock_guard = channel_data_->queue_.Guard();
        auto was_empty = channel_data_->queue_.Empty();
        channel_data_->queue_.Push(message);
        if (!was_empty) {
            return;
        }
    }

    for (auto& reaction : channel_data_->dependent_reactions_) {
        std::for_each(reaction->inputs_.begin(), reaction->inputs_.end(), [](auto input){ input->queue_.Lock(); });

        bool any_empty = false;
        for (auto& input : reaction->inputs_) {
            any_empty = any_empty || input->queue_.Empty();
        }

        if (!any_empty) {
            Objects input_objects;
            input_objects.reserve(reaction->inputs_.size());
            for (auto& input : reaction->inputs_) {
                input_objects.push_back(input->queue_.PopFront());
            }
            ImprovedRepository::GetRepository().ScheduleCall(input_objects, reaction->context_, reaction->runnable_id_);
        }

        std::for_each(reaction->inputs_.begin(), reaction->inputs_.end(), [](auto input){ input->queue_.Unlock(); });

        if (!any_empty) {
            break;
        }
    }
}

uint64_t ChannelReference::GetID() const noexcept {
    return channel_data_->id_;
}

ImprovedRepository& ImprovedRepository::GetRepository() {
    static ImprovedRepository instance;
    return instance;
}

void ImprovedRepository::RegisterJoinCase(Channels channels, Objects context, uint64_t runnable_id) {
    std::sort(
        channels.begin(), channels.end(),
        [](ChannelPtr left, ChannelPtr right){ return left->GetID() < right->GetID(); }
    );

    std::vector<ChannelDataPointer> channels_data(channels.size());
    std::transform(
        channels.begin(), channels.end(), channels_data.begin(),
        [](ChannelPtr channel){ return std::dynamic_pointer_cast<ChannelReference>(channel)->channel_data_; }
    );

    std::for_each(channels_data.begin(), channels_data.end(), [](auto data){ data->Lock(); });

    auto reaction = std::make_shared<Reaction>(channels_data, context, runnable_id);
    for (size_t i = 0; i < channels_data.size(); ++i) {
        channels_data[i]->dependent_reactions_.push_back(ReactionPointer(reaction, i));
    }

    std::for_each(channels_data.begin(), channels_data.end(), [](auto data){ data->Unlock(); });
}

ChannelPtr ImprovedRepository::NewChannel(ChannelMode mode, Type payload_type) {
    return std::make_shared<ChannelReference>(mode, payload_type, next_id.fetch_add(1, std::memory_order_relaxed));
}

void ImprovedRepository::Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) {
    runnable_map_ = std::move(runnable_map);
    auto main_runnable_it = runnable_map_.find(main_runnable_id);

    debug::runtime_assert(main_runnable_it != runnable_map_.end(), "main runnable not found");
    debug::runtime_assert(main_runnable_it->second != nullptr, "main runnable pointer is nullptr");

    is_complete.store(false);

    std::vector<std::thread> runner_threads;
    runner_threads.reserve(max_runner_threads);

    {
        auto guard = Guard();
        for (auto i = 0; i < max_runner_threads; ++i) {
            runner_threads.emplace_back(
                std::bind(&ImprovedRepository::RunRoutine, this, i));
        }

        calls.push_back({Objects{}, Objects{}, main_runnable_it->second});
        calls_semaphore.release();
    }

    while (!is_complete.load()) {
        std::this_thread::yield();
    }

    for (auto i = 0; i < max_runner_threads; ++i) {
        calls_semaphore.release();
    }
    for (auto& runner_thread : runner_threads) {
        runner_thread.join();
    }
}

ImprovedRepository::ImprovedRepository()
    : total_calls(0),
      calls_per_thread(max_runner_threads),
      calls(),
      next_id(0),
      is_complete(false),
      active_threads(0),
      calls_semaphore(0) {}

void ImprovedRepository::RunRoutine(size_t thread_index) noexcept {
    while (true) {
        calls_semaphore.acquire();
        if (is_complete.load()) {
            return;
        }
        total_calls.fetch_add(1, std::memory_order_relaxed);
        calls_per_thread[thread_index].fetch_add(1, std::memory_order_relaxed);
        SchedulledCall call;
        {
            auto guard = Guard();
            debug::runtime_assert(!calls.empty(),
                                  "scheduled routine queue is empty");
            call = std::move(calls.front());
            calls.pop_front();
            ++active_threads;
        }

        call.runnable->operator()(call.inputs, call.context);
        --active_threads;
    }
}

void ImprovedRepository::ScheduleCall(Objects inputs, Objects context, uint64_t runnable_id) noexcept {
    auto runnable = runnable_map_[runnable_id];
    auto guard = Guard();

    calls.push_back(SchedulledCall{inputs, context, runnable});
    calls_semaphore.release();
}

}  // namespace reactor
