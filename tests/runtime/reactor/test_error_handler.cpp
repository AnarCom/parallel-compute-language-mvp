#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <chrono>
#include <stdexcept>

#include "runtime/reactor/common/error_handler.hpp"

using namespace reactor;

// Simple test assertion helper
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "FAIL: " << message << std::endl; \
            return 1; \
        } \
    } while (0)

#define TEST_PASS(message) \
    std::cout << "PASS: " << message << std::endl

// Helper to create a test ScheduledReaction
ScheduledReaction CreateTestReaction(uint64_t reaction_id) {
    Match match;
    match.match_id = 1;
    match.join_case_id = 1;
    match.input_channel_ids = {1};
    match.detected_at = std::chrono::steady_clock::now();
    
    Firing firing;
    firing.firing_id = 1;
    firing.match = match;
    firing.consumed_messages = {};
    firing.context = {};
    firing.runnable_id = 1;
    firing.fired_at = std::chrono::steady_clock::now();
    
    ScheduledReaction reaction;
    reaction.reaction_id = reaction_id;
    reaction.firing = firing;
    reaction.runnable = nullptr;
    reaction.scheduled_at = std::chrono::steady_clock::now();
    
    return reaction;
}

// Test ErrorPolicy ToString
int test_error_policy_to_string() {
    std::cout << "\n=== Test: ErrorPolicy ToString ===" << std::endl;
    
    TEST_ASSERT(ToString(ErrorPolicy::FailFast) == "FailFast", 
                "ErrorPolicy::FailFast ToString");
    TEST_ASSERT(ToString(ErrorPolicy::IsolateReaction) == "IsolateReaction", 
                "ErrorPolicy::IsolateReaction ToString");
    TEST_ASSERT(ToString(ErrorPolicy::RetryOnce) == "RetryOnce", 
                "ErrorPolicy::RetryOnce ToString");
    TEST_ASSERT(ToString(ErrorPolicy::RetryWithBackoff) == "RetryWithBackoff", 
                "ErrorPolicy::RetryWithBackoff ToString");
    TEST_PASS("ErrorPolicy ToString");
    
    return 0;
}

// Test ErrorHandler basic functionality
int test_error_handler_basic() {
    std::cout << "\n=== Test: ErrorHandler Basic ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    TEST_ASSERT(handler.GetPolicy() == ErrorPolicy::IsolateReaction, 
                "Initial policy should be IsolateReaction");
    TEST_ASSERT(!handler.HasErrors(), "Should have no errors initially");
    TEST_ASSERT(handler.GetErrorCount() == 0, "Error count should be 0 initially");
    
    auto failed = handler.GetFailedReactions();
    TEST_ASSERT(failed.empty(), "Failed reactions list should be empty initially");
    TEST_PASS("ErrorHandler basic functionality");
    
    return 0;
}

// Test ErrorHandler policy changes
int test_error_handler_policy_change() {
    std::cout << "\n=== Test: ErrorHandler Policy Change ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    handler.SetPolicy(ErrorPolicy::FailFast);
    TEST_ASSERT(handler.GetPolicy() == ErrorPolicy::FailFast, 
                "Policy should change to FailFast");
    
    handler.SetPolicy(ErrorPolicy::RetryOnce);
    TEST_ASSERT(handler.GetPolicy() == ErrorPolicy::RetryOnce, 
                "Policy should change to RetryOnce");
    
    handler.SetPolicy(ErrorPolicy::RetryWithBackoff);
    TEST_ASSERT(handler.GetPolicy() == ErrorPolicy::RetryWithBackoff, 
                "Policy should change to RetryWithBackoff");
    TEST_PASS("ErrorHandler policy change");
    
    return 0;
}

// Test IsolateReaction policy
int test_isolate_reaction_policy() {
    std::cout << "\n=== Test: IsolateReaction Policy ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    auto reaction = CreateTestReaction(123);
    
    // Create an exception
    std::exception_ptr exception;
    try {
        throw std::runtime_error("Test error");
    } catch (...) {
        exception = std::current_exception();
    }
    
    // Handle the error - should not throw with IsolateReaction policy
    auto result = handler.HandleReactionError(reaction, exception);
    
    TEST_ASSERT(result.IsFailed(), "Result should indicate failure");
    TEST_ASSERT(result.reaction_id == 123, "Reaction ID should match");
    TEST_ASSERT(result.error_message.has_value(), "Error message should be present");
    TEST_ASSERT(result.error_message.value().find("Test error") != std::string::npos, 
                "Error message should contain exception message");
    
    TEST_ASSERT(handler.HasErrors(), "Handler should have errors");
    TEST_ASSERT(handler.GetErrorCount() == 1, "Error count should be 1");
    
    auto failed = handler.GetFailedReactions();
    TEST_ASSERT(failed.size() == 1, "Should have 1 failed reaction");
    TEST_ASSERT(failed[0].reaction_id == 123, "Failed reaction ID should match");
    TEST_PASS("IsolateReaction policy");
    
    return 0;
}

// Test FailFast policy
int test_fail_fast_policy() {
    std::cout << "\n=== Test: FailFast Policy ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::FailFast);
    
    auto reaction = CreateTestReaction(456);
    
    // Create an exception
    std::exception_ptr exception;
    try {
        throw std::runtime_error("Fatal error");
    } catch (...) {
        exception = std::current_exception();
    }
    
    // Handle the error - should throw with FailFast policy
    bool threw_exception = false;
    try {
        handler.HandleReactionError(reaction, exception);
    } catch (const std::runtime_error& e) {
        threw_exception = true;
        std::string msg = e.what();
        TEST_ASSERT(msg.find("Fatal error") != std::string::npos, 
                    "Exception message should contain original error");
    }
    
    TEST_ASSERT(threw_exception, "FailFast policy should throw exception");
    TEST_ASSERT(handler.HasErrors(), "Handler should have recorded the error before throwing");
    TEST_PASS("FailFast policy");
    
    return 0;
}

// Test RetryOnce policy
int test_retry_once_policy() {
    std::cout << "\n=== Test: RetryOnce Policy ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::RetryOnce);
    
    auto reaction = CreateTestReaction(789);
    
    // Create an exception
    std::exception_ptr exception;
    try {
        throw std::runtime_error("Transient error");
    } catch (...) {
        exception = std::current_exception();
    }
    
    // Handle the error - should attempt retry (though retry will fail in this test)
    auto result = handler.HandleReactionError(reaction, exception);
    
    TEST_ASSERT(result.IsFailed(), "Result should indicate failure after retry");
    TEST_ASSERT(handler.HasErrors(), "Handler should have errors");
    TEST_PASS("RetryOnce policy");
    
    return 0;
}

// Test RetryWithBackoff policy
int test_retry_with_backoff_policy() {
    std::cout << "\n=== Test: RetryWithBackoff Policy ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::RetryWithBackoff);
    
    auto reaction = CreateTestReaction(999);
    
    // Create an exception
    std::exception_ptr exception;
    try {
        throw std::runtime_error("Persistent error");
    } catch (...) {
        exception = std::current_exception();
    }
    
    // Handle the error - should attempt retries with backoff
    auto result = handler.HandleReactionError(reaction, exception);
    
    TEST_ASSERT(result.IsFailed(), "Result should indicate failure after retries");
    TEST_ASSERT(handler.HasErrors(), "Handler should have errors");
    TEST_PASS("RetryWithBackoff policy");
    
    return 0;
}

// Test multiple errors
int test_multiple_errors() {
    std::cout << "\n=== Test: Multiple Errors ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    // Handle multiple errors
    for (int i = 1; i <= 5; ++i) {
        auto reaction = CreateTestReaction(i);
        
        std::exception_ptr exception;
        try {
            throw std::runtime_error("Error " + std::to_string(i));
        } catch (...) {
            exception = std::current_exception();
        }
        
        handler.HandleReactionError(reaction, exception);
    }
    
    TEST_ASSERT(handler.GetErrorCount() == 5, "Should have 5 errors");
    
    auto failed = handler.GetFailedReactions();
    TEST_ASSERT(failed.size() == 5, "Should have 5 failed reactions");
    
    // Verify all reaction IDs are present
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(failed[i].reaction_id == i + 1, "Reaction IDs should match");
    }
    TEST_PASS("Multiple errors");
    
    return 0;
}

// Test ClearErrors
int test_clear_errors() {
    std::cout << "\n=== Test: Clear Errors ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    // Add some errors
    for (int i = 1; i <= 3; ++i) {
        auto reaction = CreateTestReaction(i);
        
        std::exception_ptr exception;
        try {
            throw std::runtime_error("Error " + std::to_string(i));
        } catch (...) {
            exception = std::current_exception();
        }
        
        handler.HandleReactionError(reaction, exception);
    }
    
    TEST_ASSERT(handler.HasErrors(), "Should have errors");
    TEST_ASSERT(handler.GetErrorCount() == 3, "Should have 3 errors");
    
    handler.ClearErrors();
    
    TEST_ASSERT(!handler.HasErrors(), "Should have no errors after clear");
    TEST_ASSERT(handler.GetErrorCount() == 0, "Error count should be 0 after clear");
    
    auto failed = handler.GetFailedReactions();
    TEST_ASSERT(failed.empty(), "Failed reactions list should be empty after clear");
    TEST_PASS("Clear errors");
    
    return 0;
}

// Test exception handling for different exception types
int test_different_exception_types() {
    std::cout << "\n=== Test: Different Exception Types ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    // Test std::runtime_error
    {
        auto reaction = CreateTestReaction(1);
        std::exception_ptr exception;
        try {
            throw std::runtime_error("Runtime error");
        } catch (...) {
            exception = std::current_exception();
        }
        auto result = handler.HandleReactionError(reaction, exception);
        TEST_ASSERT(result.error_message.value().find("Runtime error") != std::string::npos, 
                    "Should capture runtime_error message");
    }
    
    // Test std::logic_error
    {
        auto reaction = CreateTestReaction(2);
        std::exception_ptr exception;
        try {
            throw std::logic_error("Logic error");
        } catch (...) {
            exception = std::current_exception();
        }
        auto result = handler.HandleReactionError(reaction, exception);
        TEST_ASSERT(result.error_message.value().find("Logic error") != std::string::npos, 
                    "Should capture logic_error message");
    }
    
    // Test unknown exception
    {
        auto reaction = CreateTestReaction(3);
        std::exception_ptr exception;
        try {
            throw 42; // Non-standard exception
        } catch (...) {
            exception = std::current_exception();
        }
        auto result = handler.HandleReactionError(reaction, exception);
        TEST_ASSERT(result.error_message.has_value(), "Should have error message for unknown exception");
    }
    
    TEST_ASSERT(handler.GetErrorCount() == 3, "Should have 3 errors");
    TEST_PASS("Different exception types");
    
    return 0;
}

// Test thread safety
int test_error_handler_thread_safety() {
    std::cout << "\n=== Test: ErrorHandler Thread Safety ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    std::vector<std::thread> threads;
    const int num_threads = 10;
    const int errors_per_thread = 10;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&handler, i, errors_per_thread]() {
            for (int j = 0; j < errors_per_thread; ++j) {
                auto reaction = CreateTestReaction(i * errors_per_thread + j);
                
                std::exception_ptr exception;
                try {
                    throw std::runtime_error("Thread " + std::to_string(i) + 
                                           " Error " + std::to_string(j));
                } catch (...) {
                    exception = std::current_exception();
                }
                
                handler.HandleReactionError(reaction, exception);
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    TEST_ASSERT(handler.GetErrorCount() == num_threads * errors_per_thread, 
                "Should have all errors recorded");
    TEST_PASS("ErrorHandler thread safety");
    
    return 0;
}

// Test error result timing information
int test_error_result_timing() {
    std::cout << "\n=== Test: Error Result Timing ===" << std::endl;
    
    ErrorHandler handler(ErrorPolicy::IsolateReaction);
    
    auto reaction = CreateTestReaction(1);
    
    std::exception_ptr exception;
    try {
        throw std::runtime_error("Timing test error");
    } catch (...) {
        exception = std::current_exception();
    }
    
    auto result = handler.HandleReactionError(reaction, exception);
    
    TEST_ASSERT(result.started_at <= result.completed_at, 
                "Started time should be before or equal to completed time");
    TEST_ASSERT(result.duration.count() >= 0, "Duration should be non-negative");
    TEST_PASS("Error result timing");
    
    return 0;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Error Handler Tests" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int result = 0;
    
    result |= test_error_policy_to_string();
    result |= test_error_handler_basic();
    result |= test_error_handler_policy_change();
    result |= test_isolate_reaction_policy();
    result |= test_fail_fast_policy();
    result |= test_retry_once_policy();
    result |= test_retry_with_backoff_policy();
    result |= test_multiple_errors();
    result |= test_clear_errors();
    result |= test_different_exception_types();
    result |= test_error_handler_thread_safety();
    result |= test_error_result_timing();
    
    if (result == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  All Error Handler Tests PASSED!" << std::endl;
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Some Error Handler Tests FAILED!" << std::endl;
        std::cout << "========================================" << std::endl;
    }
    
    return result;
}
