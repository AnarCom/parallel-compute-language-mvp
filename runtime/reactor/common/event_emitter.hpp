#pragma once

#include <atomic>
#include <mutex>

#include "events.hpp"
#include "event_logger.hpp"
#include "firing.hpp"
#include "helpers.hpp"
#include "lifecycle.hpp"
#include "type_system.hpp"

namespace reactor {

/**
 * @brief High-level interface for emitting runtime events.
 * 
 * EventEmitter provides convenient methods for creating and logging events
 * throughout the runtime. It manages event ID generation and delegates actual
 * logging to an EventLogger implementation.
 * 
 * The emitter provides type-safe convenience methods for each event type,
 * handling the details of event creation and ensuring consistent event
 * structure.
 * 
 * Thread Safety: All methods are thread-safe. Event IDs are generated using
 * atomic operations, and logging is delegated to the thread-safe EventLogger.
 * 
 * Example:
 * @code
 * auto logger = std::make_shared<InMemoryEventLogger>();
 * EventEmitter emitter(logger);
 * 
 * // Emit various events
 * emitter.EmitChannelCreated(channel_id, ChannelMode::Async, Type::Int());
 * emitter.EmitMessageSent(channel_id, message);
 * emitter.EmitRepositoryStarted();
 * @endcode
 */
class EventEmitter {
public:
    /**
     * @brief Construct an event emitter with optional logger.
     * 
     * @param logger The event logger to use. If nullptr, events are not logged
     *               (useful for disabling tracing).
     */
    explicit EventEmitter(Pointer<EventLogger> logger = nullptr);
    
    /**
     * @brief Destructor.
     */
    ~EventEmitter() noexcept = default;
    
    // Prevent copying
    EventEmitter(const EventEmitter&) = delete;
    EventEmitter& operator=(const EventEmitter&) = delete;
    
    // Allow moving
    EventEmitter(EventEmitter&&) noexcept = default;
    EventEmitter& operator=(EventEmitter&&) noexcept = default;
    
    /**
     * @brief Set the event logger.
     * 
     * Changes the logger used for future events. Thread-safe.
     * 
     * @param logger The new logger, or nullptr to disable logging.
     */
    void SetLogger(Pointer<EventLogger> logger);
    
    /**
     * @brief Get the current event logger.
     * 
     * Thread-safe.
     * 
     * @return The current logger, or nullptr if logging is disabled.
     */
    Pointer<EventLogger> GetLogger() const;
    
    /**
     * @brief Check if logging is enabled.
     * 
     * Thread-safe.
     * 
     * @return True if a logger is set, false otherwise.
     */
    bool IsEnabled() const;
    
    // ========================================================================
    // Channel Events
    // ========================================================================
    
    /**
     * @brief Emit a ChannelCreated event.
     * 
     * @param channel_id Unique identifier of the channel.
     * @param mode Channel mode (Sync or Async).
     * @param payload_type Type of messages in the channel.
     */
    void EmitChannelCreated(
        uint64_t channel_id,
        ChannelMode mode,
        const Type& payload_type);
    
    /**
     * @brief Emit a ChannelClosed event.
     * 
     * @param channel_id Unique identifier of the channel.
     * @param mode Channel mode (Sync or Async).
     * @param payload_type Type of messages in the channel.
     */
    void EmitChannelClosed(
        uint64_t channel_id,
        ChannelMode mode,
        const Type& payload_type);
    
    /**
     * @brief Emit a MessageSent event.
     * 
     * @param channel_id Unique identifier of the channel.
     * @param mode Channel mode (Sync or Async).
     * @param payload_type Type of messages in the channel.
     * @param message The message that was sent.
     */
    void EmitMessageSent(
        uint64_t channel_id,
        ChannelMode mode,
        const Type& payload_type,
        const Object& message);
    
    /**
     * @brief Emit a MessageReceived event.
     * 
     * @param channel_id Unique identifier of the channel.
     * @param mode Channel mode (Sync or Async).
     * @param payload_type Type of messages in the channel.
     * @param message The message that was received.
     */
    void EmitMessageReceived(
        uint64_t channel_id,
        ChannelMode mode,
        const Type& payload_type,
        const Object& message);
    
    // ========================================================================
    // Match Events
    // ========================================================================
    
    /**
     * @brief Emit a JoinCaseRegistered event.
     * 
     * @param join_case_id Unique identifier of the join-case.
     * @param channel_ids IDs of input channels for the join-case.
     */
    void EmitJoinCaseRegistered(
        uint64_t join_case_id,
        const IDs& channel_ids);
    
    /**
     * @brief Emit a JoinCaseRemoved event.
     * 
     * @param join_case_id Unique identifier of the join-case.
     * @param channel_ids IDs of input channels for the join-case.
     */
    void EmitJoinCaseRemoved(
        uint64_t join_case_id,
        const IDs& channel_ids);
    
    /**
     * @brief Emit a MatchDetected event.
     * 
     * @param match The match that was detected.
     */
    void EmitMatchDetected(const Match& match);
    
    /**
     * @brief Emit a MatchFailed event.
     * 
     * @param join_case_id Unique identifier of the join-case.
     * @param channel_ids IDs of input channels for the join-case.
     * @param reason Reason why the match failed.
     */
    void EmitMatchFailed(
        uint64_t join_case_id,
        const IDs& channel_ids,
        const std::string& reason);
    
    // ========================================================================
    // Firing Events
    // ========================================================================
    
    /**
     * @brief Emit a FiringCommitted event.
     * 
     * @param firing The firing that was committed.
     */
    void EmitFiringCommitted(const Firing& firing);
    
    /**
     * @brief Emit a FiringRolledBack event.
     * 
     * @param firing_id Unique identifier of the firing.
     * @param match_id Unique identifier of the match.
     * @param message_count Number of messages involved.
     */
    void EmitFiringRolledBack(
        uint64_t firing_id,
        uint64_t match_id,
        size_t message_count);
    
    // ========================================================================
    // Reaction Events
    // ========================================================================
    
    /**
     * @brief Emit a ReactionScheduled event.
     * 
     * @param reaction The scheduled reaction.
     */
    void EmitReactionScheduled(const ScheduledReaction& reaction);
    
    /**
     * @brief Emit a ReactionStarted event.
     * 
     * @param reaction_id Unique identifier of the reaction.
     * @param firing_id Unique identifier of the firing that created this reaction.
     */
    void EmitReactionStarted(
        uint64_t reaction_id,
        uint64_t firing_id);
    
    /**
     * @brief Emit a ReactionCompleted event.
     * 
     * @param result The execution result.
     */
    void EmitReactionCompleted(const ExecutionResult& result);
    
    /**
     * @brief Emit a ReactionFailed event.
     * 
     * @param result The execution result with error information.
     */
    void EmitReactionFailed(const ExecutionResult& result);
    
    // ========================================================================
    // Lifecycle Events
    // ========================================================================
    
    /**
     * @brief Emit a RepositoryStarted event.
     */
    void EmitRepositoryStarted();
    
    /**
     * @brief Emit a RepositoryShuttingDown event.
     * 
     * @param reason Optional reason for shutdown.
     */
    void EmitRepositoryShuttingDown(const Maybe<std::string>& reason = {});
    
    /**
     * @brief Emit a RepositoryCompleted event.
     */
    void EmitRepositoryCompleted();
    
    /**
     * @brief Emit a RepositoryFailed event.
     * 
     * @param reason Reason for failure.
     */
    void EmitRepositoryFailed(const std::string& reason);
    
    // ========================================================================
    // Statistics
    // ========================================================================
    
    /**
     * @brief Get the total number of events emitted.
     * 
     * Thread-safe.
     * 
     * @return Total event count.
     */
    uint64_t GetEventCount() const noexcept;
    
    /**
     * @brief Reset the event counter.
     * 
     * Thread-safe. Note: This does not affect the event IDs, which continue
     * to increment monotonically.
     */
    void ResetEventCount() noexcept;

private:
    /**
     * @brief Generate the next event ID.
     * 
     * Thread-safe using atomic increment.
     * 
     * @return A unique event ID.
     */
    uint64_t NextEventID() noexcept;
    
    /**
     * @brief Emit an event to the logger.
     * 
     * If no logger is set, this is a no-op. Thread-safe.
     * 
     * @param event The event to emit.
     */
    void EmitEvent(const RuntimeEvent& event);
    
    Pointer<EventLogger> logger_;
    std::atomic<uint64_t> event_counter_{0};
    std::atomic<uint64_t> total_events_{0};
    mutable std::mutex mutex_;
};

}  // namespace reactor
