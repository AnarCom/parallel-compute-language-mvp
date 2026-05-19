#include "execution_context.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>

#include "repository.hpp"

namespace reactor {

// Thread-local storage for current execution context
thread_local ExecutionContext* current_execution_context = nullptr;

// ExecutionContext implementation

ExecutionContext::ExecutionContext()
    : next_temp_id_(1)
{
}

ExecutionContext::~ExecutionContext() = default;

Pointer<ChannelBase> ExecutionContext::RecordNewChannel(ChannelMode mode, Type payload_type) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Generate temporary ID
    uint64_t temp_id = next_temp_id_++;
    
    // Store pending channel
    PendingChannel pending{
        .temp_id = temp_id,
        .mode = mode,
        .payload_type = payload_type,
        .redis_id = ""  // Will be assigned during commit
    };
    pending_channels_[temp_id] = pending;
    
    // Create and return proxy channel with temporary ID
    return std::make_shared<RedisChannel>(mode, payload_type, temp_id);
}

void ExecutionContext::RecordJoinCase(const Channels& inputs, const Objects& context, uint64_t runnable_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Extract temporary IDs from input channels
    std::vector<uint64_t> input_temp_ids;
    input_temp_ids.reserve(inputs.size());
    
    for (const auto& channel_ptr : inputs) {
        // Cast to RedisChannel to get temporary ID
        auto redis_channel = std::dynamic_pointer_cast<RedisChannel>(channel_ptr);
        if (!redis_channel) {
            throw std::invalid_argument(
                "RecordJoinCase: All input channels must be RedisChannel instances. "
                "Found a channel of different type."
            );
        }
        
        uint64_t temp_id = redis_channel->GetTempID();
        
        // Verify the channel exists in our pending channels
        if (pending_channels_.find(temp_id) == pending_channels_.end()) {
            throw std::invalid_argument(
                "RecordJoinCase: Channel with temp_id " + std::to_string(temp_id) + 
                " not found in execution context. This channel may have been created in a different context."
            );
        }
        
        input_temp_ids.push_back(temp_id);
    }
    
    // Store pending join-case
    PendingJoinCase pending{
        .input_channel_temp_ids = std::move(input_temp_ids),
        .context = context,
        .runnable_id = runnable_id
    };
    pending_join_cases_.push_back(std::move(pending));
}

void ExecutionContext::RecordPush(uint64_t channel_temp_id, const Object& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Verify the channel exists
    if (pending_channels_.find(channel_temp_id) == pending_channels_.end()) {
        throw std::invalid_argument(
            "RecordPush: Channel with temp_id " + std::to_string(channel_temp_id) + 
            " not found in execution context. Cannot push to a non-existent channel."
        );
    }
    
    // Store pending push
    PendingPush pending{
        .channel_temp_id = channel_temp_id,
        .message = message
    };
    pending_pushes_.push_back(std::move(pending));
}

ExecutionResult ExecutionContext::ExtractResult() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Convert pending channels to channel creations
    std::vector<ChannelCreation> channels;
    channels.reserve(pending_channels_.size());
    for (const auto& [temp_id, pending] : pending_channels_) {
        channels.push_back(ChannelCreation{
            .temp_id = pending.temp_id,
            .mode = pending.mode,
            .payload_type = pending.payload_type
        });
    }
    
    // Convert pending join-cases to join-case registrations
    std::vector<JoinCaseRegistration> join_cases;
    join_cases.reserve(pending_join_cases_.size());
    for (const auto& pending : pending_join_cases_) {
        join_cases.push_back(JoinCaseRegistration{
            .input_channel_temp_ids = pending.input_channel_temp_ids,
            .context = pending.context,
            .runnable_id = pending.runnable_id
        });
    }
    
    // Convert pending pushes to message pushes
    std::vector<MessagePush> pushes;
    pushes.reserve(pending_pushes_.size());
    for (const auto& pending : pending_pushes_) {
        pushes.push_back(MessagePush{
            .channel_temp_id = pending.channel_temp_id,
            .message = pending.message
        });
    }
    
    // Clear internal state
    pending_channels_.clear();
    pending_join_cases_.clear();
    pending_pushes_.clear();
    next_temp_id_ = 1;
    
    // Return immutable result
    return ExecutionResult(std::move(channels), std::move(join_cases), std::move(pushes));
}

bool ExecutionContext::HasChannel(uint64_t temp_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return pending_channels_.find(temp_id) != pending_channels_.end();
}

const PendingChannel& ExecutionContext::GetChannel(uint64_t temp_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = pending_channels_.find(temp_id);
    if (it == pending_channels_.end()) {
        throw std::out_of_range(
            "GetChannel: Channel with temp_id " + std::to_string(temp_id) + " not found"
        );
    }
    
    return it->second;
}

// ExecutionContextGuard implementation

ExecutionContextGuard::ExecutionContextGuard(ExecutionContext* ctx)
    : previous_context_(current_execution_context)
{
    current_execution_context = ctx;
}

ExecutionContextGuard::~ExecutionContextGuard() {
    current_execution_context = previous_context_;
}

}  // namespace reactor
