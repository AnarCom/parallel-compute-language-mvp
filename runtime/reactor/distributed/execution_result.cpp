#include "execution_result.hpp"

#include <sstream>
#include <stdexcept>

namespace reactor {

ExecutionResult::ExecutionResult(
    std::vector<ChannelCreation> channels,
    std::vector<JoinCaseRegistration> join_cases,
    std::vector<MessagePush> pushes
)
    : channels_(std::move(channels))
    , join_cases_(std::move(join_cases))
    , pushes_(std::move(pushes))
{
}

const std::vector<ChannelCreation>& ExecutionResult::GetChannels() const noexcept {
    return channels_;
}

const std::vector<JoinCaseRegistration>& ExecutionResult::GetJoinCases() const noexcept {
    return join_cases_;
}

const std::vector<MessagePush>& ExecutionResult::GetPushes() const noexcept {
    return pushes_;
}

std::map<std::string, Objects> ExecutionResult::PrepareChannelMessagesMap(
    const std::unordered_map<uint64_t, std::string>& temp_id_to_redis_id
) const {
    std::map<std::string, Objects> result;
    
    // Group messages by Redis channel ID
    for (const auto& push : pushes_) {
        // Find the Redis ID for this temporary channel ID
        auto it = temp_id_to_redis_id.find(push.channel_temp_id);
        if (it == temp_id_to_redis_id.end()) {
            throw std::logic_error(
                "Channel temp_id " + std::to_string(push.channel_temp_id) + 
                " not found in Redis ID mapping. This indicates a bug in the execution context."
            );
        }
        
        const std::string& redis_id = it->second;
        
        // Add message to the vector for this channel
        result[redis_id].push_back(push.message);
    }
    
    return result;
}

size_t ExecutionResult::GetChannelCount() const noexcept {
    return channels_.size();
}

size_t ExecutionResult::GetJoinCaseCount() const noexcept {
    return join_cases_.size();
}

size_t ExecutionResult::GetPushCount() const noexcept {
    return pushes_.size();
}

bool ExecutionResult::IsEmpty() const noexcept {
    return channels_.empty() && join_cases_.empty() && pushes_.empty();
}

std::string ExecutionResult::ToString() const {
    std::ostringstream oss;
    
    oss << "ExecutionResult {\n";
    
    // Channels
    oss << "  Channels (" << channels_.size() << "):\n";
    for (const auto& channel : channels_) {
        oss << "    - temp_id=" << channel.temp_id
            << ", mode=" << (channel.mode == ChannelMode::Async ? "Async" : "Sync")
            << ", type=" << channel.payload_type.ToString() << "\n";
    }
    
    // Join-cases
    oss << "  JoinCases (" << join_cases_.size() << "):\n";
    for (const auto& join_case : join_cases_) {
        oss << "    - runnable_id=" << join_case.runnable_id
            << ", inputs=[";
        for (size_t i = 0; i < join_case.input_channel_temp_ids.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << join_case.input_channel_temp_ids[i];
        }
        oss << "], context_size=" << join_case.context.size() << "\n";
    }
    
    // Pushes
    oss << "  Pushes (" << pushes_.size() << "):\n";
    for (const auto& push : pushes_) {
        oss << "    - channel_temp_id=" << push.channel_temp_id
            << ", message=" << push.message.ToString() << "\n";
    }
    
    oss << "}";
    
    return oss.str();
}

}  // namespace reactor
