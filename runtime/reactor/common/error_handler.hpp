#pragma once

#include <atomic>
#include <chrono>
#include <exception>
#include <mutex>
#include <string>
#include <vector>

#include "firing.hpp"
#include "helpers.hpp"

namespace reactor {

/**
 * @brief Error handling policy for reaction failures.
 * 
 * Defines how the runtime should respond when a reaction throws an exception
 * or otherwise fails during execution. Different policies provide different
 * trade-offs between fault tolerance and fail-fast behavior.
 */
enum class ErrorPolicy {
    /**
     * @brief Terminate the runtime immediately on first error.
     * 
     * When a reaction fails, the entire runtime is shut down and the error
     * is propagated. This is the strictest policy and ensures no errors
     * are silently ignored.
     * 
     * Use when: Correctness is critical and any error indicates a serious
     * problem that should halt execution.
     */
    FailFast,

    /**
     * @brief Isolate the failed reaction and continue with others.
     * 
     * When a reaction fails, the error is logged and stored, but other
     * reactions continue to execute normally. The failed reaction is not
     * retried. This provides maximum fault tolerance.
     * 
     * Use when: Individual reaction failures should not affect the entire
     * system, and you want to maximize availability.
     */
    IsolateReaction,

    /**
     * @brief Retry the failed reaction once before isolating.
     * 
     * When a reaction fails, it is retried exactly once. If the retry
     * succeeds, execution continues normally. If the retry also fails,
     * the error is logged and the reaction is isolated (not retried again).
     * 
     * Use when: Transient failures are possible (e.g., temporary resource
     * unavailability) and a single retry might succeed.
     */
    RetryOnce,

    /**
     * @brief Retry with exponential backoff before isolating.
     * 
     * When a reaction fails, it is retried multiple times with increasing
     * delays between attempts (exponential backoff). After a maximum number
     * of retries, the error is logged and the reaction is isolated.
     * 
     * Use when: Transient failures are common and you want to give the
     * system time to recover before giving up.
     */
    RetryWithBackoff
};

/**
 * @brief Convert ErrorPolicy to string representation.
 * @param policy The error policy to convert.
 * @return String representation of the policy.
 */
std::string ToString(ErrorPolicy policy);

/**
 * @brief Handles errors that occur during reaction execution.
 * 
 * The ErrorHandler is responsible for implementing error handling policies
 * when reactions fail. It stores information about failed reactions for
 * later inspection and implements different recovery strategies based on
 * the configured policy.
 * 
 * Thread Safety: All methods are thread-safe and can be called concurrently
 * from multiple worker threads.
 * 
 * Usage Example:
 * @code
 * ErrorHandler handler(ErrorPolicy::IsolateReaction);
 * 
 * // In reaction execution:
 * try {
 *     runnable->Run(args, context);
 * } catch (...) {
 *     handler.HandleReactionError(scheduled_reaction, std::current_exception());
 * }
 * 
 * // Later, check for errors:
 * if (handler.HasErrors()) {
 *     auto failed = handler.GetFailedReactions();
 *     for (const auto& result : failed) {
 *         std::cerr << "Reaction " << result.reaction_id 
 *                   << " failed: " << result.error_message.value() << std::endl;
 *     }
 * }
 * @endcode
 */
class ErrorHandler {
public:
    /**
     * @brief Construct an ErrorHandler with the specified policy.
     * 
     * @param policy The error handling policy to use (default: IsolateReaction).
     */
    explicit ErrorHandler(ErrorPolicy policy = ErrorPolicy::IsolateReaction);

    /**
     * @brief Destructor.
     */
    ~ErrorHandler() noexcept = default;

    // Prevent copying (ErrorHandler manages shared state)
    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;

    // Allow moving
    ErrorHandler(ErrorHandler&&) noexcept = default;
    ErrorHandler& operator=(ErrorHandler&&) noexcept = default;

    /**
     * @brief Set the error handling policy.
     * 
     * Changes the policy used for handling future errors. Does not affect
     * how previous errors were handled.
     * 
     * Thread Safety: Safe to call concurrently with other methods.
     * 
     * @param policy The new error policy to use.
     */
    void SetPolicy(ErrorPolicy policy) noexcept;

    /**
     * @brief Get the current error handling policy.
     * 
     * Thread Safety: Safe to call concurrently with other methods.
     * 
     * @return The currently configured error policy.
     */
    ErrorPolicy GetPolicy() const noexcept;

    /**
     * @brief Handle an error that occurred during reaction execution.
     * 
     * This is the main entry point for error handling. When a reaction fails,
     * this method should be called with the scheduled reaction and the exception
     * that was thrown. The method will:
     * 
     * 1. Extract error information from the exception
     * 2. Create an ExecutionResult with status Failed
     * 3. Apply the configured error policy (retry, isolate, or fail fast)
     * 4. Store the error for later inspection
     * 5. Optionally trigger runtime shutdown (for FailFast policy)
     * 
     * Thread Safety: Safe to call concurrently from multiple threads.
     * 
     * @param reaction The scheduled reaction that failed.
     * @param exception The exception that was caught during execution.
     * @return ExecutionResult describing the failure.
     * 
     * @throws std::runtime_error If policy is FailFast (after storing the error).
     */
    ExecutionResult HandleReactionError(
        const ScheduledReaction& reaction,
        const std::exception_ptr& exception);

    /**
     * @brief Check if any errors have been recorded.
     * 
     * Thread Safety: Safe to call concurrently with other methods.
     * 
     * @return true if at least one reaction has failed, false otherwise.
     */
    bool HasErrors() const noexcept;

    /**
     * @brief Get all failed reaction results.
     * 
     * Returns a copy of all ExecutionResult objects for reactions that failed.
     * This includes both reactions that were isolated and those that failed
     * after retries.
     * 
     * Thread Safety: Safe to call concurrently with other methods.
     * 
     * @return Vector of ExecutionResult objects for all failed reactions.
     */
    std::vector<ExecutionResult> GetFailedReactions() const;

    /**
     * @brief Clear all stored error information.
     * 
     * Removes all failed reaction results from storage. This does not change
     * the error policy.
     * 
     * Thread Safety: Safe to call concurrently with other methods.
     */
    void ClearErrors() noexcept;

    /**
     * @brief Get the number of failed reactions.
     * 
     * Thread Safety: Safe to call concurrently with other methods.
     * 
     * @return The total number of reactions that have failed.
     */
    size_t GetErrorCount() const noexcept;

private:
    /**
     * @brief Extract error message from an exception pointer.
     * 
     * Attempts to rethrow and catch the exception to extract a meaningful
     * error message. Handles std::exception and unknown exceptions.
     * 
     * @param exception The exception pointer to extract from.
     * @return Error message string.
     */
    std::string ExtractErrorMessage(const std::exception_ptr& exception) const noexcept;

    /**
     * @brief Create an ExecutionResult for a failed reaction.
     * 
     * @param reaction The scheduled reaction that failed.
     * @param exception The exception that was caught.
     * @param error_message Human-readable error message.
     * @return ExecutionResult with status Failed.
     */
    ExecutionResult CreateFailureResult(
        const ScheduledReaction& reaction,
        const std::exception_ptr& exception,
        const std::string& error_message) const;

    /**
     * @brief Store a failed reaction result.
     * 
     * Thread Safety: Acquires mutex lock.
     * 
     * @param result The execution result to store.
     */
    void StoreFailedReaction(const ExecutionResult& result);

    /**
     * @brief Attempt to retry a failed reaction (for retry policies).
     * 
     * This is a placeholder for future retry implementation. Currently,
     * retries are not fully implemented and this method returns false.
     * 
     * @param reaction The scheduled reaction to retry.
     * @param attempt_number Which retry attempt this is (1-based).
     * @return true if retry succeeded, false if retry failed or not attempted.
     */
    bool AttemptRetry(const ScheduledReaction& reaction, int attempt_number);

    /**
     * @brief Calculate backoff delay for retry attempts.
     * 
     * Uses exponential backoff: delay = base_delay * 2^(attempt - 1)
     * 
     * @param attempt_number Which retry attempt this is (1-based).
     * @return Duration to wait before retrying.
     */
    std::chrono::milliseconds CalculateBackoffDelay(int attempt_number) const noexcept;

    // Current error handling policy
    std::atomic<ErrorPolicy> policy_;

    // Storage for failed reactions
    std::vector<ExecutionResult> failed_reactions_;

    // Mutex protecting failed_reactions_
    mutable std::mutex mutex_;

    // Configuration for retry policies
    static constexpr int kMaxRetries = 3;
    static constexpr int kBaseBackoffMs = 100;  // 100ms base delay
};

}  // namespace reactor
