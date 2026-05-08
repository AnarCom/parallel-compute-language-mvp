#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <chrono>
#include <stdexcept>

#include "runtime/reactor/common/lifecycle.hpp"
#include "runtime/reactor/common/firing.hpp"
#include "runtime/reactor/common/events.hpp"
#include "runtime/reactor/common/event_logger.hpp"
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

// Integration test: Lifecycle + Events
int test_lifecycle_with_events() {
    std::cout << "\n=== Integration Test: Lifecycle + Events ===" << std::endl;
    
    // Create event logger
    auto logger = std::make_shared<InMemoryEventLogger>(1000);
    
    // Create repository lifecycle
    RepositoryLifecycle repo_lifecycle;
    
    // Log repository started event
    auto event1 = CreateRepositoryStartedEvent(1);
    logger->Log(event1);
    repo_lifecycle.Start();
    
    TEST_ASSERT(repo_lifecycle.IsRunning(), "Repository should be running");
    
    // Create some channels and log their creation
    ChannelLifecycle channel1;
    ChannelLifecycle channel2;
    
    auto event2 = CreateChannelCreatedEvent(2, 100, ChannelMode::Sync, Type::Int());
    auto event3 = CreateChannelCreatedEvent(3, 101, ChannelMode::Async, Type::Bool());
    logger->Log(event2);
    logger->Log(event3);
    
    TEST_ASSERT(channel1.IsActive(), "Channel 1 should be active");
    TEST_ASSERT(channel2.IsActive(), "Channel 2 should be active");
    
    // Close channels and log events
    channel1.Close();
    auto event4 = CreateChannelClosedEvent(4, 100, ChannelMode::Sync, Type::Int());
    logger->Log(event4);
    
    channel2.Close();
    auto event5 = CreateChannelClosedEvent(5, 101, ChannelMode::Async, Type::Bool());
    logger->Log(event5);
    
    // Shutdown repository
    repo_lifecycle.BeginShutdown();
    auto event6 = CreateRepositoryShuttingDownEvent(6);
    logger->Log(event6);
    
    repo_lifecycle.MarkCompleted();
    auto event7 = CreateRepositoryCompletedEvent(7);
    logger->Log(event7);
    
    // Verify all events were logged
    TEST_ASSERT(logger->Size() == 7, "Should have 7 events logged");
    
    // Verify event types
    auto repo_events = logger->GetEventsByType(RuntimeEventType::RepositoryStarted);
    TEST_ASSERT(repo_events.size() == 1, "Should have 1 RepositoryStarted event");
    
    auto channel_created = logger->GetEventsByType(RuntimeEventType::ChannelCreated);
    TEST_ASSERT(channel_created.size() == 2, "Should have 2 ChannelCreated events");
    
    auto channel_closed = logger->GetEventsByType(RuntimeEventType::ChannelClosed);
    TEST_ASSERT(channel_closed.size() == 2, "Should have 2 ChannelClosed events");
    
    TEST_PASS("Lifecycle + Events integration");
    
    return 0;
}

// Integration test: Firing Model + Events
int test_firing_model_with_events() {
    std::cout << "\n=== Integration Test: Firing Model + Events ===" << std::endl;
    
    auto logger = std::make_shared<InMemoryEventLogger>(1000);
    auto& id_gen = IDGenerator::Instance();
    
    // Create a match
    Match match;
    match.match_id = id_gen.NextMatchID();
    match.join_case_id = 42;
    match.input_channel_ids = {1, 2, 3};
    match.detected_at = std::chrono::steady_clock::now();
    
    // Log match detected event
    auto event1 = CreateMatchDetectedEvent(1, match);
    logger->Log(event1);
    
    // Create a firing
    Firing firing;
    firing.firing_id = id_gen.NextFiringID();
    firing.match = match;
    firing.consumed_messages = {};
    firing.context = {};
    firing.runnable_id = 100;
    firing.fired_at = std::chrono::steady_clock::now();
    
    // Log firing committed event
    auto event2 = CreateFiringCommittedEvent(2, firing);
    logger->Log(event2);
    
    // Create a scheduled reaction
    ScheduledReaction reaction;
    reaction.reaction_id = id_gen.NextReactionID();
    reaction.firing = firing;
    reaction.runnable = nullptr;
    reaction.scheduled_at = std::chrono::steady_clock::now();
    
    // Log reaction scheduled event
    auto event3 = CreateReactionScheduledEvent(3, reaction);
    logger->Log(event3);
    
    // Simulate reaction execution
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto end = std::chrono::steady_clock::now();
    
    ExecutionResult result;
    result.reaction_id = reaction.reaction_id;
    result.status = ExecutionStatus::Success;
    result.error_message = {};
    result.exception = {};
    result.started_at = start;
    result.completed_at = end;
    result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Log reaction completed event
    auto event4 = CreateReactionCompletedEvent(4, result);
    logger->Log(event4);
    
    // Verify all events were logged
    TEST_ASSERT(logger->Size() == 4, "Should have 4 events logged");
    
    // Verify event sequence
    auto events = logger->GetEvents();
    TEST_ASSERT(events[0].type == RuntimeEventType::MatchDetected, "First event should be MatchDetected");
    TEST_ASSERT(events[1].type == RuntimeEventType::FiringCommitted, "Second event should be FiringCommitted");
    TEST_ASSERT(events[2].type == RuntimeEventType::ReactionScheduled, "Third event should be ReactionScheduled");
    TEST_ASSERT(events[3].type == RuntimeEventType::ReactionCompleted, "Fourth event should be ReactionCompleted");
    
    TEST_PASS("Firing Model + Events integration");
    
    return 0;
}

// Integration test: Error Handling + Events
int test_error_handling_with_events() {
    std::cout << "\n=== Integration Test: Error Handling + Events ===" << std::endl;
    
    auto logger = std::make_shared<InMemoryEventLogger>(1000);
    ErrorHandler error_handler(ErrorPolicy::IsolateReaction);
    auto& id_gen = IDGenerator::Instance();
    
    // Create a match and firing
    Match match;
    match.match_id = id_gen.NextMatchID();
    match.join_case_id = 42;
    match.input_channel_ids = {1, 2};
    match.detected_at = std::chrono::steady_clock::now();
    
    Firing firing;
    firing.firing_id = id_gen.NextFiringID();
    firing.match = match;
    firing.consumed_messages = {};
    firing.context = {};
    firing.runnable_id = 100;
    firing.fired_at = std::chrono::steady_clock::now();
    
    ScheduledReaction reaction;
    reaction.reaction_id = id_gen.NextReactionID();
    reaction.firing = firing;
    reaction.runnable = nullptr;
    reaction.scheduled_at = std::chrono::steady_clock::now();
    
    // Log reaction scheduled
    auto event1 = CreateReactionScheduledEvent(1, reaction);
    logger->Log(event1);
    
    // Simulate reaction failure
    std::exception_ptr exception;
    try {
        throw std::runtime_error("Simulated reaction failure");
    } catch (...) {
        exception = std::current_exception();
    }
    
    // Handle the error
    auto result = error_handler.HandleReactionError(reaction, exception);
    
    // Log reaction failed event
    auto event2 = CreateReactionFailedEvent(2, result);
    logger->Log(event2);
    
    // Verify error was handled
    TEST_ASSERT(error_handler.HasErrors(), "Error handler should have errors");
    TEST_ASSERT(error_handler.GetErrorCount() == 1, "Should have 1 error");
    TEST_ASSERT(result.IsFailed(), "Result should indicate failure");
    
    // Verify events were logged
    TEST_ASSERT(logger->Size() == 2, "Should have 2 events logged");
    
    auto failed_events = logger->GetEventsByType(RuntimeEventType::ReactionFailed);
    TEST_ASSERT(failed_events.size() == 1, "Should have 1 ReactionFailed event");
    
    TEST_PASS("Error Handling + Events integration");
    
    return 0;
}

// Integration test: Complete workflow simulation
int test_complete_workflow() {
    std::cout << "\n=== Integration Test: Complete Workflow ===" << std::endl;
    
    // Setup all components
    auto logger = std::make_shared<InMemoryEventLogger>(1000);
    ErrorHandler error_handler(ErrorPolicy::IsolateReaction);
    RepositoryLifecycle repo_lifecycle;
    auto& id_gen = IDGenerator::Instance();
    
    // 1. Start repository
    repo_lifecycle.Start();
    logger->Log(CreateRepositoryStartedEvent(1));
    TEST_ASSERT(repo_lifecycle.IsRunning(), "Repository should be running");
    
    // 2. Create channels
    ChannelLifecycle input_channel1;
    ChannelLifecycle input_channel2;
    ChannelLifecycle output_channel;
    
    logger->Log(CreateChannelCreatedEvent(2, 100, ChannelMode::Sync, Type::Int()));
    logger->Log(CreateChannelCreatedEvent(3, 101, ChannelMode::Sync, Type::Int()));
    logger->Log(CreateChannelCreatedEvent(4, 200, ChannelMode::Async, Type::Int()));
    
    // 3. Register join-case
    IDs input_ids = {100, 101};
    logger->Log(CreateJoinCaseRegisteredEvent(5, 1, input_ids));
    
    // 4. Detect match
    Match match;
    match.match_id = id_gen.NextMatchID();
    match.join_case_id = 1;
    match.input_channel_ids = input_ids;
    match.detected_at = std::chrono::steady_clock::now();
    logger->Log(CreateMatchDetectedEvent(6, match));
    
    // 5. Commit firing
    Firing firing;
    firing.firing_id = id_gen.NextFiringID();
    firing.match = match;
    firing.consumed_messages = {};
    firing.context = {};
    firing.runnable_id = 1;
    firing.fired_at = std::chrono::steady_clock::now();
    logger->Log(CreateFiringCommittedEvent(7, firing));
    
    // 6. Schedule reaction
    ScheduledReaction reaction;
    reaction.reaction_id = id_gen.NextReactionID();
    reaction.firing = firing;
    reaction.runnable = nullptr;
    reaction.scheduled_at = std::chrono::steady_clock::now();
    logger->Log(CreateReactionScheduledEvent(8, reaction));
    
    // 7. Execute reaction (success case)
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    auto end = std::chrono::steady_clock::now();
    
    ExecutionResult result;
    result.reaction_id = reaction.reaction_id;
    result.status = ExecutionStatus::Success;
    result.error_message = {};
    result.exception = {};
    result.started_at = start;
    result.completed_at = end;
    result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    logger->Log(CreateReactionCompletedEvent(9, result));
    
    // 8. Simulate another reaction that fails
    ScheduledReaction failing_reaction;
    failing_reaction.reaction_id = id_gen.NextReactionID();
    failing_reaction.firing = firing;
    failing_reaction.runnable = nullptr;
    failing_reaction.scheduled_at = std::chrono::steady_clock::now();
    logger->Log(CreateReactionScheduledEvent(10, failing_reaction));
    
    std::exception_ptr exception;
    try {
        throw std::runtime_error("Computation error");
    } catch (...) {
        exception = std::current_exception();
    }
    
    auto failed_result = error_handler.HandleReactionError(failing_reaction, exception);
    logger->Log(CreateReactionFailedEvent(11, failed_result));
    
    // 9. Close channels
    input_channel1.Close();
    input_channel1.OnLastReferenceDropped();
    input_channel1.OnQueueEmpty();
    logger->Log(CreateChannelClosedEvent(12, 100, ChannelMode::Sync, Type::Int()));
    
    input_channel2.Close();
    input_channel2.OnLastReferenceDropped();
    input_channel2.OnQueueEmpty();
    logger->Log(CreateChannelClosedEvent(13, 101, ChannelMode::Sync, Type::Int()));
    
    output_channel.Close();
    output_channel.OnLastReferenceDropped();
    output_channel.OnQueueEmpty();
    logger->Log(CreateChannelClosedEvent(14, 200, ChannelMode::Async, Type::Int()));
    
    // 10. Shutdown repository
    repo_lifecycle.BeginShutdown();
    logger->Log(CreateRepositoryShuttingDownEvent(15));
    
    repo_lifecycle.MarkCompleted();
    logger->Log(CreateRepositoryCompletedEvent(16));
    
    // Verify complete workflow
    TEST_ASSERT(logger->Size() == 16, "Should have 16 events logged");
    TEST_ASSERT(repo_lifecycle.GetState() == RepositoryState::Completed, 
                "Repository should be completed");
    TEST_ASSERT(input_channel1.IsClosed(), "Input channel 1 should be closed");
    TEST_ASSERT(input_channel2.IsClosed(), "Input channel 2 should be closed");
    TEST_ASSERT(output_channel.IsClosed(), "Output channel should be closed");
    TEST_ASSERT(error_handler.GetErrorCount() == 1, "Should have 1 error recorded");
    
    // Verify event sequence makes sense
    auto events = logger->GetEvents();
    TEST_ASSERT(events[0].type == RuntimeEventType::RepositoryStarted, 
                "First event should be RepositoryStarted");
    TEST_ASSERT(events[15].type == RuntimeEventType::RepositoryCompleted, 
                "Last event should be RepositoryCompleted");
    
    // Print summary
    std::cout << "  Workflow Summary:" << std::endl;
    std::cout << "    - Repository lifecycle: Initializing -> Running -> ShuttingDown -> Completed" << std::endl;
    std::cout << "    - Channels created: 3" << std::endl;
    std::cout << "    - Channels closed: 3" << std::endl;
    std::cout << "    - Matches detected: 1" << std::endl;
    std::cout << "    - Firings committed: 1" << std::endl;
    std::cout << "    - Reactions scheduled: 2" << std::endl;
    std::cout << "    - Reactions succeeded: 1" << std::endl;
    std::cout << "    - Reactions failed: 1" << std::endl;
    std::cout << "    - Total events logged: " << logger->Size() << std::endl;
    
    TEST_PASS("Complete workflow simulation");
    
    return 0;
}

// Integration test: Concurrent operations
int test_concurrent_operations() {
    std::cout << "\n=== Integration Test: Concurrent Operations ===" << std::endl;
    
    auto logger = std::make_shared<InMemoryEventLogger>(10000);
    ErrorHandler error_handler(ErrorPolicy::IsolateReaction);
    RepositoryLifecycle repo_lifecycle;
    
    repo_lifecycle.Start();
    
    std::vector<std::thread> threads;
    const int num_threads = 5;
    const int operations_per_thread = 20;
    
    // Launch threads that perform various operations concurrently
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&logger, &error_handler, i, operations_per_thread]() {
            auto& id_gen = IDGenerator::Instance();
            
            for (int j = 0; j < operations_per_thread; ++j) {
                // Create and log events
                uint64_t event_id = i * operations_per_thread + j;
                
                // Create a match
                Match match;
                match.match_id = id_gen.NextMatchID();
                match.join_case_id = event_id;
                match.input_channel_ids = {event_id};
                match.detected_at = std::chrono::steady_clock::now();
                
                logger->Log(CreateMatchDetectedEvent(event_id, match));
                
                // Simulate some reactions failing
                if (j % 3 == 0) {
                    Firing firing;
                    firing.firing_id = id_gen.NextFiringID();
                    firing.match = match;
                    firing.consumed_messages = {};
                    firing.context = {};
                    firing.runnable_id = event_id;
                    firing.fired_at = std::chrono::steady_clock::now();
                    
                    ScheduledReaction reaction;
                    reaction.reaction_id = id_gen.NextReactionID();
                    reaction.firing = firing;
                    reaction.runnable = nullptr;
                    reaction.scheduled_at = std::chrono::steady_clock::now();
                    
                    std::exception_ptr exception;
                    try {
                        throw std::runtime_error("Concurrent error");
                    } catch (...) {
                        exception = std::current_exception();
                    }
                    
                    error_handler.HandleReactionError(reaction, exception);
                }
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    repo_lifecycle.BeginShutdown();
    repo_lifecycle.MarkCompleted();
    
    // Verify results
    TEST_ASSERT(logger->Size() == num_threads * operations_per_thread, 
                "Should have all events logged");
    
    size_t expected_errors = num_threads * (operations_per_thread / 3 + 
                            (operations_per_thread % 3 > 0 ? 1 : 0));
    TEST_ASSERT(error_handler.GetErrorCount() >= expected_errors - 5, 
                "Should have approximately expected number of errors");
    
    TEST_PASS("Concurrent operations");
    
    return 0;
}

// Integration test: Composite logger with multiple destinations
int test_composite_logger_integration() {
    std::cout << "\n=== Integration Test: Composite Logger ===" << std::endl;
    
    // Create composite logger with multiple destinations
    auto composite = std::make_shared<CompositeEventLogger>();
    auto memory_logger = std::make_shared<InMemoryEventLogger>(1000);
    
    int callback_count = 0;
    auto callback_logger = std::make_shared<CallbackEventLogger>(
        [&callback_count](const RuntimeEvent& event) {
            callback_count++;
            // Could write to file, send to monitoring system, etc.
        }
    );
    
    composite->AddLogger(memory_logger);
    composite->AddLogger(callback_logger);
    
    // Simulate a workflow
    RepositoryLifecycle repo_lifecycle;
    repo_lifecycle.Start();
    composite->Log(CreateRepositoryStartedEvent(1));
    
    for (int i = 0; i < 10; ++i) {
        auto event = CreateChannelCreatedEvent(i + 2, 100 + i, ChannelMode::Sync, Type::Int());
        composite->Log(event);
    }
    
    repo_lifecycle.BeginShutdown();
    composite->Log(CreateRepositoryShuttingDownEvent(12));
    
    repo_lifecycle.MarkCompleted();
    composite->Log(CreateRepositoryCompletedEvent(13));
    
    // Verify both loggers received all events
    TEST_ASSERT(memory_logger->Size() == 13, "Memory logger should have 13 events");
    TEST_ASSERT(callback_count == 13, "Callback should be invoked 13 times");
    
    TEST_PASS("Composite logger integration");
    
    return 0;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Integration Tests" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int result = 0;
    
    result |= test_lifecycle_with_events();
    result |= test_firing_model_with_events();
    result |= test_error_handling_with_events();
    result |= test_complete_workflow();
    result |= test_concurrent_operations();
    result |= test_composite_logger_integration();
    
    if (result == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  All Integration Tests PASSED!" << std::endl;
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Some Integration Tests FAILED!" << std::endl;
        std::cout << "========================================" << std::endl;
    }
    
    return result;
}
