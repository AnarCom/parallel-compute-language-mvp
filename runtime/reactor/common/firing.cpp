#include "firing.hpp"

#include <sstream>
#include <iomanip>

#include "interface.hpp"

namespace reactor {

// ============================================================================
// IDGenerator Implementation
// ============================================================================

IDGenerator& IDGenerator::Instance() {
    static IDGenerator instance;
    return instance;
}

uint64_t IDGenerator::NextMatchID() {
    return match_counter_.fetch_add(1, std::memory_order_relaxed);
}

uint64_t IDGenerator::NextFiringID() {
    return firing_counter_.fetch_add(1, std::memory_order_relaxed);
}

uint64_t IDGenerator::NextReactionID() {
    return reaction_counter_.fetch_add(1, std::memory_order_relaxed);
}

// ============================================================================
// Helper Functions
// ============================================================================

namespace {

/**
 * @brief Format a timestamp as a string with millisecond precision.
 * @param tp The time point to format.
 * @return String representation of the timestamp.
 */
std::string FormatTimestamp(const std::chrono::steady_clock::time_point& tp) {
    auto duration = tp.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
    std::ostringstream oss;
    oss << millis << "ms";
    return oss.str();
}

/**
 * @brief Format a duration as a string with millisecond precision.
 * @param duration The duration to format.
 * @return String representation of the duration.
 */
std::string FormatDuration(const std::chrono::milliseconds& duration) {
    std::ostringstream oss;
    oss << duration.count() << "ms";
    return oss.str();
}

/**
 * @brief Format a vector of IDs as a comma-separated string.
 * @param ids The vector of IDs to format.
 * @return String representation like "[1, 2, 3]".
 */
std::string FormatIDs(const IDs& ids) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << ids[i];
    }
    oss << "]";
    return oss.str();
}

/**
 * @brief Format a vector of Objects as a comma-separated string.
 * @param objects The vector of objects to format.
 * @return String representation like "[obj1, obj2, obj3]".
 */
std::string FormatObjects(const Objects& objects) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < objects.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << objects[i].ToString();
    }
    oss << "]";
    return oss.str();
}

}  // anonymous namespace

// ============================================================================
// Match Implementation
// ============================================================================

std::string Match::ToString() const {
    std::ostringstream oss;
    oss << "Match{"
        << "match_id=" << match_id
        << ", join_case_id=" << join_case_id
        << ", input_channel_ids=" << FormatIDs(input_channel_ids)
        << ", detected_at=" << FormatTimestamp(detected_at)
        << "}";
    return oss.str();
}

// ============================================================================
// Firing Implementation
// ============================================================================

std::string Firing::ToString() const {
    std::ostringstream oss;
    oss << "Firing{"
        << "firing_id=" << firing_id
        << ", match=" << match.ToString()
        << ", consumed_messages=" << FormatObjects(consumed_messages)
        << ", context=" << FormatObjects(context)
        << ", runnable_id=" << runnable_id
        << ", fired_at=" << FormatTimestamp(fired_at)
        << "}";
    return oss.str();
}

// ============================================================================
// ScheduledReaction Implementation
// ============================================================================

std::string ScheduledReaction::ToString() const {
    std::ostringstream oss;
    oss << "ScheduledReaction{"
        << "reaction_id=" << reaction_id
        << ", firing=" << firing.ToString()
        << ", runnable=" << (runnable ? std::to_string(runnable->GetID()) : "null")
        << ", scheduled_at=" << FormatTimestamp(scheduled_at)
        << "}";
    return oss.str();
}

// ============================================================================
// ExecutionStatus Implementation
// ============================================================================

std::string ToString(ExecutionStatus status) {
    switch (status) {
        case ExecutionStatus::Success:
            return "Success";
        case ExecutionStatus::Failed:
            return "Failed";
        case ExecutionStatus::Cancelled:
            return "Cancelled";
        default:
            return "Unknown";
    }
}

// ============================================================================
// ExecutionResult Implementation
// ============================================================================

bool ExecutionResult::IsSuccess() const noexcept {
    return status == ExecutionStatus::Success;
}

bool ExecutionResult::IsFailed() const noexcept {
    return status == ExecutionStatus::Failed;
}

bool ExecutionResult::IsCancelled() const noexcept {
    return status == ExecutionStatus::Cancelled;
}

std::string ExecutionResult::ToString() const {
    std::ostringstream oss;
    oss << "ExecutionResult{"
        << "reaction_id=" << reaction_id
        << ", status=" << reactor::ToString(status)
        << ", started_at=" << FormatTimestamp(started_at)
        << ", completed_at=" << FormatTimestamp(completed_at)
        << ", duration=" << FormatDuration(duration);
    
    if (error_message.has_value()) {
        oss << ", error_message=\"" << error_message.value() << "\"";
    }
    
    if (exception.has_value()) {
        oss << ", exception=<captured>";
    }
    
    oss << "}";
    return oss.str();
}

}  // namespace reactor
