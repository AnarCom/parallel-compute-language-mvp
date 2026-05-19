#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <chrono>
#include <set>

#include "runtime/reactor/common/firing.hpp"

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

// Test IDGenerator uniqueness
int test_id_generator_uniqueness() {
    std::cout << "\n=== Test: ID Generator Uniqueness ===" << std::endl;
    
    auto& generator = IDGenerator::Instance();
    
    // Generate multiple IDs and ensure they're unique
    std::set<uint64_t> match_ids;
    std::set<uint64_t> firing_ids;
    std::set<uint64_t> reaction_ids;
    
    const int num_ids = 1000;
    
    for (int i = 0; i < num_ids; ++i) {
        match_ids.insert(generator.NextMatchID());
        firing_ids.insert(generator.NextFiringID());
        reaction_ids.insert(generator.NextReactionID());
    }
    
    TEST_ASSERT(match_ids.size() == num_ids, "All match IDs should be unique");
    TEST_ASSERT(firing_ids.size() == num_ids, "All firing IDs should be unique");
    TEST_ASSERT(reaction_ids.size() == num_ids, "All reaction IDs should be unique");
    TEST_PASS("ID uniqueness");
    
    return 0;
}

// Test IDGenerator thread safety
int test_id_generator_thread_safety() {
    std::cout << "\n=== Test: ID Generator Thread Safety ===" << std::endl;
    
    auto& generator = IDGenerator::Instance();
    
    std::vector<std::thread> threads;
    std::vector<std::vector<uint64_t>> thread_match_ids(10);
    std::vector<std::vector<uint64_t>> thread_firing_ids(10);
    std::vector<std::vector<uint64_t>> thread_reaction_ids(10);
    
    const int ids_per_thread = 100;
    
    // Launch threads that generate IDs concurrently
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&generator, &thread_match_ids, &thread_firing_ids, 
                              &thread_reaction_ids, i, ids_per_thread]() {
            for (int j = 0; j < ids_per_thread; ++j) {
                thread_match_ids[i].push_back(generator.NextMatchID());
                thread_firing_ids[i].push_back(generator.NextFiringID());
                thread_reaction_ids[i].push_back(generator.NextReactionID());
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Collect all IDs and check for uniqueness
    std::set<uint64_t> all_match_ids;
    std::set<uint64_t> all_firing_ids;
    std::set<uint64_t> all_reaction_ids;
    
    for (const auto& ids : thread_match_ids) {
        all_match_ids.insert(ids.begin(), ids.end());
    }
    for (const auto& ids : thread_firing_ids) {
        all_firing_ids.insert(ids.begin(), ids.end());
    }
    for (const auto& ids : thread_reaction_ids) {
        all_reaction_ids.insert(ids.begin(), ids.end());
    }
    
    const int total_ids = 10 * ids_per_thread;
    TEST_ASSERT(all_match_ids.size() == total_ids, 
                "All match IDs should be unique across threads");
    TEST_ASSERT(all_firing_ids.size() == total_ids, 
                "All firing IDs should be unique across threads");
    TEST_ASSERT(all_reaction_ids.size() == total_ids, 
                "All reaction IDs should be unique across threads");
    TEST_PASS("Thread-safe ID generation");
    
    return 0;
}

// Test Match creation and ToString
int test_match_creation() {
    std::cout << "\n=== Test: Match Creation ===" << std::endl;
    
    auto& generator = IDGenerator::Instance();
    
    Match match;
    match.match_id = generator.NextMatchID();
    match.join_case_id = 42;
    match.input_channel_ids = {1, 2, 3};
    match.detected_at = std::chrono::steady_clock::now();
    
    TEST_ASSERT(match.match_id > 0, "Match ID should be positive");
    TEST_ASSERT(match.join_case_id == 42, "Join case ID should match");
    TEST_ASSERT(match.input_channel_ids.size() == 3, "Should have 3 input channels");
    
    std::string str = match.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_ASSERT(str.find("Match") != std::string::npos, "ToString should contain 'Match'");
    TEST_PASS("Match creation and ToString");
    
    return 0;
}

// Test Firing creation and ToString
int test_firing_creation() {
    std::cout << "\n=== Test: Firing Creation ===" << std::endl;
    
    auto& generator = IDGenerator::Instance();
    
    // Create a match first
    Match match;
    match.match_id = generator.NextMatchID();
    match.join_case_id = 42;
    match.input_channel_ids = {1, 2};
    match.detected_at = std::chrono::steady_clock::now();
    
    // Create a firing
    Firing firing;
    firing.firing_id = generator.NextFiringID();
    firing.match = match;
    firing.consumed_messages = {}; // Empty for this test
    firing.context = {};
    firing.runnable_id = 100;
    firing.fired_at = std::chrono::steady_clock::now();
    
    TEST_ASSERT(firing.firing_id > 0, "Firing ID should be positive");
    TEST_ASSERT(firing.match.match_id == match.match_id, "Match should be preserved");
    TEST_ASSERT(firing.runnable_id == 100, "Runnable ID should match");
    
    std::string str = firing.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_ASSERT(str.find("Firing") != std::string::npos, "ToString should contain 'Firing'");
    TEST_PASS("Firing creation and ToString");
    
    return 0;
}

// Test ScheduledReaction creation and ToString
int test_scheduled_reaction_creation() {
    std::cout << "\n=== Test: ScheduledReaction Creation ===" << std::endl;
    
    auto& generator = IDGenerator::Instance();
    
    // Create a match
    Match match;
    match.match_id = generator.NextMatchID();
    match.join_case_id = 42;
    match.input_channel_ids = {1, 2};
    match.detected_at = std::chrono::steady_clock::now();
    
    // Create a firing
    Firing firing;
    firing.firing_id = generator.NextFiringID();
    firing.match = match;
    firing.consumed_messages = {};
    firing.context = {};
    firing.runnable_id = 100;
    firing.fired_at = std::chrono::steady_clock::now();
    
    // Create a scheduled reaction
    ScheduledReaction reaction;
    reaction.reaction_id = generator.NextReactionID();
    reaction.firing = firing;
    reaction.runnable = nullptr; // No actual runnable for this test
    reaction.scheduled_at = std::chrono::steady_clock::now();
    
    TEST_ASSERT(reaction.reaction_id > 0, "Reaction ID should be positive");
    TEST_ASSERT(reaction.firing.firing_id == firing.firing_id, "Firing should be preserved");
    
    std::string str = reaction.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_ASSERT(str.find("ScheduledReaction") != std::string::npos, 
                "ToString should contain 'ScheduledReaction'");
    TEST_PASS("ScheduledReaction creation and ToString");
    
    return 0;
}

// Test ExecutionResult creation and status checks
int test_execution_result_success() {
    std::cout << "\n=== Test: ExecutionResult Success ===" << std::endl;
    
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto end = std::chrono::steady_clock::now();
    
    ExecutionResult result;
    result.reaction_id = 123;
    result.status = ExecutionStatus::Success;
    result.error_message = {};
    result.exception = {};
    result.started_at = start;
    result.completed_at = end;
    result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    TEST_ASSERT(result.IsSuccess(), "IsSuccess() should return true");
    TEST_ASSERT(!result.IsFailed(), "IsFailed() should return false");
    TEST_ASSERT(!result.IsCancelled(), "IsCancelled() should return false");
    TEST_ASSERT(result.duration.count() >= 10, "Duration should be at least 10ms");
    TEST_ASSERT(!result.error_message.has_value(), "Error message should not be present");
    
    std::string str = result.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_ASSERT(str.find("Success") != std::string::npos, "ToString should contain 'Success'");
    TEST_PASS("ExecutionResult success");
    
    return 0;
}

// Test ExecutionResult failure
int test_execution_result_failure() {
    std::cout << "\n=== Test: ExecutionResult Failure ===" << std::endl;
    
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    
    ExecutionResult result;
    result.reaction_id = 456;
    result.status = ExecutionStatus::Failed;
    result.error_message = "Test error message";
    result.exception = {};
    result.started_at = start;
    result.completed_at = end;
    result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    TEST_ASSERT(!result.IsSuccess(), "IsSuccess() should return false");
    TEST_ASSERT(result.IsFailed(), "IsFailed() should return true");
    TEST_ASSERT(!result.IsCancelled(), "IsCancelled() should return false");
    TEST_ASSERT(result.error_message.has_value(), "Error message should be present");
    TEST_ASSERT(result.error_message.value() == "Test error message", 
                "Error message should match");
    
    std::string str = result.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_ASSERT(str.find("Failed") != std::string::npos, "ToString should contain 'Failed'");
    TEST_ASSERT(str.find("Test error message") != std::string::npos, 
                "ToString should contain error message");
    TEST_PASS("ExecutionResult failure");
    
    return 0;
}

// Test ExecutionResult cancelled
int test_execution_result_cancelled() {
    std::cout << "\n=== Test: ExecutionResult Cancelled ===" << std::endl;
    
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    
    ExecutionResult result;
    result.reaction_id = 789;
    result.status = ExecutionStatus::Cancelled;
    result.error_message = {};
    result.exception = {};
    result.started_at = start;
    result.completed_at = end;
    result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    TEST_ASSERT(!result.IsSuccess(), "IsSuccess() should return false");
    TEST_ASSERT(!result.IsFailed(), "IsFailed() should return false");
    TEST_ASSERT(result.IsCancelled(), "IsCancelled() should return true");
    
    std::string str = result.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_ASSERT(str.find("Cancelled") != std::string::npos, "ToString should contain 'Cancelled'");
    TEST_PASS("ExecutionResult cancelled");
    
    return 0;
}

// Test ExecutionStatus ToString
int test_execution_status_to_string() {
    std::cout << "\n=== Test: ExecutionStatus ToString ===" << std::endl;
    
    TEST_ASSERT(ToString(ExecutionStatus::Success) == "Success", 
                "ExecutionStatus::Success ToString");
    TEST_ASSERT(ToString(ExecutionStatus::Failed) == "Failed", 
                "ExecutionStatus::Failed ToString");
    TEST_ASSERT(ToString(ExecutionStatus::Cancelled) == "Cancelled", 
                "ExecutionStatus::Cancelled ToString");
    TEST_PASS("ExecutionStatus ToString");
    
    return 0;
}

// Test timing information capture
int test_timing_information() {
    std::cout << "\n=== Test: Timing Information Capture ===" << std::endl;
    
    auto t1 = std::chrono::steady_clock::now();
    
    Match match;
    match.match_id = 1;
    match.join_case_id = 1;
    match.input_channel_ids = {1};
    match.detected_at = t1;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    auto t2 = std::chrono::steady_clock::now();
    
    Firing firing;
    firing.firing_id = 1;
    firing.match = match;
    firing.consumed_messages = {};
    firing.context = {};
    firing.runnable_id = 1;
    firing.fired_at = t2;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    auto t3 = std::chrono::steady_clock::now();
    
    ScheduledReaction reaction;
    reaction.reaction_id = 1;
    reaction.firing = firing;
    reaction.runnable = nullptr;
    reaction.scheduled_at = t3;
    
    // Verify timing relationships
    TEST_ASSERT(firing.fired_at >= match.detected_at, 
                "Firing should occur after match detection");
    TEST_ASSERT(reaction.scheduled_at >= firing.fired_at, 
                "Scheduling should occur after firing");
    TEST_PASS("Timing information capture");
    
    return 0;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Firing Model Tests" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int result = 0;
    
    result |= test_id_generator_uniqueness();
    result |= test_id_generator_thread_safety();
    result |= test_match_creation();
    result |= test_firing_creation();
    result |= test_scheduled_reaction_creation();
    result |= test_execution_result_success();
    result |= test_execution_result_failure();
    result |= test_execution_result_cancelled();
    result |= test_execution_status_to_string();
    result |= test_timing_information();
    
    if (result == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  All Firing Model Tests PASSED!" << std::endl;
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Some Firing Model Tests FAILED!" << std::endl;
        std::cout << "========================================" << std::endl;
    }
    
    return result;
}
