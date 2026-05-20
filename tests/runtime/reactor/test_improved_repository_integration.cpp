#include <gtest/gtest.h>
#include <runtime/reactor/parallel_improved/repository.hpp>
#include <runtime/reactor/common/event_logger.hpp>
#include <thread>
#include <chrono>

using namespace reactor;

// Test runnable that increments a counter
class CounterRunnable : public Runnable {
public:
    explicit CounterRunnable(uint64_t id, std::atomic<int>& counter) 
        : id_(id), counter_(counter) {}
    
    void operator()(Objects inputs, Objects context) override {
        counter_.fetch_add(1, std::memory_order_relaxed);
    }
    
    uint64_t GetID() const noexcept override { return id_; }

private:
    uint64_t id_;
    std::atomic<int>& counter_;
};

// Test runnable that throws an exception
class FailingRunnable : public Runnable {
public:
    explicit FailingRunnable(uint64_t id) : id_(id) {}
    
    void operator()(Objects inputs, Objects context) override {
        throw std::runtime_error("Test error");
    }
    
    uint64_t GetID() const noexcept override { return id_; }

private:
    uint64_t id_;
};

// Test runnable that completes and signals
class CompletionRunnable : public Runnable {
public:
    explicit CompletionRunnable(uint64_t id, std::atomic<bool>& completed)
        : id_(id), completed_(completed) {}
    
    void operator()(Objects inputs, Objects context) override {
        completed_.store(true, std::memory_order_release);
    }
    
    uint64_t GetID() const noexcept override { return id_; }

private:
    uint64_t id_;
    std::atomic<bool>& completed_;
};

class ImprovedRepositoryIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Note: Using singleton, so state may persist between tests
        // In production, you'd want to reset the repository
    }
};

TEST_F(ImprovedRepositoryIntegrationTest, ChannelLifecycleBasic) {
    auto& repo = ImprovedRepository::GetRepository();
    
    // Create a channel
    auto channel = repo.NewChannel(ChannelMode::Async, Type::Int());
    
    // Check initial state
    EXPECT_TRUE(channel->IsActive());
    EXPECT_TRUE(channel->CanAcceptMessages());
    EXPECT_FALSE(channel->IsClosed());
    EXPECT_EQ(channel->GetState(), ChannelState::Active);
    
    // Close the channel
    channel->Close();
    
    // Check closed state
    EXPECT_FALSE(channel->CanAcceptMessages());
    EXPECT_EQ(channel->GetState(), ChannelState::Closing);
}

TEST_F(ImprovedRepositoryIntegrationTest, RepositoryLifecycleStates) {
    auto& repo = ImprovedRepository::GetRepository();
    
    // Initial state should be Initializing
    EXPECT_EQ(repo.GetState(), RepositoryState::Initializing);
    
    std::atomic<bool> completed{false};
    CompletionRunnable runnable(1, completed);
    std::unordered_map<uint64_t, Runnable*> map;
    map[1] = &runnable;
    
    // Run in a separate thread
    std::thread t([&]() {
        repo.Run(1, map);
    });
    
    // Wait a bit for state transition
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    // Should be running
    EXPECT_EQ(repo.GetState(), RepositoryState::Running);
    
    // Wait for completion
    while (!completed.load(std::memory_order_acquire)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    repo.Shutdown();
    t.join();
}

TEST_F(ImprovedRepositoryIntegrationTest, EventSystemIntegration) {
    auto& repo = ImprovedRepository::GetRepository();
    auto logger = std::make_shared<InMemoryEventLogger>(100);
    repo.SetEventLogger(logger);
    
    // Clear any previous events
    logger->Clear();
    
    // Create a channel - should emit ChannelCreated event
    auto channel = repo.NewChannel(ChannelMode::Async, Type::Int());
    
    auto events = logger->GetEvents();
    ASSERT_GE(events.size(), 1);
    
    bool found_channel_created = false;
    for (const auto& event : events) {
        if (event.type == RuntimeEventType::ChannelCreated) {
            found_channel_created = true;
            break;
        }
    }
    EXPECT_TRUE(found_channel_created);
}

TEST_F(ImprovedRepositoryIntegrationTest, MessageSentEvent) {
    auto& repo = ImprovedRepository::GetRepository();
    auto logger = std::make_shared<InMemoryEventLogger>(100);
    repo.SetEventLogger(logger);
    
    logger->Clear();
    
    // Create channel and send message
    auto channel = repo.NewChannel(ChannelMode::Async, Type::Int());
    logger->Clear();  // Clear channel created event
    
    channel->Push(Object::Int(42));
    
    auto events = logger->GetEvents();
    ASSERT_GE(events.size(), 1);
    
    bool found_message_sent = false;
    for (const auto& event : events) {
        if (event.type == RuntimeEventType::MessageSent) {
            found_message_sent = true;
            break;
        }
    }
    EXPECT_TRUE(found_message_sent);
}

TEST_F(ImprovedRepositoryIntegrationTest, ErrorHandlingIsolateReaction) {
    auto& repo = ImprovedRepository::GetRepository();
    repo.GetErrorHandler().SetPolicy(ErrorPolicy::IsolateReaction);
    
    auto logger = std::make_shared<InMemoryEventLogger>(100);
    repo.SetEventLogger(logger);
    logger->Clear();
    
    std::atomic<bool> completed{false};
    FailingRunnable failing_runnable(1);
    CompletionRunnable completion_runnable(2, completed);
    
    std::unordered_map<uint64_t, Runnable*> map;
    map[1] = &failing_runnable;
    map[2] = &completion_runnable;
    
    // Create channels for the failing runnable
    auto ch1 = repo.NewChannel(ChannelMode::Async, Type::Int());
    repo.RegisterJoinCase({ch1}, {}, 1);
    
    // Push message to trigger failing runnable
    ch1->Push(Object::Int(1));
    
    // Run in separate thread
    std::thread t([&]() {
        // This should not crash despite the error
        repo.Run(2, map);
    });
    
    // Wait for completion
    while (!completed.load(std::memory_order_acquire)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    repo.Shutdown();
    t.join();
    
    // Check that ReactionFailed event was emitted
    auto events = logger->GetEvents();
    bool found_reaction_failed = false;
    for (const auto& event : events) {
        if (event.type == RuntimeEventType::ReactionFailed) {
            found_reaction_failed = true;
            break;
        }
    }
    EXPECT_TRUE(found_reaction_failed);
}

TEST_F(ImprovedRepositoryIntegrationTest, JoinCaseRegistration) {
    auto& repo = ImprovedRepository::GetRepository();
    auto logger = std::make_shared<InMemoryEventLogger>(100);
    repo.SetEventLogger(logger);
    logger->Clear();
    
    // Create channels
    auto ch1 = repo.NewChannel(ChannelMode::Async, Type::Int());
    auto ch2 = repo.NewChannel(ChannelMode::Async, Type::Int());
    
    logger->Clear();  // Clear channel created events
    
    std::atomic<int> counter{0};
    CounterRunnable runnable(1, counter);
    
    // Register join case - should emit JoinCaseRegistered event
    repo.RegisterJoinCase({ch1, ch2}, {}, 1);
    
    auto events = logger->GetEvents();
    bool found_join_case_registered = false;
    for (const auto& event : events) {
        if (event.type == RuntimeEventType::JoinCaseRegistered) {
            found_join_case_registered = true;
            break;
        }
    }
    EXPECT_TRUE(found_join_case_registered);
}

TEST_F(ImprovedRepositoryIntegrationTest, MatchDetectionEvent) {
    auto& repo = ImprovedRepository::GetRepository();
    auto logger = std::make_shared<InMemoryEventLogger>(100);
    repo.SetEventLogger(logger);
    
    std::atomic<int> counter{0};
    CounterRunnable runnable(1, counter);
    
    std::unordered_map<uint64_t, Runnable*> map;
    map[1] = &runnable;
    
    // Create channels
    auto ch1 = repo.NewChannel(ChannelMode::Async, Type::Int());
    auto ch2 = repo.NewChannel(ChannelMode::Async, Type::Int());
    
    // Register join case
    repo.RegisterJoinCase({ch1, ch2}, {}, 1);
    
    logger->Clear();  // Clear previous events
    
    // Push messages to trigger match
    ch1->Push(Object::Int(1));
    ch2->Push(Object::Int(2));
    
    // Check for MatchDetected event
    auto events = logger->GetEvents();
    bool found_match_detected = false;
    for (const auto& event : events) {
        if (event.type == RuntimeEventType::MatchDetected) {
            found_match_detected = true;
            break;
        }
    }
    EXPECT_TRUE(found_match_detected);
}

TEST_F(ImprovedRepositoryIntegrationTest, ShutdownGraceful) {
    auto& repo = ImprovedRepository::GetRepository();
    
    std::atomic<bool> completed{false};
    CompletionRunnable runnable(1, completed);
    std::unordered_map<uint64_t, Runnable*> map;
    map[1] = &runnable;
    
    std::thread t([&]() {
        repo.Run(1, map);
    });
    
    // Wait for running state
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    // Trigger shutdown
    repo.Shutdown();
    
    // Wait for completion
    repo.WaitForCompletion();
    
    t.join();
    
    // Should be in completed or shutting down state
    auto state = repo.GetState();
    EXPECT_TRUE(state == RepositoryState::Completed || 
                state == RepositoryState::ShuttingDown);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
