#include "repository.hpp"

#include <algorithm>
#include <format>
#include <iterator>
#include <runtime/reactor/common/logging.hpp>
#include <thread>
#include <vector>

namespace reactor {

thread_local CallQueueWriteIterator write_iterator;

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

SchedulledCall::SchedulledCall() : lock(0) {}

CallQueueNode::CallQueueNode() : next_write_pos(0), next_read_pos(0) {}

std::shared_ptr<CallQueueNode> CallQueueNode::AllocateNext() {
    auto guard = Guard();

    if (!static_cast<bool>(next)) {
        next = std::make_shared<CallQueueNode>();
    }
    return next;
}

void CallQueueWriteIterator::ScheduleCall(Objects inputs, Objects context, Runnable* runnable) {
    size_t pos = node->next_write_pos.fetch_add(1, std::memory_order_relaxed);
    if (pos < calls_queue_node_size) {
        node->calls[pos].inputs = inputs;
        node->calls[pos].context = context;
        node->calls[pos].runnable = runnable;
        node->calls[pos].lock.release();
        return;
    }
    global_offset += calls_queue_node_size;
    node = node->AllocateNext();
    ScheduleCall(inputs, context, runnable);
}

size_t CallQueueWriteIterator::GetLastPos() {
    return global_offset + node->next_write_pos.load(std::memory_order_relaxed);
}

std::tuple<SchedulledCall*, size_t> CallQueueReadIterator::GetNextCall() {
    size_t fetch_amount = write_iterator.GetLastPos() > (GetLastPos() + calls_queue_batch_threshold) ? calls_queue_batch_size : 1;
    size_t pos = node->next_read_pos.fetch_add(fetch_amount, std::memory_order_relaxed);
    if (pos < calls_queue_node_size) {
        return {&(node->calls[pos]), std::min(pos + fetch_amount, calls_queue_node_size) - pos};
    }
    global_offset += calls_queue_node_size;
    node = node->AllocateNext();
    return GetNextCall();
}

size_t CallQueueReadIterator::GetLastPos() {
    return global_offset + node->next_read_pos.load(std::memory_order_relaxed);
}

ChannelData::ChannelData(uint64_t id) noexcept
    : id_(id), queue_(), dependent_reactions_() {}

ChannelReference::ChannelReference(ChannelMode mode, Type payload_type, uint64_t id) noexcept
    : ChannelBase(mode, std::move(payload_type)), channel_data_(std::make_shared<ChannelData>(id)) {}

ChannelReference::~ChannelReference() noexcept {
    GetLifecycle().OnLastReferenceDropped();
}

void ChannelReference::Push(const Object& message) {
    if (!CanAcceptMessages()) {
        debug::runtime_assert(false, "Cannot push to closed/closing channel");
        return;
    }
    
    auto channel_lock_guard = channel_data_->Guard();

    {
        auto queue_lock_guard = channel_data_->queue_.Guard();
        auto was_empty = channel_data_->queue_.Empty();
        channel_data_->queue_.Push(message);
        
        auto& repo = ImprovedRepository::GetRepository();
        if (repo.GetEventEmitter()->IsEnabled()) {
            repo.GetEventEmitter()->EmitMessageSent(channel_data_->id_, mode(), payload_type(), message);
        }
        
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
            auto& repo = ImprovedRepository::GetRepository();
            if (repo.GetEventEmitter()->IsEnabled()) {
                IDs channel_ids;
                for (auto& input : reaction->inputs_) {
                    channel_ids.push_back(input->id_);
                }
                Match match{
                    .match_id = IDGenerator::Instance().NextMatchID(),
                    .join_case_id = reaction->runnable_id_,
                    .input_channel_ids = channel_ids,
                    .detected_at = std::chrono::steady_clock::now()
                };
                repo.GetEventEmitter()->EmitMatchDetected(match);
            }
            
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

    if (event_emitter_->IsEnabled()) {
        uint64_t join_case_id = next_join_case_id_.fetch_add(1, std::memory_order_relaxed);
        IDs channel_ids;
        channel_ids.reserve(channels.size());
        for (const auto& ch : channels) {
            channel_ids.push_back(ch->GetID());
        }
        event_emitter_->EmitJoinCaseRegistered(join_case_id, channel_ids);
    }
}

ChannelPtr ImprovedRepository::NewChannel(ChannelMode mode, Type payload_type) {
    uint64_t channel_id = next_id.fetch_add(1, std::memory_order_relaxed);
    
    auto channel = std::make_shared<ChannelReference>(mode, payload_type, channel_id);
    
    if (event_emitter_->IsEnabled()) {
        event_emitter_->EmitChannelCreated(channel_id, mode, payload_type);
    }
    
    return channel;
}

void ImprovedRepository::Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) {
    lifecycle_.Start();
    if (event_emitter_->IsEnabled()) {
        event_emitter_->EmitRepositoryStarted();
    }

    runnable_map_ = std::move(runnable_map);
    auto main_runnable_it = runnable_map_.find(main_runnable_id);

    debug::runtime_assert(main_runnable_it != runnable_map_.end(), "main runnable not found");
    debug::runtime_assert(main_runnable_it->second != nullptr, "main runnable pointer is nullptr");

    is_complete.store(false);

    std::vector<std::thread> runner_threads;
    runner_threads.reserve(max_runner_threads);

    auto call_queue_node = std::make_shared<CallQueueNode>();

    for (auto i = 0; i < max_runner_threads; ++i) {
        runner_threads.emplace_back(
            std::bind(&ImprovedRepository::RunRoutine, this, i, call_queue_node));
    }

    CallQueueWriteIterator{.node = call_queue_node}.ScheduleCall(Objects{}, Objects{}, main_runnable_it->second);

    for (auto& runner_thread : runner_threads) {
        runner_thread.join();
    }

    lifecycle_.MarkCompleted();
    if (event_emitter_->IsEnabled()) {
        event_emitter_->EmitRepositoryCompleted();
    }
}

ImprovedRepository::ImprovedRepository()
    : next_id(0),
      next_join_case_id_(0),
      is_complete(false),
      lifecycle_(),
      event_emitter_(std::make_shared<EventEmitter>()),
      error_handler_(ErrorPolicy::IsolateReaction) {}

void ImprovedRepository::RunRoutine(size_t thread_index, std::shared_ptr<CallQueueNode> node) noexcept {
    write_iterator = CallQueueWriteIterator{.node = node};
    auto read_iterator = CallQueueReadIterator{.node = node};
    while (true) {
        if (is_complete.load() || lifecycle_.ShouldTerminate()) {
            break;
        }
        
        auto [call_batch_ptr, batch_size] = read_iterator.GetNextCall();
        for (size_t i = 0; i < batch_size; ++i) {
            auto call = call_batch_ptr + i;
            call->lock.acquire();
            
            auto started_at = std::chrono::steady_clock::now();
            uint64_t reaction_id = IDGenerator::Instance().NextReactionID();
            
            try {
                if (event_emitter_->IsEnabled()) {
                    event_emitter_->EmitReactionStarted(reaction_id, 0);
                }
                
                call->runnable->operator()(call->inputs, call->context);
                
                auto completed_at = std::chrono::steady_clock::now();
                
                if (event_emitter_->IsEnabled()) {
                    ExecutionResult result{
                        .reaction_id = reaction_id,
                        .status = ExecutionStatus::Success,
                        .error_message = {},
                        .exception = {},
                        .started_at = started_at,
                        .completed_at = completed_at,
                        .duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                            completed_at - started_at)
                    };
                    event_emitter_->EmitReactionCompleted(result);
                }
                
            } catch (...) {
                std::exception_ptr exception = std::current_exception();
                auto completed_at = std::chrono::steady_clock::now();
                
                ExecutionResult result{
                    .reaction_id = reaction_id,
                    .status = ExecutionStatus::Failed,
                    .error_message = {},
                    .exception = exception,
                    .started_at = started_at,
                    .completed_at = completed_at,
                    .duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        completed_at - started_at)
                };
                
                try {
                    std::rethrow_exception(exception);
                } catch (const std::exception& e) {
                    result.error_message = e.what();
                } catch (...) {
                    result.error_message = "Unknown exception";
                }
                
                if (event_emitter_->IsEnabled()) {
                    event_emitter_->EmitReactionFailed(result);
                }
                
                ErrorPolicy policy = error_handler_.GetPolicy();
                if (policy == ErrorPolicy::FailFast) {
                    // For FailFast, we need to create a ScheduledReaction to pass to HandleReactionError
                    // For now, just trigger shutdown without storing
                    Shutdown();
                    break;
                } else {
                    // Isolate error and continue
                    // Error is already logged via event system
                }
            }
        }
    }
}

void ImprovedRepository::ScheduleCall(Objects inputs, Objects context, uint64_t runnable_id) noexcept {
    auto runnable = runnable_map_[runnable_id];
    write_iterator.ScheduleCall(inputs, context, runnable);
}

void ChannelReference::NotifyQueueEmpty() noexcept {
    GetLifecycle().OnQueueEmpty();
}

void ChannelReference::NotifyLastReference() noexcept {
    GetLifecycle().OnLastReferenceDropped();
}

void ImprovedRepository::Shutdown() noexcept {
    lifecycle_.BeginShutdown();
    is_complete.store(true);
    if (event_emitter_->IsEnabled()) {
        event_emitter_->EmitRepositoryShuttingDown();
    }
}

void ImprovedRepository::WaitForCompletion() noexcept {
    while (!lifecycle_.ShouldTerminate()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

RepositoryState ImprovedRepository::GetState() const noexcept {
    return lifecycle_.GetState();
}

bool ImprovedRepository::IsRunning() const noexcept {
    return lifecycle_.IsRunning();
}

void ImprovedRepository::SetEventLogger(Pointer<EventLogger> logger) {
    event_emitter_->SetLogger(logger);
}

Pointer<EventLogger> ImprovedRepository::GetEventLogger() const {
    return event_emitter_->GetLogger();
}

Pointer<EventEmitter> ImprovedRepository::GetEventEmitter() const {
    return event_emitter_;
}

ErrorHandler& ImprovedRepository::GetErrorHandler() {
    return error_handler_;
}

const ErrorHandler& ImprovedRepository::GetErrorHandler() const {
    return error_handler_;
}

}  // namespace reactor
