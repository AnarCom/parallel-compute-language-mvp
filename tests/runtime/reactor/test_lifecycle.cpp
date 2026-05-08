#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <chrono>

#include "runtime/reactor/common/lifecycle.hpp"

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

// Test ChannelLifecycle state transitions
int test_channel_lifecycle_basic_transitions() {
    std::cout << "\n=== Test: Channel Lifecycle Basic Transitions ===" << std::endl;
    
    ChannelLifecycle lifecycle;
    
    // Initial state should be Active
    TEST_ASSERT(lifecycle.GetState() == ChannelState::Active, 
                "Initial state should be Active");
    TEST_ASSERT(lifecycle.IsActive(), "IsActive() should return true initially");
    TEST_ASSERT(lifecycle.CanAcceptMessages(), "Should accept messages initially");
    TEST_ASSERT(lifecycle.CanConsumeMessages(), "Should consume messages initially");
    TEST_PASS("Initial state is Active");
    
    // Transition to Closing
    lifecycle.Close();
    TEST_ASSERT(lifecycle.GetState() == ChannelState::Closing, 
                "State should be Closing after Close()");
    TEST_ASSERT(!lifecycle.IsActive(), "IsActive() should return false after Close()");
    TEST_ASSERT(!lifecycle.CanAcceptMessages(), "Should not accept messages after Close()");
    TEST_ASSERT(lifecycle.CanConsumeMessages(), "Should still consume messages in Closing");
    TEST_PASS("Transition to Closing");
    
    // Transition to Draining
    lifecycle.OnLastReferenceDropped();
    TEST_ASSERT(lifecycle.GetState() == ChannelState::Draining, 
                "State should be Draining after OnLastReferenceDropped()");
    TEST_ASSERT(!lifecycle.CanAcceptMessages(), "Should not accept messages in Draining");
    TEST_ASSERT(lifecycle.CanConsumeMessages(), "Should still consume messages in Draining");
    TEST_PASS("Transition to Draining");
    
    // Transition to Closed
    lifecycle.OnQueueEmpty();
    TEST_ASSERT(lifecycle.GetState() == ChannelState::Closed, 
                "State should be Closed after OnQueueEmpty()");
    TEST_ASSERT(lifecycle.IsClosed(), "IsClosed() should return true");
    TEST_ASSERT(!lifecycle.CanAcceptMessages(), "Should not accept messages when Closed");
    TEST_ASSERT(!lifecycle.CanConsumeMessages(), "Should not consume messages when Closed");
    TEST_PASS("Transition to Closed");
    
    return 0;
}

// Test alternative transition path: Active -> Draining -> Closed
int test_channel_lifecycle_draining_path() {
    std::cout << "\n=== Test: Channel Lifecycle Draining Path ===" << std::endl;
    
    ChannelLifecycle lifecycle;
    
    // Active -> Draining (last reference dropped before explicit close)
    lifecycle.OnLastReferenceDropped();
    TEST_ASSERT(lifecycle.GetState() == ChannelState::Draining, 
                "State should be Draining after OnLastReferenceDropped()");
    TEST_PASS("Active -> Draining transition");
    
    // Draining -> Closed
    lifecycle.OnQueueEmpty();
    TEST_ASSERT(lifecycle.GetState() == ChannelState::Closed, 
                "State should be Closed after OnQueueEmpty()");
    TEST_PASS("Draining -> Closed transition");
    
    return 0;
}

// Test idempotent operations (calling same transition multiple times)
int test_channel_lifecycle_idempotent() {
    std::cout << "\n=== Test: Channel Lifecycle Idempotent Operations ===" << std::endl;
    
    ChannelLifecycle lifecycle;
    
    // Multiple Close() calls should be idempotent
    lifecycle.Close();
    auto state1 = lifecycle.GetState();
    lifecycle.Close();
    auto state2 = lifecycle.GetState();
    TEST_ASSERT(state1 == state2, "Multiple Close() calls should be idempotent");
    TEST_PASS("Close() is idempotent");
    
    // Multiple OnLastReferenceDropped() calls should be idempotent
    lifecycle.OnLastReferenceDropped();
    state1 = lifecycle.GetState();
    lifecycle.OnLastReferenceDropped();
    state2 = lifecycle.GetState();
    TEST_ASSERT(state1 == state2, "Multiple OnLastReferenceDropped() calls should be idempotent");
    TEST_PASS("OnLastReferenceDropped() is idempotent");
    
    // Multiple OnQueueEmpty() calls should be idempotent
    lifecycle.OnQueueEmpty();
    state1 = lifecycle.GetState();
    lifecycle.OnQueueEmpty();
    state2 = lifecycle.GetState();
    TEST_ASSERT(state1 == state2, "Multiple OnQueueEmpty() calls should be idempotent");
    TEST_PASS("OnQueueEmpty() is idempotent");
    
    return 0;
}

// Test thread safety of ChannelLifecycle
int test_channel_lifecycle_thread_safety() {
    std::cout << "\n=== Test: Channel Lifecycle Thread Safety ===" << std::endl;
    
    ChannelLifecycle lifecycle;
    
    // Launch multiple threads that try to transition the state
    std::vector<std::thread> threads;
    const int num_threads = 10;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&lifecycle]() {
            lifecycle.Close();
            lifecycle.OnLastReferenceDropped();
            lifecycle.OnQueueEmpty();
            // Read state multiple times
            for (int j = 0; j < 100; ++j) {
                auto state = lifecycle.GetState();
                (void)state; // Suppress unused warning
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Final state should be Closed
    TEST_ASSERT(lifecycle.GetState() == ChannelState::Closed, 
                "Final state should be Closed after concurrent transitions");
    TEST_PASS("Thread-safe state transitions");
    
    return 0;
}

// Test RepositoryLifecycle state transitions
int test_repository_lifecycle_basic_transitions() {
    std::cout << "\n=== Test: Repository Lifecycle Basic Transitions ===" << std::endl;
    
    RepositoryLifecycle lifecycle;
    
    // Initial state should be Initializing
    TEST_ASSERT(lifecycle.GetState() == RepositoryState::Initializing, 
                "Initial state should be Initializing");
    TEST_ASSERT(!lifecycle.IsRunning(), "IsRunning() should return false initially");
    TEST_ASSERT(!lifecycle.ShouldTerminate(), "ShouldTerminate() should return false initially");
    TEST_PASS("Initial state is Initializing");
    
    // Transition to Running
    lifecycle.Start();
    TEST_ASSERT(lifecycle.GetState() == RepositoryState::Running, 
                "State should be Running after Start()");
    TEST_ASSERT(lifecycle.IsRunning(), "IsRunning() should return true after Start()");
    TEST_ASSERT(!lifecycle.ShouldTerminate(), "ShouldTerminate() should return false when Running");
    TEST_PASS("Transition to Running");
    
    // Transition to ShuttingDown
    lifecycle.BeginShutdown();
    TEST_ASSERT(lifecycle.GetState() == RepositoryState::ShuttingDown, 
                "State should be ShuttingDown after BeginShutdown()");
    TEST_ASSERT(!lifecycle.IsRunning(), "IsRunning() should return false when ShuttingDown");
    TEST_ASSERT(lifecycle.ShouldTerminate(), "ShouldTerminate() should return true when ShuttingDown");
    TEST_PASS("Transition to ShuttingDown");
    
    // Transition to Completed
    lifecycle.MarkCompleted();
    TEST_ASSERT(lifecycle.GetState() == RepositoryState::Completed, 
                "State should be Completed after MarkCompleted()");
    TEST_ASSERT(lifecycle.ShouldTerminate(), "ShouldTerminate() should return true when Completed");
    TEST_PASS("Transition to Completed");
    
    return 0;
}

// Test RepositoryLifecycle failure path
int test_repository_lifecycle_failure_path() {
    std::cout << "\n=== Test: Repository Lifecycle Failure Path ===" << std::endl;
    
    RepositoryLifecycle lifecycle;
    
    lifecycle.Start();
    TEST_ASSERT(lifecycle.IsRunning(), "Should be running");
    
    // Mark as failed with a reason
    std::string failure_reason = "Connection lost";
    lifecycle.MarkFailed(failure_reason);
    
    TEST_ASSERT(lifecycle.GetState() == RepositoryState::Failed, 
                "State should be Failed after MarkFailed()");
    TEST_ASSERT(lifecycle.ShouldTerminate(), "ShouldTerminate() should return true when Failed");
    
    auto reason = lifecycle.GetFailureReason();
    TEST_ASSERT(reason.has_value(), "Failure reason should be present");
    TEST_ASSERT(reason.value() == failure_reason, "Failure reason should match");
    TEST_PASS("Failure path with reason");
    
    return 0;
}

// Test RepositoryLifecycle thread safety
int test_repository_lifecycle_thread_safety() {
    std::cout << "\n=== Test: Repository Lifecycle Thread Safety ===" << std::endl;
    
    RepositoryLifecycle lifecycle;
    
    // Launch multiple threads that try to transition the state
    std::vector<std::thread> threads;
    const int num_threads = 10;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&lifecycle, i]() {
            lifecycle.Start();
            lifecycle.BeginShutdown();
            if (i % 2 == 0) {
                lifecycle.MarkCompleted();
            } else {
                lifecycle.MarkFailed("Test failure");
            }
            // Read state multiple times
            for (int j = 0; j < 100; ++j) {
                auto state = lifecycle.GetState();
                (void)state; // Suppress unused warning
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Final state should be either Completed or Failed
    auto final_state = lifecycle.GetState();
    TEST_ASSERT(final_state == RepositoryState::Completed || 
                final_state == RepositoryState::Failed, 
                "Final state should be Completed or Failed");
    TEST_PASS("Thread-safe state transitions");
    
    return 0;
}

// Test ToString functions
int test_to_string_functions() {
    std::cout << "\n=== Test: ToString Functions ===" << std::endl;
    
    // Test ChannelState ToString
    TEST_ASSERT(ToString(ChannelState::Active) == "Active", "ChannelState::Active ToString");
    TEST_ASSERT(ToString(ChannelState::Closing) == "Closing", "ChannelState::Closing ToString");
    TEST_ASSERT(ToString(ChannelState::Draining) == "Draining", "ChannelState::Draining ToString");
    TEST_ASSERT(ToString(ChannelState::Closed) == "Closed", "ChannelState::Closed ToString");
    TEST_PASS("ChannelState ToString");
    
    // Test RepositoryState ToString
    TEST_ASSERT(ToString(RepositoryState::Initializing) == "Initializing", 
                "RepositoryState::Initializing ToString");
    TEST_ASSERT(ToString(RepositoryState::Running) == "Running", 
                "RepositoryState::Running ToString");
    TEST_ASSERT(ToString(RepositoryState::ShuttingDown) == "ShuttingDown", 
                "RepositoryState::ShuttingDown ToString");
    TEST_ASSERT(ToString(RepositoryState::Completed) == "Completed", 
                "RepositoryState::Completed ToString");
    TEST_ASSERT(ToString(RepositoryState::Failed) == "Failed", 
                "RepositoryState::Failed ToString");
    TEST_PASS("RepositoryState ToString");
    
    return 0;
}

// Test edge case: invalid transitions
int test_invalid_transitions() {
    std::cout << "\n=== Test: Invalid Transitions ===" << std::endl;
    
    // Try to transition from Closed back to Active (should be ignored)
    ChannelLifecycle lifecycle;
    lifecycle.Close();
    lifecycle.OnLastReferenceDropped();
    lifecycle.OnQueueEmpty();
    TEST_ASSERT(lifecycle.IsClosed(), "Should be closed");
    
    // Try to call Close() again - should remain Closed
    lifecycle.Close();
    TEST_ASSERT(lifecycle.IsClosed(), "Should remain closed");
    TEST_PASS("Invalid transitions are ignored");
    
    return 0;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Lifecycle Model Tests" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int result = 0;
    
    result |= test_channel_lifecycle_basic_transitions();
    result |= test_channel_lifecycle_draining_path();
    result |= test_channel_lifecycle_idempotent();
    result |= test_channel_lifecycle_thread_safety();
    result |= test_repository_lifecycle_basic_transitions();
    result |= test_repository_lifecycle_failure_path();
    result |= test_repository_lifecycle_thread_safety();
    result |= test_to_string_functions();
    result |= test_invalid_transitions();
    
    if (result == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  All Lifecycle Tests PASSED!" << std::endl;
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Some Lifecycle Tests FAILED!" << std::endl;
        std::cout << "========================================" << std::endl;
    }
    
    return result;
}
