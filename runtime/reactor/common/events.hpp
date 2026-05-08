#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <variant>
#include <vector>

#include "helpers.hpp"
#include "type_system.hpp"
#include "lifecycle.hpp"
#include "firing.hpp"

namespace reactor {

/**
 * @brief Types of runtime events that can be logged.
 * 
 * Events are categorized into:
 * - Channel events: Channel lifecycle and message operations
 * - Match events: Join-case registration and match detection
 * - Firing events: Message commitment for execution
 * - Reaction events: Reaction scheduling and execution
 * - Lifecycle events: Repository state transitions
 */
enum class RuntimeEventType {
    // Channel events
    /**
     * @brief A new channel was created.
     */
    ChannelCreated,
    
    /**
     * @brief A channel was explicitly closed.
     */
    ChannelClosed,
    
    /**
     * @brief A message was sent to a channel.
     */
    MessageSent,
    
    /**
     * @brief A message was received from a channel.
     */
    MessageReceived,
    
    // Matching events
    /**
     * @brief A new join-case was registered.
     */
    JoinCaseRegistered,
    
    /**
     * @brief A join-case was removed from the scheduler.
     */
    JoinCaseRemoved,
    
    /**
     * @brief A match was detected (all inputs ready).
     */
    MatchDetected,
    
    /**
     * @brief A match attempt failed (inputs not ready or channels closed).
     */
    MatchFailed,
    
    // Firing events
    /**
     * @brief A firing was committed (messages atomically consumed).
     */
    FiringCommitted,
    
    /**
     * @brief A firing was rolled back (transaction aborted).
     */
    FiringRolledBack,
    
    // Execution events
    /**
     * @brief A reaction was scheduled for execution.
     */
    ReactionScheduled,
    
    /**
     * @brief A reaction started executing.
     */
    ReactionStarted,
    
    /**
     * @brief A reaction completed successfully.
     */
    ReactionCompleted,
    
    /**
     * @brief A reaction failed with an error.
     */
    ReactionFailed,
    
    // Lifecycle events
    /**
     * @brief The repository started running.
     */
    RepositoryStarted,
    
    /**
     * @brief The repository began shutting down.
     */
    RepositoryShuttingDown,
    
    /**
     * @brief The repository completed successfully.
     */
    RepositoryCompleted,
    
    /**
     * @brief The repository failed with an error.
     */
    RepositoryFailed
};

/**
 * @brief Convert RuntimeEventType to string representation.
 * @param type The event type to convert.
 * @return String name of the event type.
 */
std::string ToString(RuntimeEventType type);

/**
 * @brief Event data for channel-related events.
 * 
 * Used for: ChannelCreated, ChannelClosed, MessageSent, MessageReceived
 */
struct ChannelEventData {
    /**
     * @brief Unique identifier of the channel.
     */
    uint64_t channel_id;
    
    /**
     * @brief Channel mode (Sync or Async).
     */
    ChannelMode mode;
    
    /**
     * @brief Type of messages the channel carries.
     */
    Type payload_type;
    
    /**
     * @brief Optional message data (for MessageSent/MessageReceived events).
     */
    Maybe<Object> message;
    
    /**
     * @brief Convert to string representation.
     * @return Human-readable string describing the event data.
     */
    std::string ToString() const;
    
    /**
     * @brief Convert to JSON representation.
     * @return JSON string describing the event data.
     */
    std::string ToJSON() const;
};

/**
 * @brief Event data for match-related events.
 * 
 * Used for: JoinCaseRegistered, JoinCaseRemoved, MatchDetected, MatchFailed
 */
struct MatchEventData {
    /**
     * @brief Unique identifier of the match (0 if not applicable).
     */
    uint64_t match_id;
    
    /**
     * @brief Identifier of the join-case.
     */
    uint64_t join_case_id;
    
    /**
     * @brief IDs of channels involved in the join-case.
     */
    IDs channel_ids;
    
    /**
     * @brief Whether the match was successful.
     */
    bool success;
    
    /**
     * @brief Optional failure reason (for MatchFailed events).
     */
    Maybe<std::string> failure_reason;
    
    /**
     * @brief Convert to string representation.
     * @return Human-readable string describing the event data.
     */
    std::string ToString() const;
    
    /**
     * @brief Convert to JSON representation.
     * @return JSON string describing the event data.
     */
    std::string ToJSON() const;
};

/**
 * @brief Event data for firing-related events.
 * 
 * Used for: FiringCommitted, FiringRolledBack
 */
struct FiringEventData {
    /**
     * @brief Unique identifier of the firing.
     */
    uint64_t firing_id;
    
    /**
     * @brief Identifier of the match that triggered this firing.
     */
    uint64_t match_id;
    
    /**
     * @brief Number of messages consumed in this firing.
     */
    size_t message_count;
    
    /**
     * @brief Convert to string representation.
     * @return Human-readable string describing the event data.
     */
    std::string ToString() const;
    
    /**
     * @brief Convert to JSON representation.
     * @return JSON string describing the event data.
     */
    std::string ToJSON() const;
};

/**
 * @brief Event data for reaction-related events.
 * 
 * Used for: ReactionScheduled, ReactionStarted, ReactionCompleted, ReactionFailed
 */
struct ReactionEventData {
    /**
     * @brief Unique identifier of the reaction.
     */
    uint64_t reaction_id;
    
    /**
     * @brief Identifier of the firing that created this reaction.
     */
    uint64_t firing_id;
    
    /**
     * @brief Optional execution result (for completed/failed reactions).
     */
    Maybe<ExecutionResult> result;
    
    /**
     * @brief Convert to string representation.
     * @return Human-readable string describing the event data.
     */
    std::string ToString() const;
    
    /**
     * @brief Convert to JSON representation.
     * @return JSON string describing the event data.
     */
    std::string ToJSON() const;
};

/**
 * @brief Event data for lifecycle-related events.
 * 
 * Used for: RepositoryStarted, RepositoryShuttingDown, RepositoryCompleted, RepositoryFailed
 */
struct LifecycleEventData {
    /**
     * @brief Current repository state.
     */
    RepositoryState state;
    
    /**
     * @brief Optional reason (for state transitions or failures).
     */
    Maybe<std::string> reason;
    
    /**
     * @brief Convert to string representation.
     * @return Human-readable string describing the event data.
     */
    std::string ToString() const;
    
    /**
     * @brief Convert to JSON representation.
     * @return JSON string describing the event data.
     */
    std::string ToJSON() const;
};

/**
 * @brief A runtime event capturing a significant occurrence in the system.
 * 
 * RuntimeEvent is the core data structure for the tracing system. Each event
 * captures:
 * - What happened (type)
 * - When it happened (timestamp)
 * - Where it happened (thread_id)
 * - Details about what happened (data variant)
 * 
 * Events are immutable once created and can be serialized to JSON for
 * external analysis tools.
 * 
 * Thread Safety: RuntimeEvent instances are immutable and safe to share
 * across threads once created.
 */
struct RuntimeEvent {
    /**
     * @brief Unique identifier for this event.
     */
    uint64_t event_id;
    
    /**
     * @brief Type of event that occurred.
     */
    RuntimeEventType type;
    
    /**
     * @brief When the event occurred (steady clock for relative timing).
     */
    std::chrono::steady_clock::time_point timestamp;
    
    /**
     * @brief ID of the thread that generated this event.
     */
    std::thread::id thread_id;
    
    /**
     * @brief Event-specific data.
     * 
     * The variant holds different data structures depending on the event type:
     * - Channel events: ChannelEventData
     * - Match events: MatchEventData
     * - Firing events: FiringEventData
     * - Reaction events: ReactionEventData
     * - Lifecycle events: LifecycleEventData
     */
    std::variant<
        ChannelEventData,
        MatchEventData,
        FiringEventData,
        ReactionEventData,
        LifecycleEventData
    > data;
    
    /**
     * @brief Convert event to human-readable string.
     * @return String representation of the event.
     */
    std::string ToString() const;
    
    /**
     * @brief Convert event to JSON format.
     * @return JSON string representation of the event.
     */
    std::string ToJSON() const;
};

/**
 * @brief Helper function to create a ChannelCreated event.
 * @param event_id Unique event identifier.
 * @param channel_id Channel identifier.
 * @param mode Channel mode (Sync/Async).
 * @param payload_type Type of messages in the channel.
 * @return RuntimeEvent for channel creation.
 */
RuntimeEvent CreateChannelCreatedEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type);

/**
 * @brief Helper function to create a ChannelClosed event.
 * @param event_id Unique event identifier.
 * @param channel_id Channel identifier.
 * @param mode Channel mode (Sync/Async).
 * @param payload_type Type of messages in the channel.
 * @return RuntimeEvent for channel closure.
 */
RuntimeEvent CreateChannelClosedEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type);

/**
 * @brief Helper function to create a MessageSent event.
 * @param event_id Unique event identifier.
 * @param channel_id Channel identifier.
 * @param mode Channel mode (Sync/Async).
 * @param payload_type Type of messages in the channel.
 * @param message The message that was sent.
 * @return RuntimeEvent for message send.
 */
RuntimeEvent CreateMessageSentEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type,
    const Object& message);

/**
 * @brief Helper function to create a MessageReceived event.
 * @param event_id Unique event identifier.
 * @param channel_id Channel identifier.
 * @param mode Channel mode (Sync/Async).
 * @param payload_type Type of messages in the channel.
 * @param message The message that was received.
 * @return RuntimeEvent for message receive.
 */
RuntimeEvent CreateMessageReceivedEvent(
    uint64_t event_id,
    uint64_t channel_id,
    ChannelMode mode,
    const Type& payload_type,
    const Object& message);

/**
 * @brief Helper function to create a JoinCaseRegistered event.
 * @param event_id Unique event identifier.
 * @param join_case_id Join-case identifier.
 * @param channel_ids IDs of input channels.
 * @return RuntimeEvent for join-case registration.
 */
RuntimeEvent CreateJoinCaseRegisteredEvent(
    uint64_t event_id,
    uint64_t join_case_id,
    const IDs& channel_ids);

/**
 * @brief Helper function to create a JoinCaseRemoved event.
 * @param event_id Unique event identifier.
 * @param join_case_id Join-case identifier.
 * @param channel_ids IDs of input channels.
 * @return RuntimeEvent for join-case removal.
 */
RuntimeEvent CreateJoinCaseRemovedEvent(
    uint64_t event_id,
    uint64_t join_case_id,
    const IDs& channel_ids);

/**
 * @brief Helper function to create a MatchDetected event.
 * @param event_id Unique event identifier.
 * @param match The match that was detected.
 * @return RuntimeEvent for match detection.
 */
RuntimeEvent CreateMatchDetectedEvent(
    uint64_t event_id,
    const Match& match);

/**
 * @brief Helper function to create a MatchFailed event.
 * @param event_id Unique event identifier.
 * @param join_case_id Join-case identifier.
 * @param channel_ids IDs of input channels.
 * @param reason Reason for match failure.
 * @return RuntimeEvent for match failure.
 */
RuntimeEvent CreateMatchFailedEvent(
    uint64_t event_id,
    uint64_t join_case_id,
    const IDs& channel_ids,
    const std::string& reason);

/**
 * @brief Helper function to create a FiringCommitted event.
 * @param event_id Unique event identifier.
 * @param firing The firing that was committed.
 * @return RuntimeEvent for firing commitment.
 */
RuntimeEvent CreateFiringCommittedEvent(
    uint64_t event_id,
    const Firing& firing);

/**
 * @brief Helper function to create a FiringRolledBack event.
 * @param event_id Unique event identifier.
 * @param firing_id Firing identifier.
 * @param match_id Match identifier.
 * @param message_count Number of messages involved.
 * @return RuntimeEvent for firing rollback.
 */
RuntimeEvent CreateFiringRolledBackEvent(
    uint64_t event_id,
    uint64_t firing_id,
    uint64_t match_id,
    size_t message_count);

/**
 * @brief Helper function to create a ReactionScheduled event.
 * @param event_id Unique event identifier.
 * @param reaction The scheduled reaction.
 * @return RuntimeEvent for reaction scheduling.
 */
RuntimeEvent CreateReactionScheduledEvent(
    uint64_t event_id,
    const ScheduledReaction& reaction);

/**
 * @brief Helper function to create a ReactionStarted event.
 * @param event_id Unique event identifier.
 * @param reaction_id Reaction identifier.
 * @param firing_id Firing identifier.
 * @return RuntimeEvent for reaction start.
 */
RuntimeEvent CreateReactionStartedEvent(
    uint64_t event_id,
    uint64_t reaction_id,
    uint64_t firing_id);

/**
 * @brief Helper function to create a ReactionCompleted event.
 * @param event_id Unique event identifier.
 * @param result The execution result.
 * @return RuntimeEvent for reaction completion.
 */
RuntimeEvent CreateReactionCompletedEvent(
    uint64_t event_id,
    const ExecutionResult& result);

/**
 * @brief Helper function to create a ReactionFailed event.
 * @param event_id Unique event identifier.
 * @param result The execution result with error information.
 * @return RuntimeEvent for reaction failure.
 */
RuntimeEvent CreateReactionFailedEvent(
    uint64_t event_id,
    const ExecutionResult& result);

/**
 * @brief Helper function to create a RepositoryStarted event.
 * @param event_id Unique event identifier.
 * @return RuntimeEvent for repository start.
 */
RuntimeEvent CreateRepositoryStartedEvent(uint64_t event_id);

/**
 * @brief Helper function to create a RepositoryShuttingDown event.
 * @param event_id Unique event identifier.
 * @param reason Optional reason for shutdown.
 * @return RuntimeEvent for repository shutdown.
 */
RuntimeEvent CreateRepositoryShuttingDownEvent(
    uint64_t event_id,
    const Maybe<std::string>& reason = {});

/**
 * @brief Helper function to create a RepositoryCompleted event.
 * @param event_id Unique event identifier.
 * @return RuntimeEvent for repository completion.
 */
RuntimeEvent CreateRepositoryCompletedEvent(uint64_t event_id);

/**
 * @brief Helper function to create a RepositoryFailed event.
 * @param event_id Unique event identifier.
 * @param reason Reason for failure.
 * @return RuntimeEvent for repository failure.
 */
RuntimeEvent CreateRepositoryFailedEvent(
    uint64_t event_id,
    const std::string& reason);

}  // namespace reactor
