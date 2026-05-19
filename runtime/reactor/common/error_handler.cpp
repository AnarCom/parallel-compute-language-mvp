#include "error_handler.hpp"

#include <sstream>
#include <stdexcept>
#include <thread>

namespace reactor {

// ============================================================================
// ErrorPolicy String Conversion
// ============================================================================

std::string ToString(ErrorPolicy policy) {
    switch (policy) {
        case ErrorPolicy::FailFast:
            return "FailFast";
        case ErrorPolicy::IsolateReaction:
            return "IsolateReaction";
        case ErrorPolicy::RetryOnce:
            return "RetryOnce";
        case ErrorPolicy::RetryWithBackoff:
            return "RetryWithBackoff";
        default:
            return "Unknown";
    }
}

// ============================================================================
// ErrorHandler Implementation
// ============================================================================

ErrorHandler::ErrorHandler(ErrorPolicy policy)
    : policy_(policy) {
}

void ErrorHandler::SetPolicy(ErrorPolicy policy) noexcept {
    policy_.store(policy, std::memory_order_release);
}

ErrorPolicy ErrorHandler::GetPolicy() const noexcept {
    return policy_.load(std::memory_order_acquire);
}

ExecutionResult ErrorHandler::HandleReactionError(
    const ScheduledReaction& reaction,
    const std::exception_ptr& exception) {
    
    // Extract error message from exception
    std::string error_message = ExtractErrorMessage(exception);
    
    // Get current policy
    ErrorPolicy current_policy = GetPolicy();
    
    // Handle based on policy
    switch (current_policy) {
        case ErrorPolicy::FailFast: {
            // Create failure result
            ExecutionResult result = CreateFailureResult(
                reaction, exception, error_message);
            
            // Store the error
            StoreFailedReaction(result);
            
            // Throw to terminate runtime
            std::ostringstream oss;
            oss << "Reaction " << reaction.reaction_id 
                << " failed with FailFast policy: " << error_message;
            throw std::runtime_error(oss.str());
        }
        
        case ErrorPolicy::IsolateReaction: {
            // Create failure result
            ExecutionResult result = CreateFailureResult(
                reaction, exception, error_message);
            
            // Store the error and continue
            StoreFailedReaction(result);
            
            return result;
        }
        
        case ErrorPolicy::RetryOnce: {
            // Attempt one retry
            bool retry_succeeded = AttemptRetry(reaction, 1);
            
            if (retry_succeeded) {
                // Retry succeeded, create success result
                auto now = std::chrono::steady_clock::now();
                ExecutionResult result;
                result.reaction_id = reaction.reaction_id;
                result.status = ExecutionStatus::Success;
                result.started_at = now;
                result.completed_at = now;
                result.duration = std::chrono::milliseconds(0);
                return result;
            } else {
                // Retry failed, isolate the reaction
                ExecutionResult result = CreateFailureResult(
                    reaction, exception, 
                    error_message + " (retry failed)");
                StoreFailedReaction(result);
                return result;
            }
        }
        
        case ErrorPolicy::RetryWithBackoff: {
            // Attempt multiple retries with exponential backoff
            for (int attempt = 1; attempt <= kMaxRetries; ++attempt) {
                // Calculate and wait for backoff delay
                if (attempt > 1) {
                    auto delay = CalculateBackoffDelay(attempt - 1);
                    std::this_thread::sleep_for(delay);
                }
                
                // Attempt retry
                bool retry_succeeded = AttemptRetry(reaction, attempt);
                
                if (retry_succeeded) {
                    // Retry succeeded, create success result
                    auto now = std::chrono::steady_clock::now();
                    ExecutionResult result;
                    result.reaction_id = reaction.reaction_id;
                    result.status = ExecutionStatus::Success;
                    result.started_at = now;
                    result.completed_at = now;
                    result.duration = std::chrono::milliseconds(0);
                    return result;
                }
            }
            
            // All retries failed, isolate the reaction
            std::ostringstream oss;
            oss << error_message << " (all " << kMaxRetries << " retries failed)";
            ExecutionResult result = CreateFailureResult(
                reaction, exception, oss.str());
            StoreFailedReaction(result);
            return result;
        }
        
        default: {
            // Unknown policy, treat as IsolateReaction
            ExecutionResult result = CreateFailureResult(
                reaction, exception, error_message);
            StoreFailedReaction(result);
            return result;
        }
    }
}

bool ErrorHandler::HasErrors() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    return !failed_reactions_.empty();
}

std::vector<ExecutionResult> ErrorHandler::GetFailedReactions() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return failed_reactions_;  // Return a copy
}

void ErrorHandler::ClearErrors() noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    failed_reactions_.clear();
}

size_t ErrorHandler::GetErrorCount() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    return failed_reactions_.size();
}

// ============================================================================
// Private Helper Methods
// ============================================================================

std::string ErrorHandler::ExtractErrorMessage(
    const std::exception_ptr& exception) const noexcept {
    
    if (!exception) {
        return "Unknown error (null exception pointer)";
    }
    
    try {
        std::rethrow_exception(exception);
    } catch (const std::exception& e) {
        // Standard exception with what() message
        return std::string("Exception: ") + e.what();
    } catch (const std::string& s) {
        // String exception
        return std::string("String exception: ") + s;
    } catch (const char* s) {
        // C-string exception
        return std::string("C-string exception: ") + s;
    } catch (...) {
        // Unknown exception type
        return "Unknown exception type";
    }
}

ExecutionResult ErrorHandler::CreateFailureResult(
    const ScheduledReaction& reaction,
    const std::exception_ptr& exception,
    const std::string& error_message) const {
    
    auto now = std::chrono::steady_clock::now();
    
    ExecutionResult result;
    result.reaction_id = reaction.reaction_id;
    result.status = ExecutionStatus::Failed;
    result.error_message = error_message;
    result.exception = exception;
    result.started_at = reaction.scheduled_at;
    result.completed_at = now;
    
    // Calculate duration
    auto duration_ns = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - reaction.scheduled_at);
    result.duration = duration_ns;
    
    return result;
}

void ErrorHandler::StoreFailedReaction(const ExecutionResult& result) {
    std::lock_guard<std::mutex> lock(mutex_);
    failed_reactions_.push_back(result);
}

bool ErrorHandler::AttemptRetry(
    const ScheduledReaction& reaction,
    int attempt_number) {
    
    // NOTE: This is a placeholder implementation for retry logic.
    // In a full implementation, this would:
    // 1. Re-execute the reaction's runnable with the same inputs
    // 2. Catch any exceptions and return false if it fails again
    // 3. Return true if the retry succeeds
    //
    // For now, we always return false (retry not implemented).
    // This means RetryOnce and RetryWithBackoff will behave like
    // IsolateReaction until retry execution is implemented.
    
    // TODO: Implement actual retry logic
    // This would require:
    // - Access to the runnable execution context
    // - Ability to re-invoke runnable->Run() with the same arguments
    // - Proper exception handling around the retry attempt
    
    (void)reaction;       // Suppress unused parameter warning
    (void)attempt_number; // Suppress unused parameter warning
    
    return false;  // Retry not yet implemented
}

std::chrono::milliseconds ErrorHandler::CalculateBackoffDelay(
    int attempt_number) const noexcept {
    
    // Exponential backoff: delay = base_delay * 2^(attempt - 1)
    // attempt 1: 100ms
    // attempt 2: 200ms
    // attempt 3: 400ms
    // etc.
    
    if (attempt_number <= 0) {
        return std::chrono::milliseconds(0);
    }
    
    // Calculate 2^(attempt_number - 1)
    int multiplier = 1 << (attempt_number - 1);
    
    // Cap the multiplier to prevent overflow
    constexpr int kMaxMultiplier = 64;  // Max 6.4 seconds
    if (multiplier > kMaxMultiplier) {
        multiplier = kMaxMultiplier;
    }
    
    return std::chrono::milliseconds(kBaseBackoffMs * multiplier);
}

}  // namespace reactor
