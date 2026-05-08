#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <chrono>

#include "runtime/reactor/common/events.hpp"
#include "runtime/reactor/common/event_logger.hpp"

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

// Test RuntimeEventType ToString
int test_event_type_to_string() {
    std::cout << "\n=== Test: RuntimeEventType ToString ===" << std::endl;
    
    TEST_ASSERT(ToString(RuntimeEventType::ChannelCreated) == "ChannelCreated", 
                "ChannelCreated ToString");
    TEST_ASSERT(ToString(RuntimeEventType::ChannelClosed) == "ChannelClosed", 
                "ChannelClosed ToString");
    TEST_ASSERT(ToString(RuntimeEventType::MessageSent) == "MessageSent", 
                "MessageSent ToString");
    TEST_ASSERT(ToString(RuntimeEventType::MessageReceived) == "MessageReceived", 
                "MessageReceived ToString");
    TEST_ASSERT(ToString(RuntimeEventType::JoinCaseRegistered) == "JoinCaseRegistered", 
                "JoinCaseRegistered ToString");
    TEST_ASSERT(ToString(RuntimeEventType::MatchDetected) == "MatchDetected", 
                "MatchDetected ToString");
    TEST_ASSERT(ToString(RuntimeEventType::FiringCommitted) == "FiringCommitted", 
                "FiringCommitted ToString");
    TEST_ASSERT(ToString(RuntimeEventType::ReactionScheduled) == "ReactionScheduled", 
                "ReactionScheduled ToString");
    TEST_ASSERT(ToString(RuntimeEventType::ReactionCompleted) == "ReactionCompleted", 
                "ReactionCompleted ToString");
    TEST_ASSERT(ToString(RuntimeEventType::RepositoryStarted) == "RepositoryStarted", 
                "RepositoryStarted ToString");
    TEST_PASS("RuntimeEventType ToString");
    
    return 0;
}

// Test ChannelCreated event creation
int test_channel_created_event() {
    std::cout << "\n=== Test: ChannelCreated Event ===" << std::endl;
    
    auto event = CreateChannelCreatedEvent(1, 100, ChannelMode::Sync, Type::Int());
    
    TEST_ASSERT(event.event_id == 1, "Event ID should match");
    TEST_ASSERT(event.type == RuntimeEventType::ChannelCreated, "Event type should be ChannelCreated");
    
    auto* data = std::get_if<ChannelEventData>(&event.data);
    TEST_ASSERT(data != nullptr, "Event data should be ChannelEventData");
    TEST_ASSERT(data->channel_id == 100, "Channel ID should match");
    TEST_ASSERT(data->mode == ChannelMode::Sync, "Channel mode should be Sync");
    
    std::string str = event.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_ASSERT(str.find("ChannelCreated") != std::string::npos, 
                "ToString should contain event type");
    
    std::string json = event.ToJSON();
    TEST_ASSERT(!json.empty(), "ToJSON should produce non-empty string");
    TEST_ASSERT(json.find("ChannelCreated") != std::string::npos, 
                "ToJSON should contain event type");
    TEST_PASS("ChannelCreated event");
    
    return 0;
}

// Test JoinCaseRegistered event creation
int test_join_case_registered_event() {
    std::cout << "\n=== Test: JoinCaseRegistered Event ===" << std::endl;
    
    IDs channel_ids = {1, 2, 3};
    auto event = CreateJoinCaseRegisteredEvent(2, 42, channel_ids);
    
    TEST_ASSERT(event.event_id == 2, "Event ID should match");
    TEST_ASSERT(event.type == RuntimeEventType::JoinCaseRegistered, 
                "Event type should be JoinCaseRegistered");
    
    auto* data = std::get_if<MatchEventData>(&event.data);
    TEST_ASSERT(data != nullptr, "Event data should be MatchEventData");
    TEST_ASSERT(data->join_case_id == 42, "Join case ID should match");
    TEST_ASSERT(data->channel_ids.size() == 3, "Should have 3 channel IDs");
    
    std::string str = event.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    
    std::string json = event.ToJSON();
    TEST_ASSERT(!json.empty(), "ToJSON should produce non-empty string");
    TEST_PASS("JoinCaseRegistered event");
    
    return 0;
}

// Test MatchDetected event creation
int test_match_detected_event() {
    std::cout << "\n=== Test: MatchDetected Event ===" << std::endl;
    
    Match match;
    match.match_id = 123;
    match.join_case_id = 42;
    match.input_channel_ids = {1, 2};
    match.detected_at = std::chrono::steady_clock::now();
    
    auto event = CreateMatchDetectedEvent(3, match);
    
    TEST_ASSERT(event.event_id == 3, "Event ID should match");
    TEST_ASSERT(event.type == RuntimeEventType::MatchDetected, 
                "Event type should be MatchDetected");
    
    auto* data = std::get_if<MatchEventData>(&event.data);
    TEST_ASSERT(data != nullptr, "Event data should be MatchEventData");
    TEST_ASSERT(data->match_id == 123, "Match ID should match");
    TEST_ASSERT(data->join_case_id == 42, "Join case ID should match");
    TEST_ASSERT(data->success == true, "Match should be successful");
    
    std::string str = event.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_PASS("MatchDetected event");
    
    return 0;
}

// Test FiringCommitted event creation
int test_firing_committed_event() {
    std::cout << "\n=== Test: FiringCommitted Event ===" << std::endl;
    
    Match match;
    match.match_id = 123;
    match.join_case_id = 42;
    match.input_channel_ids = {1, 2};
    match.detected_at = std::chrono::steady_clock::now();
    
    Firing firing;
    firing.firing_id = 456;
    firing.match = match;
    firing.consumed_messages = {};
    firing.context = {};
    firing.runnable_id = 100;
    firing.fired_at = std::chrono::steady_clock::now();
    
    auto event = CreateFiringCommittedEvent(4, firing);
    
    TEST_ASSERT(event.event_id == 4, "Event ID should match");
    TEST_ASSERT(event.type == RuntimeEventType::FiringCommitted, 
                "Event type should be FiringCommitted");
    
    auto* data = std::get_if<FiringEventData>(&event.data);
    TEST_ASSERT(data != nullptr, "Event data should be FiringEventData");
    TEST_ASSERT(data->firing_id == 456, "Firing ID should match");
    TEST_ASSERT(data->match_id == 123, "Match ID should match");
    
    std::string str = event.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_PASS("FiringCommitted event");
    
    return 0;
}

// Test ReactionCompleted event creation
int test_reaction_completed_event() {
    std::cout << "\n=== Test: ReactionCompleted Event ===" << std::endl;
    
    ExecutionResult result;
    result.reaction_id = 789;
    result.status = ExecutionStatus::Success;
    result.error_message = {};
    result.exception = {};
    result.started_at = std::chrono::steady_clock::now();
    result.completed_at = std::chrono::steady_clock::now();
    result.duration = std::chrono::milliseconds(10);
    
    auto event = CreateReactionCompletedEvent(5, result);
    
    TEST_ASSERT(event.event_id == 5, "Event ID should match");
    TEST_ASSERT(event.type == RuntimeEventType::ReactionCompleted, 
                "Event type should be ReactionCompleted");
    
    auto* data = std::get_if<ReactionEventData>(&event.data);
    TEST_ASSERT(data != nullptr, "Event data should be ReactionEventData");
    TEST_ASSERT(data->reaction_id == 789, "Reaction ID should match");
    TEST_ASSERT(data->result.has_value(), "Result should be present");
    
    std::string str = event.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_PASS("ReactionCompleted event");
    
    return 0;
}

// Test RepositoryStarted event creation
int test_repository_started_event() {
    std::cout << "\n=== Test: RepositoryStarted Event ===" << std::endl;
    
    auto event = CreateRepositoryStartedEvent(6);
    
    TEST_ASSERT(event.event_id == 6, "Event ID should match");
    TEST_ASSERT(event.type == RuntimeEventType::RepositoryStarted, 
                "Event type should be RepositoryStarted");
    
    auto* data = std::get_if<LifecycleEventData>(&event.data);
    TEST_ASSERT(data != nullptr, "Event data should be LifecycleEventData");
    TEST_ASSERT(data->state == RepositoryState::Running, "State should be Running");
    
    std::string str = event.ToString();
    TEST_ASSERT(!str.empty(), "ToString should produce non-empty string");
    TEST_PASS("RepositoryStarted event");
    
    return 0;
}

// Test InMemoryEventLogger basic functionality
int test_in_memory_logger_basic() {
    std::cout << "\n=== Test: InMemoryEventLogger Basic ===" << std::endl;
    
    InMemoryEventLogger logger(100);
    
    TEST_ASSERT(logger.Empty(), "Logger should be empty initially");
    TEST_ASSERT(logger.Size() == 0, "Size should be 0 initially");
    TEST_ASSERT(logger.Capacity() == 100, "Capacity should be 100");
    
    // Log some events
    auto event1 = CreateRepositoryStartedEvent(1);
    auto event2 = CreateRepositoryStartedEvent(2);
    auto event3 = CreateRepositoryStartedEvent(3);
    
    logger.Log(event1);
    logger.Log(event2);
    logger.Log(event3);
    
    TEST_ASSERT(!logger.Empty(), "Logger should not be empty after logging");
    TEST_ASSERT(logger.Size() == 3, "Size should be 3 after logging 3 events");
    
    auto events = logger.GetEvents();
    TEST_ASSERT(events.size() == 3, "Should retrieve 3 events");
    TEST_ASSERT(events[0].event_id == 1, "First event ID should be 1");
    TEST_ASSERT(events[1].event_id == 2, "Second event ID should be 2");
    TEST_ASSERT(events[2].event_id == 3, "Third event ID should be 3");
    
    logger.Clear();
    TEST_ASSERT(logger.Empty(), "Logger should be empty after Clear()");
    TEST_PASS("InMemoryEventLogger basic functionality");
    
    return 0;
}

// Test InMemoryEventLogger capacity limit
int test_in_memory_logger_capacity() {
    std::cout << "\n=== Test: InMemoryEventLogger Capacity ===" << std::endl;
    
    InMemoryEventLogger logger(5);
    
    // Log more events than capacity
    for (int i = 1; i <= 10; ++i) {
        auto event = CreateRepositoryStartedEvent(i);
        logger.Log(event);
    }
    
    TEST_ASSERT(logger.Size() == 5, "Size should be limited to capacity");
    
    auto events = logger.GetEvents();
    TEST_ASSERT(events.size() == 5, "Should retrieve only 5 events");
    // Should have the last 5 events (6-10)
    TEST_ASSERT(events[0].event_id == 6, "First event should be ID 6 (oldest kept)");
    TEST_ASSERT(events[4].event_id == 10, "Last event should be ID 10 (newest)");
    TEST_PASS("InMemoryEventLogger capacity limit");
    
    return 0;
}

// Test InMemoryEventLogger filtering by type
int test_in_memory_logger_filter_by_type() {
    std::cout << "\n=== Test: InMemoryEventLogger Filter by Type ===" << std::endl;
    
    InMemoryEventLogger logger(100);
    
    // Log different types of events
    logger.Log(CreateRepositoryStartedEvent(1));
    logger.Log(CreateChannelCreatedEvent(2, 100, ChannelMode::Sync, Type::Int()));
    logger.Log(CreateRepositoryStartedEvent(3));
    logger.Log(CreateChannelCreatedEvent(4, 101, ChannelMode::Async, Type::Bool()));
    logger.Log(CreateRepositoryStartedEvent(5));
    
    auto repo_events = logger.GetEventsByType(RuntimeEventType::RepositoryStarted);
    TEST_ASSERT(repo_events.size() == 3, "Should have 3 RepositoryStarted events");
    
    auto channel_events = logger.GetEventsByType(RuntimeEventType::ChannelCreated);
    TEST_ASSERT(channel_events.size() == 2, "Should have 2 ChannelCreated events");
    TEST_PASS("InMemoryEventLogger filter by type");
    
    return 0;
}

// Test InMemoryEventLogger filtering by time range
int test_in_memory_logger_filter_by_time() {
    std::cout << "\n=== Test: InMemoryEventLogger Filter by Time ===" << std::endl;
    
    InMemoryEventLogger logger(100);
    
    auto start = std::chrono::steady_clock::now();
    
    logger.Log(CreateRepositoryStartedEvent(1));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto mid = std::chrono::steady_clock::now();
    
    logger.Log(CreateRepositoryStartedEvent(2));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto end = std::chrono::steady_clock::now();
    
    logger.Log(CreateRepositoryStartedEvent(3));
    
    // Get events in middle range
    auto events = logger.GetEventsInRange(mid, end);
    TEST_ASSERT(events.size() >= 1, "Should have at least 1 event in range");
    TEST_PASS("InMemoryEventLogger filter by time");
    
    return 0;
}

// Test InMemoryEventLogger custom predicate
int test_in_memory_logger_custom_predicate() {
    std::cout << "\n=== Test: InMemoryEventLogger Custom Predicate ===" << std::endl;
    
    InMemoryEventLogger logger(100);
    
    for (int i = 1; i <= 10; ++i) {
        logger.Log(CreateRepositoryStartedEvent(i));
    }
    
    // Filter for even event IDs
    auto events = logger.GetEventsWhere([](const RuntimeEvent& e) {
        return e.event_id % 2 == 0;
    });
    
    TEST_ASSERT(events.size() == 5, "Should have 5 events with even IDs");
    for (const auto& event : events) {
        TEST_ASSERT(event.event_id % 2 == 0, "All filtered events should have even IDs");
    }
    TEST_PASS("InMemoryEventLogger custom predicate");
    
    return 0;
}

// Test CallbackEventLogger
int test_callback_logger() {
    std::cout << "\n=== Test: CallbackEventLogger ===" << std::endl;
    
    int callback_count = 0;
    uint64_t last_event_id = 0;
    
    CallbackEventLogger logger([&callback_count, &last_event_id](const RuntimeEvent& event) {
        callback_count++;
        last_event_id = event.event_id;
    });
    
    logger.Log(CreateRepositoryStartedEvent(1));
    logger.Log(CreateRepositoryStartedEvent(2));
    logger.Log(CreateRepositoryStartedEvent(3));
    
    TEST_ASSERT(callback_count == 3, "Callback should be invoked 3 times");
    TEST_ASSERT(last_event_id == 3, "Last event ID should be 3");
    
    logger.Flush(); // Should be no-op
    TEST_PASS("CallbackEventLogger");
    
    return 0;
}

// Test CompositeEventLogger
int test_composite_logger() {
    std::cout << "\n=== Test: CompositeEventLogger ===" << std::endl;
    
    auto composite = std::make_shared<CompositeEventLogger>();
    
    TEST_ASSERT(composite->LoggerCount() == 0, "Should have 0 loggers initially");
    
    auto memory_logger = std::make_shared<InMemoryEventLogger>(100);
    int callback_count = 0;
    auto callback_logger = std::make_shared<CallbackEventLogger>(
        [&callback_count](const RuntimeEvent&) { callback_count++; }
    );
    
    composite->AddLogger(memory_logger);
    composite->AddLogger(callback_logger);
    
    TEST_ASSERT(composite->LoggerCount() == 2, "Should have 2 loggers");
    
    // Log events through composite
    composite->Log(CreateRepositoryStartedEvent(1));
    composite->Log(CreateRepositoryStartedEvent(2));
    
    // Both loggers should receive events
    TEST_ASSERT(memory_logger->Size() == 2, "Memory logger should have 2 events");
    TEST_ASSERT(callback_count == 2, "Callback should be invoked 2 times");
    
    // Remove a logger
    bool removed = composite->RemoveLogger(callback_logger);
    TEST_ASSERT(removed, "Should successfully remove logger");
    TEST_ASSERT(composite->LoggerCount() == 1, "Should have 1 logger after removal");
    
    composite->Clear();
    TEST_ASSERT(composite->LoggerCount() == 0, "Should have 0 loggers after Clear()");
    TEST_PASS("CompositeEventLogger");
    
    return 0;
}

// Test thread safety of InMemoryEventLogger
int test_in_memory_logger_thread_safety() {
    std::cout << "\n=== Test: InMemoryEventLogger Thread Safety ===" << std::endl;
    
    InMemoryEventLogger logger(10000);
    
    std::vector<std::thread> threads;
    const int num_threads = 10;
    const int events_per_thread = 100;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&logger, i, events_per_thread]() {
            for (int j = 0; j < events_per_thread; ++j) {
                auto event = CreateRepositoryStartedEvent(i * events_per_thread + j);
                logger.Log(event);
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    TEST_ASSERT(logger.Size() == num_threads * events_per_thread, 
                "Should have all events logged");
    TEST_PASS("InMemoryEventLogger thread safety");
    
    return 0;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Events and Tracing Tests" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int result = 0;
    
    result |= test_event_type_to_string();
    result |= test_channel_created_event();
    result |= test_join_case_registered_event();
    result |= test_match_detected_event();
    result |= test_firing_committed_event();
    result |= test_reaction_completed_event();
    result |= test_repository_started_event();
    result |= test_in_memory_logger_basic();
    result |= test_in_memory_logger_capacity();
    result |= test_in_memory_logger_filter_by_type();
    result |= test_in_memory_logger_filter_by_time();
    result |= test_in_memory_logger_custom_predicate();
    result |= test_callback_logger();
    result |= test_composite_logger();
    result |= test_in_memory_logger_thread_safety();
    
    if (result == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  All Events Tests PASSED!" << std::endl;
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Some Events Tests FAILED!" << std::endl;
        std::cout << "========================================" << std::endl;
    }
    
    return result;
}
