#pragma once

#include <atomic>
#include <mutex>
#include <string>

#include "helpers.hpp"

namespace reactor {

/**
 * @brief Channel lifecycle states
 * 
 * Represents the lifecycle of a channel from creation to closure.
 * 
 * State Transitions:
 * - Active -> Closing: Close() called explicitly
 * - Active -> Draining: Last external reference dropped
 * - Active -> Closed: Close() called on empty channel
 * - Closing -> Draining: All pending sends complete
 * - Draining -> Closed: Queue becomes empty
 * 
 * @see ChannelLifecycle for state management
 */
enum class ChannelState {
    /**
     * @brief Channel is active and accepting messages
     * 
     * - Push() operations are allowed
     * - Messages can be consumed by join-cases
     * - Reference count > 1 OR queue not empty
     */
    Active,
    
    /**
     * @brief Channel is closing, no new messages accepted
     * 
     * - Close() has been called explicitly
     * - Push() operations will fail
     * - Existing messages still consumable
     * - Transitions to Draining when pending operations complete
     */
    Closing,
    
    /**
     * @brief Channel is draining existing messages
     * 
     * - Last external reference dropped (use_count == 1)
     * - No new messages accepted
     * - Existing messages still consumable
     * - Transitions to Closed when queue becomes empty
     */
    Draining,
    
    /**
     * @brief Channel is closed and can be garbage collected
     * 
     * - No messages in queue
     * - No external references
     * - Join-cases with this channel are removed
     * - Channel can be garbage collected
     */
    Closed
};

/**
 * @brief Repository lifecycle states
 * 
 * Represents the lifecycle of a runtime repository from initialization to completion.
 * 
 * State Transitions:
 * - Initializing -> Running: Run() called
 * - Running -> ShuttingDown: All work complete OR Shutdown() called
 * - Running -> Failed: Unrecoverable error
 * - ShuttingDown -> Completed: Graceful cleanup done
 * - ShuttingDown -> Failed: Cleanup error
 * 
 * @see RepositoryLifecycle for state management
 */
enum class RepositoryState {
    /**
     * @brief Repository created but not started
     * 
     * - Channels can be created
     * - Join-cases can be registered
     * - No execution happening
     */
    Initializing,
    
    /**
     * @brief Repository is running normally
     * 
     * - Main execution loop active
     * - Worker threads processing reactions
     * - Scheduler checking for matches
     * - Normal operation mode
     */
    Running,
    
    /**
     * @brief Repository is shutting down gracefully
     * 
     * - Triggered when: all channels closed + no pending work, OR explicit Shutdown() call
     * - No new join-cases accepted
     * - Existing reactions complete
     * - Graceful cleanup in progress
     */
    ShuttingDown,
    
    /**
     * @brief Repository completed successfully
     * 
     * - All work finished successfully
     * - All channels closed
     * - All threads joined
     * - Clean exit
     */
    Completed,
    
    /**
     * @brief Repository failed with error
     * 
     * - Unrecoverable error occurred
     * - Error state captured
     * - Resources cleaned up (best effort)
     * - Error available for inspection
     */
    Failed
};

/**
 * @brief Thread-safe channel lifecycle state machine
 * 
 * Manages the lifecycle of a channel with atomic state transitions.
 * All state transitions are thread-safe and follow the defined state machine.
 * 
 * Thread Safety:
 * - All methods are thread-safe
 * - State transitions use atomic operations
 * - Mutex protects complex state changes
 * 
 * Example Usage:
 * @code
 * ChannelLifecycle lifecycle;
 * 
 * // Check if channel can accept messages
 * if (lifecycle.CanAcceptMessages()) {
 *     // Push message
 * }
 * 
 * // Close channel
 * lifecycle.Close();
 * 
 * // Check if closed
 * if (lifecycle.IsClosed()) {
 *     // Cleanup
 * }
 * @endcode
 */
class ChannelLifecycle {
public:
    /**
     * @brief Construct a new channel lifecycle in Active state
     */
    ChannelLifecycle();
    
    /**
     * @brief Get the current state
     * 
     * @return Current channel state
     * 
     * Thread Safety: Safe to call from any thread
     */
    ChannelState GetState() const noexcept;
    
    /**
     * @brief Check if channel can accept new messages
     * 
     * @return true if state is Active, false otherwise
     * 
     * Thread Safety: Safe to call from any thread
     */
    bool CanAcceptMessages() const noexcept;
    
    /**
     * @brief Check if channel can consume existing messages
     * 
     * @return true if state is Active, Closing, or Draining, false if Closed
     * 
     * Thread Safety: Safe to call from any thread
     */
    bool CanConsumeMessages() const noexcept;
    
    /**
     * @brief Transition to Closing state
     * 
     * Valid transitions:
     * - Active -> Closing
     * - Active -> Closed (if queue is empty)
     * 
     * Invalid transitions are ignored (idempotent).
     * 
     * Thread Safety: Safe to call from any thread
     */
    void Close() noexcept;
    
    /**
     * @brief Signal that last external reference was dropped
     * 
     * Valid transitions:
     * - Active -> Draining
     * - Closing -> Draining
     * 
     * Invalid transitions are ignored (idempotent).
     * 
     * Thread Safety: Safe to call from any thread
     */
    void OnLastReferenceDropped() noexcept;
    
    /**
     * @brief Signal that queue became empty
     * 
     * Valid transitions:
     * - Draining -> Closed
     * - Closing -> Closed
     * 
     * Invalid transitions are ignored (idempotent).
     * 
     * Thread Safety: Safe to call from any thread
     */
    void OnQueueEmpty() noexcept;
    
    /**
     * @brief Check if channel is in Active state
     * 
     * @return true if Active, false otherwise
     * 
     * Thread Safety: Safe to call from any thread
     */
    bool IsActive() const noexcept;
    
    /**
     * @brief Check if channel is in Closed state
     * 
     * @return true if Closed, false otherwise
     * 
     * Thread Safety: Safe to call from any thread
     */
    bool IsClosed() const noexcept;
    
private:
    /**
     * @brief Current state (atomic for lock-free reads)
     */
    std::atomic<ChannelState> state_;
    
    /**
     * @brief Mutex for complex state transitions
     */
    mutable std::mutex mutex_;
};

/**
 * @brief Thread-safe repository lifecycle state machine
 * 
 * Manages the lifecycle of a runtime repository with atomic state transitions.
 * All state transitions are thread-safe and follow the defined state machine.
 * 
 * Thread Safety:
 * - All methods are thread-safe
 * - State transitions use atomic operations
 * - Mutex protects failure reason updates
 * 
 * Example Usage:
 * @code
 * RepositoryLifecycle lifecycle;
 * 
 * // Start repository
 * lifecycle.Start();
 * 
 * // Check if running
 * if (lifecycle.IsRunning()) {
 *     // Process work
 * }
 * 
 * // Shutdown
 * lifecycle.BeginShutdown();
 * lifecycle.MarkCompleted();
 * 
 * // Or handle failure
 * lifecycle.MarkFailed("Connection lost");
 * auto reason = lifecycle.GetFailureReason();
 * @endcode
 */
class RepositoryLifecycle {
public:
    /**
     * @brief Construct a new repository lifecycle in Initializing state
     */
    RepositoryLifecycle();
    
    /**
     * @brief Get the current state
     * 
     * @return Current repository state
     * 
     * Thread Safety: Safe to call from any thread
     */
    RepositoryState GetState() const noexcept;
    
    /**
     * @brief Transition to Running state
     * 
     * Valid transitions:
     * - Initializing -> Running
     * 
     * Invalid transitions are ignored (idempotent).
     * 
     * Thread Safety: Safe to call from any thread
     */
    void Start() noexcept;
    
    /**
     * @brief Transition to ShuttingDown state
     * 
     * Valid transitions:
     * - Running -> ShuttingDown
     * 
     * Invalid transitions are ignored (idempotent).
     * 
     * Thread Safety: Safe to call from any thread
     */
    void BeginShutdown() noexcept;
    
    /**
     * @brief Transition to Completed state
     * 
     * Valid transitions:
     * - ShuttingDown -> Completed
     * 
     * Invalid transitions are ignored (idempotent).
     * 
     * Thread Safety: Safe to call from any thread
     */
    void MarkCompleted() noexcept;
    
    /**
     * @brief Transition to Failed state with reason
     * 
     * Valid transitions:
     * - Any state -> Failed
     * 
     * The failure reason is stored and can be retrieved later.
     * 
     * @param reason Human-readable failure reason
     * 
     * Thread Safety: Safe to call from any thread
     */
    void MarkFailed(std::string reason) noexcept;
    
    /**
     * @brief Check if repository is in Running state
     * 
     * @return true if Running, false otherwise
     * 
     * Thread Safety: Safe to call from any thread
     */
    bool IsRunning() const noexcept;
    
    /**
     * @brief Check if repository should terminate
     * 
     * @return true if state is ShuttingDown, Completed, or Failed
     * 
     * Thread Safety: Safe to call from any thread
     */
    bool ShouldTerminate() const noexcept;
    
    /**
     * @brief Get the failure reason if in Failed state
     * 
     * @return Maybe containing failure reason if Failed, empty otherwise
     * 
     * Thread Safety: Safe to call from any thread
     */
    Maybe<std::string> GetFailureReason() const noexcept;
    
private:
    /**
     * @brief Current state (atomic for lock-free reads)
     */
    std::atomic<RepositoryState> state_;
    
    /**
     * @brief Failure reason (only set in Failed state)
     */
    Maybe<std::string> failure_reason_;
    
    /**
     * @brief Mutex for failure reason updates
     */
    mutable std::mutex mutex_;
};

/**
 * @brief Convert ChannelState to string representation
 * 
 * @param state Channel state to convert
 * @return String representation ("Active", "Closing", "Draining", "Closed")
 */
std::string ToString(ChannelState state);

/**
 * @brief Convert RepositoryState to string representation
 * 
 * @param state Repository state to convert
 * @return String representation ("Initializing", "Running", "ShuttingDown", "Completed", "Failed")
 */
std::string ToString(RepositoryState state);

}  // namespace reactor
