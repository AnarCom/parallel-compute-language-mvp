#include "event_emitter.hpp"

namespace reactor {

// ============================================================================
// EventEmitter Implementation
// ============================================================================

EventEmitter::EventEmitter(Pointer<EventLogger> logger)
    : logger_(std::move(logger)) {
}

void EventEmitter::SetLogger(Pointer<EventLogger> logger) {
    std::lock_guard<std::mutex> lock(mutex_);
    logger_ = std::move(logger);
}

Pointer<EventLogger> EventEmitter::GetLogger() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return logger_;
}

bool EventEmitter::IsEnabled() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return logger_ != nullptr;
}

uint64_t EventEmitter::NextEventID() noexcept {
    return event_counter_.fetch_add(1, std::memory_order_relaxed);
}

void EventEmitter::EmitEvent(const RuntimeEvent& event) {
    // Increment total events counter
    total_events_.fetch_add(1, std::memory_order_relaxed);
    
    // Get logger under lock
    Pointer<EventLogger> logger;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        logger = logger_;
    }
    
    // Log event if logger is set (outside the lock to avoid holding it during logging)
    if (logger) {
        try {
            logger->Log(event);
        } catch (...) {
            // Catch and ignore exceptions to prevent disrupting runtime
        }
    }
}

// ============================================================================
// Channel Events
// ============================================================================

void EventEmitter::EmitChannelCreated(
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type) {
    
    auto event = CreateChannelCreatedEvent(
        NextEventID(),
        channel_id,
        mode,
        payload_type);
    
    EmitEvent(event);
}

void EventEmitter::EmitChannelClosed(
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type) {
    
    auto event = CreateChannelClosedEvent(
        NextEventID(),
        channel_id,
        mode,
        payload_type);
    
    EmitEvent(event);
}

void EventEmitter::EmitMessageSent(
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type,
    const Object& message) {
    
    auto event = CreateMessageSentEvent(
        NextEventID(),
        channel_id,
        mode,
        payload_type,
        message);
    
    EmitEvent(event);
}

void EventEmitter::EmitMessageReceived(
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type,
    const Object& message) {
    
    auto event = CreateMessageReceivedEvent(
        NextEventID(),
        channel_id,
        mode,
        payload_type,
        message);
    
    EmitEvent(event);
}

// ============================================================================
// Match Events
// ============================================================================

void EventEmitter::EmitJoinCaseRegistered(
    uint64_t join_case_id,
    const IDs& channel_ids) {
    
    auto event = CreateJoinCaseRegisteredEvent(
        NextEventID(),
        join_case_id,
        channel_ids);
    
    EmitEvent(event);
}

void EventEmitter::EmitJoinCaseRemoved(
    uint64_t join_case_id,
    const IDs& channel_ids) {
    
    auto event = CreateJoinCaseRemovedEvent(
        NextEventID(),
        join_case_id,
        channel_ids);
    
    EmitEvent(event);
}

void EventEmitter::EmitMatchDetected(const Match& match) {
    auto event = CreateMatchDetectedEvent(NextEventID(), match);
    EmitEvent(event);
}

void EventEmitter::EmitMatchFailed(
    uint64_t join_case_id,
    const IDs& channel_ids,
    const std::string& reason) {
    
    auto event = CreateMatchFailedEvent(
        NextEventID(),
        join_case_id,
        channel_ids,
        reason);
    
    EmitEvent(event);
}

// ============================================================================
// Firing Events
// ============================================================================

void EventEmitter::EmitFiringCommitted(const Firing& firing) {
    auto event = CreateFiringCommittedEvent(NextEventID(), firing);
    EmitEvent(event);
}

void EventEmitter::EmitFiringRolledBack(
    uint64_t firing_id,
    uint64_t match_id,
    size_t message_count) {
    
    auto event = CreateFiringRolledBackEvent(
        NextEventID(),
        firing_id,
        match_id,
        message_count);
    
    EmitEvent(event);
}

// ============================================================================
// Reaction Events
// ============================================================================

void EventEmitter::EmitReactionScheduled(const ScheduledReaction& reaction) {
    auto event = CreateReactionScheduledEvent(NextEventID(), reaction);
    EmitEvent(event);
}

void EventEmitter::EmitReactionStarted(
    uint64_t reaction_id,
    uint64_t firing_id) {
    
    auto event = CreateReactionStartedEvent(
        NextEventID(),
        reaction_id,
        firing_id);
    
    EmitEvent(event);
}

void EventEmitter::EmitReactionCompleted(const ExecutionResult& result) {
    auto event = CreateReactionCompletedEvent(NextEventID(), result);
    EmitEvent(event);
}

void EventEmitter::EmitReactionFailed(const ExecutionResult& result) {
    auto event = CreateReactionFailedEvent(NextEventID(), result);
    EmitEvent(event);
}

// ============================================================================
// Lifecycle Events
// ============================================================================

void EventEmitter::EmitRepositoryStarted() {
    auto event = CreateRepositoryStartedEvent(NextEventID());
    EmitEvent(event);
}

void EventEmitter::EmitRepositoryShuttingDown(const Maybe<std::string>& reason) {
    auto event = CreateRepositoryShuttingDownEvent(NextEventID(), reason);
    EmitEvent(event);
}

void EventEmitter::EmitRepositoryCompleted() {
    auto event = CreateRepositoryCompletedEvent(NextEventID());
    EmitEvent(event);
}

void EventEmitter::EmitRepositoryFailed(const std::string& reason) {
    auto event = CreateRepositoryFailedEvent(NextEventID(), reason);
    EmitEvent(event);
}

// ============================================================================
// Statistics
// ============================================================================

uint64_t EventEmitter::GetEventCount() const noexcept {
    return total_events_.load(std::memory_order_relaxed);
}

void EventEmitter::ResetEventCount() noexcept {
    total_events_.store(0, std::memory_order_relaxed);
}

}  // namespace reactor
