#include "events.hpp"

#include <sstream>
#include <iomanip>

namespace reactor {

// RuntimeEventType to string conversion
std::string ToString(RuntimeEventType type) {
    switch (type) {
        case RuntimeEventType::ChannelCreated:
            return "ChannelCreated";
        case RuntimeEventType::ChannelClosed:
            return "ChannelClosed";
        case RuntimeEventType::MessageSent:
            return "MessageSent";
        case RuntimeEventType::MessageReceived:
            return "MessageReceived";
        case RuntimeEventType::JoinCaseRegistered:
            return "JoinCaseRegistered";
        case RuntimeEventType::JoinCaseRemoved:
            return "JoinCaseRemoved";
        case RuntimeEventType::MatchDetected:
            return "MatchDetected";
        case RuntimeEventType::MatchFailed:
            return "MatchFailed";
        case RuntimeEventType::FiringCommitted:
            return "FiringCommitted";
        case RuntimeEventType::FiringRolledBack:
            return "FiringRolledBack";
        case RuntimeEventType::ReactionScheduled:
            return "ReactionScheduled";
        case RuntimeEventType::ReactionStarted:
            return "ReactionStarted";
        case RuntimeEventType::ReactionCompleted:
            return "ReactionCompleted";
        case RuntimeEventType::ReactionFailed:
            return "ReactionFailed";
        case RuntimeEventType::RepositoryStarted:
            return "RepositoryStarted";
        case RuntimeEventType::RepositoryShuttingDown:
            return "RepositoryShuttingDown";
        case RuntimeEventType::RepositoryCompleted:
            return "RepositoryCompleted";
        case RuntimeEventType::RepositoryFailed:
            return "RepositoryFailed";
        default:
            return "Unknown";
    }
}

// Helper function to escape JSON strings
static std::string EscapeJSON(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"':  oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default:
                if (c < 0x20) {
                    oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
                } else {
                    oss << c;
                }
        }
    }
    return oss.str();
}

// Helper function to format IDs as JSON array
static std::string IDsToJSON(const IDs& ids) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << ids[i];
    }
    oss << "]";
    return oss.str();
}

// ChannelEventData implementations
std::string ChannelEventData::ToString() const {
    std::ostringstream oss;
    oss << "Channel{id=" << channel_id 
        << ", mode=" << (mode == ChannelMode::Sync ? "Sync" : "Async")
        << ", type=" << payload_type.ToString();
    if (message.has_value()) {
        oss << ", message=" << message.value().ToString();
    }
    oss << "}";
    return oss.str();
}

std::string ChannelEventData::ToJSON() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"channel_id\": " << channel_id << ", ";
    oss << "\"mode\": \"" << (mode == ChannelMode::Sync ? "Sync" : "Async") << "\", ";
    oss << "\"payload_type\": \"" << EscapeJSON(payload_type.ToString()) << "\"";
    if (message.has_value()) {
        oss << ", \"message\": \"" << EscapeJSON(message.value().ToString()) << "\"";
    }
    oss << "}";
    return oss.str();
}

// MatchEventData implementations
std::string MatchEventData::ToString() const {
    std::ostringstream oss;
    oss << "Match{";
    if (match_id != 0) {
        oss << "match_id=" << match_id << ", ";
    }
    oss << "join_case_id=" << join_case_id
        << ", channels=[";
    for (size_t i = 0; i < channel_ids.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << channel_ids[i];
    }
    oss << "], success=" << (success ? "true" : "false");
    if (failure_reason.has_value()) {
        oss << ", reason=\"" << failure_reason.value() << "\"";
    }
    oss << "}";
    return oss.str();
}

std::string MatchEventData::ToJSON() const {
    std::ostringstream oss;
    oss << "{";
    if (match_id != 0) {
        oss << "\"match_id\": " << match_id << ", ";
    }
    oss << "\"join_case_id\": " << join_case_id << ", ";
    oss << "\"channel_ids\": " << IDsToJSON(channel_ids) << ", ";
    oss << "\"success\": " << (success ? "true" : "false");
    if (failure_reason.has_value()) {
        oss << ", \"failure_reason\": \"" << EscapeJSON(failure_reason.value()) << "\"";
    }
    oss << "}";
    return oss.str();
}

// FiringEventData implementations
std::string FiringEventData::ToString() const {
    std::ostringstream oss;
    oss << "Firing{firing_id=" << firing_id
        << ", match_id=" << match_id
        << ", message_count=" << message_count
        << "}";
    return oss.str();
}

std::string FiringEventData::ToJSON() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"firing_id\": " << firing_id << ", ";
    oss << "\"match_id\": " << match_id << ", ";
    oss << "\"message_count\": " << message_count;
    oss << "}";
    return oss.str();
}

// ReactionEventData implementations
std::string ReactionEventData::ToString() const {
    std::ostringstream oss;
    oss << "Reaction{reaction_id=" << reaction_id
        << ", firing_id=" << firing_id;
    if (result.has_value()) {
        oss << ", result=" << result.value().ToString();
    }
    oss << "}";
    return oss.str();
}

std::string ReactionEventData::ToJSON() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"reaction_id\": " << reaction_id << ", ";
    oss << "\"firing_id\": " << firing_id;
    if (result.has_value()) {
        const auto& res = result.value();
        oss << ", \"result\": {";
        oss << "\"status\": \"" << reactor::ToString(res.status) << "\", ";
        oss << "\"duration_ms\": " << res.duration.count();
        if (res.error_message.has_value()) {
            oss << ", \"error_message\": \"" << EscapeJSON(res.error_message.value()) << "\"";
        }
        oss << "}";
    }
    oss << "}";
    return oss.str();
}

// LifecycleEventData implementations
std::string LifecycleEventData::ToString() const {
    std::ostringstream oss;
    oss << "Lifecycle{state=" << reactor::ToString(state);
    if (reason.has_value()) {
        oss << ", reason=\"" << reason.value() << "\"";
    }
    oss << "}";
    return oss.str();
}

std::string LifecycleEventData::ToJSON() const {
    std::ostringstream oss;
    oss << "{";
    oss << "\"state\": \"" << EscapeJSON(reactor::ToString(state)) << "\"";
    if (reason.has_value()) {
        oss << ", \"reason\": \"" << EscapeJSON(reason.value()) << "\"";
    }
    oss << "}";
    return oss.str();
}

// RuntimeEvent implementations
std::string RuntimeEvent::ToString() const {
    std::ostringstream oss;
    
    // Format timestamp as microseconds since epoch
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(
        timestamp.time_since_epoch()).count();
    
    oss << "[" << reactor::ToString(type) << " @" << micros << "us thread=" << thread_id << "] ";
    
    // Format event-specific data
    std::visit([&oss](const auto& event_data) {
        oss << event_data.ToString();
    }, data);
    
    return oss.str();
}

std::string RuntimeEvent::ToJSON() const {
    std::ostringstream oss;
    
    // Format timestamp as microseconds since epoch
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(
        timestamp.time_since_epoch()).count();
    
    oss << "{";
    oss << "\"event_id\": " << event_id << ", ";
    oss << "\"type\": \"" << reactor::ToString(type) << "\", ";
    oss << "\"timestamp_us\": " << micros << ", ";
    oss << "\"thread_id\": \"" << thread_id << "\", ";
    oss << "\"data\": ";
    
    // Format event-specific data
    std::visit([&oss](const auto& event_data) {
        oss << event_data.ToJSON();
    }, data);
    
    oss << "}";
    return oss.str();
}

// Event creation helper functions
RuntimeEvent CreateChannelCreatedEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::ChannelCreated,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ChannelEventData{channel_id, mode, payload_type, {}}
    };
}

RuntimeEvent CreateChannelClosedEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::ChannelClosed,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ChannelEventData{channel_id, mode, payload_type, {}}
    };
}

RuntimeEvent CreateMessageSentEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type,
    const Object& message) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::MessageSent,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ChannelEventData{channel_id, mode, payload_type, message}
    };
}

RuntimeEvent CreateMessageReceivedEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type,
    const Object& message) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::MessageReceived,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ChannelEventData{channel_id, mode, payload_type, message}
    };
}

RuntimeEvent CreateJoinCaseRegisteredEvent(
    uint64_t event_id,
    uint64_t join_case_id,
    const IDs& channel_ids) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::JoinCaseRegistered,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        MatchEventData{0, join_case_id, channel_ids, true, {}}
    };
}

RuntimeEvent CreateJoinCaseRemovedEvent(
    uint64_t event_id,
    uint64_t join_case_id,
    const IDs& channel_ids) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::JoinCaseRemoved,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        MatchEventData{0, join_case_id, channel_ids, true, {}}
    };
}

RuntimeEvent CreateMatchDetectedEvent(
    uint64_t event_id,
    const Match& match) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::MatchDetected,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        MatchEventData{match.match_id, match.join_case_id, match.input_channel_ids, true, {}}
    };
}

RuntimeEvent CreateMatchFailedEvent(
    uint64_t event_id,
    uint64_t join_case_id,
    const IDs& channel_ids,
    const std::string& reason) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::MatchFailed,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        MatchEventData{0, join_case_id, channel_ids, false, reason}
    };
}

RuntimeEvent CreateFiringCommittedEvent(
    uint64_t event_id,
    const Firing& firing) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::FiringCommitted,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        FiringEventData{firing.firing_id, firing.match.match_id, firing.consumed_messages.size()}
    };
}

RuntimeEvent CreateFiringRolledBackEvent(
    uint64_t event_id,
    uint64_t firing_id,
    uint64_t match_id,
    size_t message_count) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::FiringRolledBack,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        FiringEventData{firing_id, match_id, message_count}
    };
}

RuntimeEvent CreateReactionScheduledEvent(
    uint64_t event_id,
    const ScheduledReaction& reaction) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::ReactionScheduled,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ReactionEventData{reaction.reaction_id, reaction.firing.firing_id, {}}
    };
}

RuntimeEvent CreateReactionStartedEvent(
    uint64_t event_id,
    uint64_t reaction_id,
    uint64_t firing_id) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::ReactionStarted,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ReactionEventData{reaction_id, firing_id, {}}
    };
}

RuntimeEvent CreateReactionCompletedEvent(
    uint64_t event_id,
    const ExecutionResult& result) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::ReactionCompleted,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ReactionEventData{result.reaction_id, 0, result}
    };
}

RuntimeEvent CreateReactionFailedEvent(
    uint64_t event_id,
    const ExecutionResult& result) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::ReactionFailed,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        ReactionEventData{result.reaction_id, 0, result}
    };
}

RuntimeEvent CreateRepositoryStartedEvent(uint64_t event_id) {
    return RuntimeEvent{
        event_id,
        RuntimeEventType::RepositoryStarted,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        LifecycleEventData{RepositoryState::Running, {}}
    };
}

RuntimeEvent CreateRepositoryShuttingDownEvent(
    uint64_t event_id,
    const Maybe<std::string>& reason) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::RepositoryShuttingDown,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        LifecycleEventData{RepositoryState::ShuttingDown, reason}
    };
}

RuntimeEvent CreateRepositoryCompletedEvent(uint64_t event_id) {
    return RuntimeEvent{
        event_id,
        RuntimeEventType::RepositoryCompleted,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        LifecycleEventData{RepositoryState::Completed, {}}
    };
}

RuntimeEvent CreateRepositoryFailedEvent(
    uint64_t event_id,
    const std::string& reason) {
    
    return RuntimeEvent{
        event_id,
        RuntimeEventType::RepositoryFailed,
        std::chrono::steady_clock::now(),
        std::this_thread::get_id(),
        LifecycleEventData{RepositoryState::Failed, reason}
    };
}

}  // namespace reactor
