#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <exception>
#include <string>
#include <vector>

#include "helpers.hpp"
#include "type_system.hpp"

namespace reactor {

// Forward declarations
class Runnable;
struct Match;
struct Firing;
struct ScheduledReaction;
struct ExecutionResult;
enum class ExecutionStatus;

// Type aliases for convenience
using IDs = std::vector<uint64_t>;

/**
 * @brief Thread-safe ID generator for firing model entities.
 * 
 * Provides unique IDs for matches, firings, and reactions using atomic counters.
 * This is a singleton class accessed via Instance().
 * 
 * Thread Safety: All methods are thread-safe using atomic operations.
 */
class IDGenerator {
public:
    /**
     * @brief Get the singleton instance of IDGenerator.
     * @return Reference to the global IDGenerator instance.
     */
    static IDGenerator& Instance();

    /**
     * @brief Generate a unique match ID.
     * @return A unique 64-bit match identifier.
     */
    uint64_t NextMatchID();

    /**
     * @brief Generate a unique firing ID.
     * @return A unique 64-bit firing identifier.
     */
    uint64_t NextFiringID();

    /**
     * @brief Generate a unique reaction ID.
     * @return A unique 64-bit reaction identifier.
     */
    uint64_t NextReactionID();

private:
    IDGenerator() = default;
    ~IDGenerator() = default;
    
    // Prevent copying and moving
    IDGenerator(const IDGenerator&) = delete;
    IDGenerator& operator=(const IDGenerator&) = delete;
    IDGenerator(IDGenerator&&) = delete;
    IDGenerator& operator=(IDGenerator&&) = delete;

    std::atomic<uint64_t> match_counter_{0};
    std::atomic<uint64_t> firing_counter_{0};
    std::atomic<uint64_t> reaction_counter_{0};
};

/**
 * @brief Represents a detected opportunity to fire a join-case.
 * 
 * A Match is created when all required input channels for a join-case have
 * messages available. It captures the moment of detection and identifies
 * which channels are involved.
 * 
 * Lifecycle: Match -> Firing (if committed) or discarded (if conditions change)
 */
struct Match {
    /**
     * @brief Unique identifier for this match.
     */
    uint64_t match_id;

    /**
     * @brief Identifier of the join-case that matched.
     */
    uint64_t join_case_id;

    /**
     * @brief IDs of the input channels involved in this match.
     * 
     * The order corresponds to the join-case input channel order.
     */
    IDs input_channel_ids;

    /**
     * @brief Timestamp when this match was detected.
     */
    std::chrono::steady_clock::time_point detected_at;

    /**
     * @brief Create a string representation of this match.
     * @return Human-readable description of the match.
     */
    std::string ToString() const;
};

/**
 * @brief Represents the atomic commitment of messages for execution.
 * 
 * A Firing represents the point of no return where messages are atomically
 * removed from input queues and committed to a reaction. This is the core
 * transactional unit in the firing model.
 * 
 * Lifecycle: Created from a Match, leads to ScheduledReaction
 */
struct Firing {
    /**
     * @brief Unique identifier for this firing.
     */
    uint64_t firing_id;

    /**
     * @brief The match that triggered this firing.
     */
    Match match;

    /**
     * @brief Messages atomically consumed from input channels.
     * 
     * These messages have been removed from their respective queues and
     * are now owned by this firing. The order corresponds to the
     * input_channel_ids in the match.
     */
    Objects consumed_messages;

    /**
     * @brief Context objects for the reaction.
     * 
     * Additional data passed to the reaction that is not consumed from channels.
     */
    Objects context;

    /**
     * @brief Identifier of the runnable (reaction code) to execute.
     */
    uint64_t runnable_id;

    /**
     * @brief Timestamp when this firing was committed.
     */
    std::chrono::steady_clock::time_point fired_at;

    /**
     * @brief Create a string representation of this firing.
     * @return Human-readable description of the firing.
     */
    std::string ToString() const;
};

/**
 * @brief Represents a reaction ready for execution.
 * 
 * A ScheduledReaction bridges the gap between the firing (scheduler) and
 * execution (worker threads). It contains all information needed to execute
 * the reaction, including a pointer to the actual runnable code.
 * 
 * Lifecycle: Created from a Firing, executed to produce ExecutionResult
 */
struct ScheduledReaction {
    /**
     * @brief Unique identifier for this reaction execution.
     */
    uint64_t reaction_id;

    /**
     * @brief The firing that created this scheduled reaction.
     */
    Firing firing;

    /**
     * @brief Pointer to the runnable code to execute.
     * 
     * This is a non-owning pointer. The runnable must remain valid
     * for the duration of the reaction execution.
     */
    Runnable* runnable;

    /**
     * @brief Timestamp when this reaction was scheduled.
     */
    std::chrono::steady_clock::time_point scheduled_at;

    /**
     * @brief Create a string representation of this scheduled reaction.
     * @return Human-readable description of the scheduled reaction.
     */
    std::string ToString() const;
};

/**
 * @brief Execution status of a reaction.
 */
enum class ExecutionStatus {
    /**
     * @brief Reaction completed successfully without errors.
     */
    Success,

    /**
     * @brief Reaction failed with an error or exception.
     */
    Failed,

    /**
     * @brief Reaction was cancelled before or during execution.
     */
    Cancelled
};

/**
 * @brief Convert ExecutionStatus to string representation.
 * @param status The execution status to convert.
 * @return String representation of the status.
 */
std::string ToString(ExecutionStatus status);

/**
 * @brief Represents the outcome of executing a reaction.
 * 
 * An ExecutionResult captures the complete outcome of a reaction execution,
 * including success/failure status, timing information, and error details
 * if the execution failed.
 * 
 * Lifecycle: Terminal state - created after reaction execution completes
 */
struct ExecutionResult {
    /**
     * @brief Identifier linking back to the ScheduledReaction.
     */
    uint64_t reaction_id;

    /**
     * @brief Execution status (Success, Failed, or Cancelled).
     */
    ExecutionStatus status;

    /**
     * @brief Error message if execution failed.
     * 
     * Contains a human-readable description of the error.
     * Only present when status is Failed.
     */
    Maybe<std::string> error_message;

    /**
     * @brief Exception pointer if an exception was thrown.
     * 
     * Captures the actual exception for later inspection or rethrowing.
     * Only present when status is Failed and an exception was caught.
     */
    Maybe<std::exception_ptr> exception;

    /**
     * @brief Timestamp when reaction execution started.
     */
    std::chrono::steady_clock::time_point started_at;

    /**
     * @brief Timestamp when reaction execution completed.
     */
    std::chrono::steady_clock::time_point completed_at;

    /**
     * @brief Duration of the reaction execution.
     * 
     * Calculated as (completed_at - started_at).
     */
    std::chrono::milliseconds duration;

    /**
     * @brief Check if the execution was successful.
     * @return true if status is Success, false otherwise.
     */
    bool IsSuccess() const noexcept;

    /**
     * @brief Check if the execution failed.
     * @return true if status is Failed, false otherwise.
     */
    bool IsFailed() const noexcept;

    /**
     * @brief Check if the execution was cancelled.
     * @return true if status is Cancelled, false otherwise.
     */
    bool IsCancelled() const noexcept;

    /**
     * @brief Create a string representation of this execution result.
     * @return Human-readable description of the execution result.
     */
    std::string ToString() const;
};

}  // namespace reactor
