# Runtime Enhancement Integration Guide

## Overview

This document provides a comprehensive guide for integrating the three major runtime enhancements into the existing GoJo parallel compute language runtime:

1. **Lifecycle Model** - Implemented in [`lifecycle.hpp`](../runtime/reactor/common/lifecycle.hpp:1) and [`lifecycle.cpp`](../runtime/reactor/common/lifecycle.cpp:1)
2. **Firing Model** - Implemented in [`firing.hpp`](../runtime/reactor/common/firing.hpp:1) and [`firing.cpp`](../runtime/reactor/common/firing.cpp:1)
3. **Events & Tracing** - Implemented in [`events.hpp`](../runtime/reactor/common/events.hpp:1), [`event_logger.hpp`](../runtime/reactor/common/event_logger.hpp:1), [`event_emitter.hpp`](../runtime/reactor/common/event_emitter.hpp:1)
4. **Error Handling** - Implemented in [`error_handler.hpp`](../runtime/reactor/common/error_handler.hpp:1) and [`error_handler.cpp`](../runtime/reactor/common/error_handler.cpp:1)

## Implementation Status

### ✅ Completed Components

All core components have been implemented and are ready for integration:

| Component | Files | Status |
|-----------|-------|--------|
| Lifecycle Model | lifecycle.hpp, lifecycle.cpp | ✅ Complete |
| Firing Model | firing.hpp, firing.cpp | ✅ Complete |
| Events System | events.hpp, events.cpp | ✅ Complete |
| Event Loggers | event_logger.hpp, event_logger.cpp | ✅ Complete |
| Event Emitter | event_emitter.hpp, event_emitter.cpp | ✅ Complete |
| Error Handler | error_handler.hpp, error_handler.cpp | ✅ Complete |

### 📋 Integration Tasks

The following tasks remain to integrate these components into the runtime:

1. **Update ChannelBase** - Add lifecycle management
2. **Update CycleRepository** - Integrate all systems
3. **Refactor CheckCase** - Use firing model
4. **Add Event Emission** - Throughout execution flow
5. **Add Error Handling** - Wrap reaction execution
6. **Update RedisRepository** - Apply same changes for distributed runtime
7. **Write Tests** - Unit and integration tests
8. **Update Documentation** - User and developer docs

---

## Integration Plan

### Phase 1: Update ChannelBase (Lifecycle Integration)

#### File: [`runtime/reactor/common/interface.hpp`](../runtime/reactor/common/interface.hpp:1)

**Changes Required:**

```cpp
#include "lifecycle.hpp"  // Add include

class ChannelBase : public ObjectValue {
public:
    ChannelBase(ChannelMode mode, Type payload_type);
    virtual ~ChannelBase() noexcept;

    virtual void Push(const Object& message) = 0;
    virtual uint64_t GetID() const noexcept = 0;

    // NEW: Lifecycle methods
    void Close() noexcept;
    ChannelState GetState() const noexcept;
    bool CanAcceptMessages() const noexcept;
    bool CanConsumeMessages() const noexcept;
    bool IsActive() const noexcept;
    bool IsClosed() const noexcept;

    [[nodiscard]] ChannelMode mode() const noexcept;
    [[nodiscard]] const Type& payload_type() const noexcept;
    [[nodiscard]] bool Accepts(const Object& message) const noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;
    std::string Serialize() const override;

private:
    ChannelMode mode_;
    Type payload_type_;
    ChannelLifecycle lifecycle_;  // NEW: Add lifecycle member
};
```

#### File: [`runtime/reactor/common/interface.cpp`](../runtime/reactor/common/interface.cpp:1)

**Changes Required:**

```cpp
#include "lifecycle.hpp"

ChannelBase::ChannelBase(ChannelMode mode, Type payload_type)
    : mode_(mode), payload_type_(std::move(payload_type)), lifecycle_() {}

// NEW: Implement lifecycle methods
void ChannelBase::Close() noexcept {
    lifecycle_.Close();
}

ChannelState ChannelBase::GetState() const noexcept {
    return lifecycle_.GetState();
}

bool ChannelBase::CanAcceptMessages() const noexcept {
    return lifecycle_.CanAcceptMessages();
}

bool ChannelBase::CanConsumeMessages() const noexcept {
    return lifecycle_.CanConsumeMessages();
}

bool ChannelBase::IsActive() const noexcept {
    return lifecycle_.IsActive();
}

bool ChannelBase::IsClosed() const noexcept {
    return lifecycle_.IsClosed();
}
```

---

### Phase 2: Update CycleChannel (Lifecycle Integration)

#### File: [`runtime/reactor/parallel/repository.hpp`](../runtime/reactor/parallel/repository.hpp:1)

**Changes Required:**

```cpp
class CycleChannel : public ChannelBase {
public:
    CycleChannel(ChannelMode mode, Type payload_type, uint64_t id, 
                 Pointer<Callback> callback) noexcept;

    void Push(const Object& message) override;
    uint64_t GetID() const noexcept override;
    
    // NEW: Notify lifecycle of reference changes
    void OnReferenceDropped() noexcept;
    void OnQueueEmpty() noexcept;

private:
    Pointer<Callback> GetCallback() const noexcept;

    uint64_t id_;
    Pointer<Callback> callback_;

    friend CycleRepository;
};
```

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Changes Required:**

```cpp
void CycleChannel::Push(const Object& message) {
    // NEW: Check if channel can accept messages
    if (!CanAcceptMessages()) {
        debug::runtime_assert(false, "Cannot push to closed channel");
        return;
    }
    
    auto maybe_callback = GetCallback();
    debug::runtime_assert(bool(maybe_callback), "channel callback is not installed");
    maybe_callback->OnMessage(id_, message);
}

// NEW: Lifecycle notification methods
void CycleChannel::OnReferenceDropped() noexcept {
    lifecycle_.OnLastReferenceDropped();
}

void CycleChannel::OnQueueEmpty() noexcept {
    lifecycle_.OnQueueEmpty();
}
```

---

### Phase 3: Update CycleRepository (Add All Systems)

#### File: [`runtime/reactor/parallel/repository.hpp`](../runtime/reactor/parallel/repository.hpp:1)

**Changes Required:**

```cpp
#include <runtime/reactor/common/lifecycle.hpp>
#include <runtime/reactor/common/firing.hpp>
#include <runtime/reactor/common/event_emitter.hpp>
#include <runtime/reactor/common/error_handler.hpp>

class CycleRepository : public Repository {
public:
    CycleRepository();   
    static CycleRepository& GetRepository();
    
    void RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) override;
    Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, 
                                     Type payload_type = Type::Unit()) override;
    void Run(uint64_t main_runnable_id, 
             std::unordered_map<uint64_t, Runnable*> runnable_map) override;

    // NEW: Lifecycle management
    void Shutdown() noexcept;
    void WaitForCompletion() noexcept;
    RepositoryState GetState() const noexcept;
    
    // NEW: Event system access
    void SetEventLogger(Pointer<EventLogger> logger);
    Pointer<EventLogger> GetEventLogger() const;
    Pointer<EventEmitter> GetEventEmitter() const;
    
    // NEW: Error handling access
    ErrorHandler& GetErrorHandler();
    const ErrorHandler& GetErrorHandler() const;

private:
    using QueuesMap = std::map<uint64_t, QueuePointer>;

    void RunRoutine() noexcept;
    bool CheckCases() noexcept;
    
    // NEW: Refactored firing pipeline
    Maybe<Match> DetectMatch(JoinCase& current_case) noexcept;
    Maybe<Firing> CommitFiring(const Match& match, JoinCase& current_case) noexcept;
    ScheduledReaction CreateScheduledReaction(const Firing& firing) noexcept;
    ExecutionResult ExecuteReaction(const ScheduledReaction& reaction) noexcept;
    
    void CleanUpQueues() noexcept;
    bool CheckQueueAliveById(uint64_t channel_id) noexcept;
    bool CheckQueueReadyById(uint64_t channel_id) noexcept;
    QueuesMap::iterator GetQueueById(uint64_t channel_id) noexcept;

    std::list<JoinCase> cases;
    std::deque<ScheduledReaction> scheduled_reactions_;  // CHANGED: Use ScheduledReaction
    QueuesMap queues;
    size_t cycle_offset;
    uint64_t next_id;
    uint64_t next_join_case_id_;  // NEW: For join case IDs

    std::atomic<bool> is_complete;
    std::atomic<std::ptrdiff_t> active_threads;
    std::recursive_mutex lock;
    std::counting_semaphore<max_schedulled_calls> calls_semaphore;
    std::unordered_map<uint64_t, Runnable*> runnable_map_;
    
    // NEW: System components
    RepositoryLifecycle lifecycle_;
    Pointer<EventEmitter> event_emitter_;
    ErrorHandler error_handler_;
};
```

---

### Phase 4: Refactor CheckCase (Use Firing Model)

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Current Implementation (to be replaced):**

```cpp
bool CycleRepository::CheckCase(JoinCase& current_case) noexcept {
    bool is_ready = std::all_of(...);
    bool will_destroy_case = std::any_of(...);
    
    if (is_ready && !will_destroy_case) {
        Objects inputs;
        // Pop messages
        calls.push_back({std::move(inputs), current_case.context, 
                        runnable_map_[current_case.runnable_id]});
        calls_semaphore.release();
    }
    return will_destroy_case;
}
```

**New Implementation (using firing model):**

```cpp
bool CycleRepository::CheckCase(JoinCase& current_case) noexcept {
    // Phase 1: Detect Match
    auto maybe_match = DetectMatch(current_case);
    if (!maybe_match.has_value()) {
        // No match - check if case should be destroyed
        bool will_destroy = std::any_of(
            current_case.input_ids.begin(),
            current_case.input_ids.end(),
            [this](uint64_t channel_id) {
                return !CheckQueueAliveById(channel_id);
            });
        
        if (will_destroy) {
            event_emitter_->EmitJoinCaseRemoved(
                current_case.runnable_id, current_case.input_ids);
        }
        return will_destroy;
    }
    
    // Phase 2: Commit Firing
    auto maybe_firing = CommitFiring(maybe_match.value(), current_case);
    if (!maybe_firing.has_value()) {
        // Firing failed (race condition)
        return false;
    }
    
    // Phase 3: Schedule Reaction
    auto scheduled = CreateScheduledReaction(maybe_firing.value());
    
    // Phase 4: Add to execution queue
    {
        auto guard = std::lock_guard(lock);
        scheduled_reactions_.push_back(scheduled);
        calls_semaphore.release();
    }
    
    // Check if case should be destroyed after firing
    bool will_destroy = std::any_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) {
            return !CheckQueueAliveById(channel_id);
        });
    
    return will_destroy;
}

Maybe<Match> CycleRepository::DetectMatch(JoinCase& current_case) noexcept {
    // Check if all channels are ready
    bool is_ready = std::all_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) {
            return CheckQueueReadyById(channel_id);
        });
    
    if (!is_ready) {
        return {};  // No match
    }
    
    // Check if all channels are alive
    bool all_alive = std::all_of(
        current_case.input_ids.begin(),
        current_case.input_ids.end(),
        [this](uint64_t channel_id) {
            return CheckQueueAliveById(channel_id);
        });
    
    if (!all_alive) {
        event_emitter_->EmitMatchFailed(
            current_case.runnable_id,
            "One or more input channels are closed");
        return {};  // No match
    }
    
    // Create match
    Match match{
        .match_id = IDGenerator::Instance().NextMatchID(),
        .join_case_id = current_case.runnable_id,
        .input_channel_ids = current_case.input_ids,
        .detected_at = std::chrono::steady_clock::now()
    };
    
    event_emitter_->EmitMatchDetected(match);
    return match;
}

Maybe<Firing> CycleRepository::CommitFiring(
    const Match& match, JoinCase& current_case) noexcept {
    
    // Atomically consume messages from all channels
    Objects consumed_messages;
    consumed_messages.reserve(current_case.input_ids.size());
    
    for (const auto& channel_id : current_case.input_ids) {
        auto queue_it = GetQueueById(channel_id);
        if (queue_it->second->Empty()) {
            // Race condition - messages consumed by another thread
            // Put back any messages we already consumed
            // (In practice, this shouldn't happen due to locking)
            return {};
        }
        consumed_messages.push_back(queue_it->second->PopFront());
        
        // Notify channel if queue is now empty
        if (queue_it->second->Empty()) {
            // Find channel and notify
            // (Implementation depends on how we track channels)
        }
    }
    
    // Create firing
    Firing firing{
        .firing_id = IDGenerator::Instance().NextFiringID(),
        .match = match,
        .consumed_messages = std::move(consumed_messages),
        .context = current_case.context,
        .runnable_id = current_case.runnable_id,
        .fired_at = std::chrono::steady_clock::now()
    };
    
    event_emitter_->EmitFiringCommitted(firing);
    return firing;
}

ScheduledReaction CycleRepository::CreateScheduledReaction(
    const Firing& firing) noexcept {
    
    ScheduledReaction reaction{
        .reaction_id = IDGenerator::Instance().NextReactionID(),
        .firing = firing,
        .runnable = runnable_map_[firing.runnable_id],
        .scheduled_at = std::chrono::steady_clock::now()
    };
    
    event_emitter_->EmitReactionScheduled(reaction);
    return reaction;
}

ExecutionResult CycleRepository::ExecuteReaction(
    const ScheduledReaction& reaction) noexcept {
    
    auto started_at = std::chrono::steady_clock::now();
    event_emitter_->EmitReactionStarted(reaction.reaction_id);
    
    ExecutionResult result{
        .reaction_id = reaction.reaction_id,
        .status = ExecutionStatus::Success,
        .error_message = {},
        .exception = {},
        .started_at = started_at,
        .completed_at = {},
        .duration = {}
    };
    
    try {
        // Execute the reaction
        reaction.runnable->operator()(
            reaction.firing.consumed_messages,
            reaction.firing.context);
        
        result.completed_at = std::chrono::steady_clock::now();
        result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            result.completed_at - result.started_at);
        result.status = ExecutionStatus::Success;
        
        event_emitter_->EmitReactionCompleted(result);
        
    } catch (...) {
        result.completed_at = std::chrono::steady_clock::now();
        result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            result.completed_at - result.started_at);
        result.status = ExecutionStatus::Failed;
        result.exception = std::current_exception();
        
        // Extract error message
        try {
            std::rethrow_exception(result.exception.value());
        } catch (const std::exception& e) {
            result.error_message = e.what();
        } catch (...) {
            result.error_message = "Unknown exception";
        }
        
        event_emitter_->EmitReactionFailed(result);
        
        // Handle error according to policy
        error_handler_.HandleReactionError(reaction, result.exception.value());
    }
    
    return result;
}
```

---

### Phase 5: Update RunRoutine (Use ExecuteReaction)

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Current Implementation:**

```cpp
void CycleRepository::RunRoutine() noexcept {
    while (true) {
        calls_semaphore.acquire();
        if (is_complete.load()) {
            return;
        }

        SchedulledCall call;
        {
            auto guard = std::lock_guard(lock);
            debug::runtime_assert(!calls.empty(), "scheduled routine queue is empty");
            call = std::move(calls.front());
            calls.pop_front();
            ++active_threads;
        }
        call.runnable->operator()(call.inputs, call.context);
        --active_threads;
    }
}
```

**New Implementation:**

```cpp
void CycleRepository::RunRoutine() noexcept {
    while (true) {
        calls_semaphore.acquire();
        if (is_complete.load()) {
            return;
        }

        ScheduledReaction reaction;
        {
            auto guard = std::lock_guard(lock);
            debug::runtime_assert(!scheduled_reactions_.empty(), 
                                  "scheduled routine queue is empty");
            reaction = std::move(scheduled_reactions_.front());
            scheduled_reactions_.pop_front();
            ++active_threads;
        }
        
        // Execute reaction with error handling
        ExecutionResult result = ExecuteReaction(reaction);
        
        --active_threads;
    }
}
```

---

### Phase 6: Update Run Method (Lifecycle Integration)

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Changes Required:**

```cpp
void CycleRepository::Run(uint64_t main_runnable_id, 
                          std::unordered_map<uint64_t, Runnable*> runnable_map) {
    runnable_map_ = std::move(runnable_map);
    auto main_runnable_it = runnable_map_.find(main_runnable_id);

    debug::runtime_assert(main_runnable_it != runnable_map_.end(), 
                          "main runnable not found");
    debug::runtime_assert(main_runnable_it->second != nullptr, 
                          "main runnable pointer is nullptr");

    // NEW: Transition to Running state
    lifecycle_.Start();
    event_emitter_->EmitRepositoryStarted();

    is_complete.store(false);
    cycle_offset = 0;

    std::vector<std::thread> runner_threads;
    runner_threads.reserve(max_runner_threads);

    {
        auto guard = std::lock_guard(lock);
        for (auto i = 0; i < max_runner_threads; ++i) {
            runner_threads.emplace_back(
                std::bind(&CycleRepository::RunRoutine, this));
        }

        // Schedule main runnable
        Firing main_firing{
            .firing_id = IDGenerator::Instance().NextFiringID(),
            .match = Match{
                .match_id = IDGenerator::Instance().NextMatchID(),
                .join_case_id = main_runnable_id,
                .input_channel_ids = {},
                .detected_at = std::chrono::steady_clock::now()
            },
            .consumed_messages = {},
            .context = {},
            .runnable_id = main_runnable_id,
            .fired_at = std::chrono::steady_clock::now()
        };
        
        scheduled_reactions_.push_back(CreateScheduledReaction(main_firing));
        calls_semaphore.release();
    }

    // Main scheduling loop
    while (CheckCases()) {
        // NEW: Check if shutdown requested
        if (lifecycle_.ShouldTerminate()) {
            break;
        }
    }

    // NEW: Begin shutdown
    lifecycle_.BeginShutdown();
    event_emitter_->EmitRepositoryShuttingDown();

    is_complete.store(true);
    for (auto i = 0; i < max_runner_threads; ++i) {
        calls_semaphore.release();
    }
    for (auto& runner_thread : runner_threads) {
        runner_thread.join();
    }
    
    // NEW: Mark completed or failed
    if (error_handler_.HasErrors() && 
        error_handler_.GetPolicy() == ErrorPolicy::FailFast) {
        lifecycle_.MarkFailed("Reactions failed with FailFast policy");
        event_emitter_->EmitRepositoryFailed("Reactions failed");
    } else {
        lifecycle_.MarkCompleted();
        event_emitter_->EmitRepositoryCompleted();
    }
}

// NEW: Shutdown method
void CycleRepository::Shutdown() noexcept {
    lifecycle_.BeginShutdown();
}

// NEW: Wait for completion
void CycleRepository::WaitForCompletion() noexcept {
    while (!lifecycle_.ShouldTerminate()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// NEW: Get state
RepositoryState CycleRepository::GetState() const noexcept {
    return lifecycle_.GetState();
}

// NEW: Event system access
void CycleRepository::SetEventLogger(Pointer<EventLogger> logger) {
    event_emitter_->SetLogger(logger);
}

Pointer<EventLogger> CycleRepository::GetEventLogger() const {
    return event_emitter_->GetLogger();
}

Pointer<EventEmitter> CycleRepository::GetEventEmitter() const {
    return event_emitter_;
}

// NEW: Error handler access
ErrorHandler& CycleRepository::GetErrorHandler() {
    return error_handler_;
}

const ErrorHandler& CycleRepository::GetErrorHandler() const {
    return error_handler_;
}
```

---

### Phase 7: Update Constructor (Initialize New Components)

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Changes Required:**

```cpp
CycleRepository::CycleRepository()
    : cases(),
      scheduled_reactions_(),  // CHANGED
      queues(),
      cycle_offset(0),
      next_id(0),
      next_join_case_id_(0),  // NEW
      is_complete(false),
      active_threads(0),
      lock(),
      calls_semaphore(0),
      lifecycle_(),  // NEW
      event_emitter_(std::make_shared<EventEmitter>()),  // NEW
      error_handler_(ErrorPolicy::IsolateReaction) {}  // NEW
```

---

### Phase 8: Update NewChannel (Emit Events)

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Changes Required:**

```cpp
Pointer<ChannelBase> CycleRepository::NewChannel(ChannelMode mode,
                                                  Type payload_type) {
    auto guard = std::lock_guard(lock);

    QueuePointer queue_ptr = std::make_shared<MessageQueue>();
    auto channel = std::make_shared<CycleChannel>(
        mode, std::move(payload_type), next_id,
        std::make_shared<Callback>(next_id, queue_ptr));

    queues[next_id] = std::move(queue_ptr);
    
    // NEW: Emit channel created event
    event_emitter_->EmitChannelCreated(next_id, mode, channel->payload_type());
    
    ++next_id;

    return channel;
}
```

---

### Phase 9: Update RegisterJoinCase (Emit Events)

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Changes Required:**

```cpp
void CycleRepository::RegisterJoinCase(Channels inputs, Objects context, 
                                       uint64_t runnable_id) {
    auto guard = std::lock_guard(lock);

    IDs input_ids;
    input_ids.reserve(inputs.size());
    for (const auto& input : inputs) {
        debug::runtime_assert(
            input.use_count() > 0,
            "case inputs cannot be null when registering case");
        input_ids.push_back(input->GetID());
    }
    
    uint64_t join_case_id = next_join_case_id_++;  // NEW
    
    cases.push_back({.input_ids = std::move(input_ids),
                     .context = std::move(context),
                     .runnable_id = runnable_id});
    
    // NEW: Emit join case registered event
    event_emitter_->EmitJoinCaseRegistered(join_case_id, input_ids);
}
```

---

### Phase 10: Update Callback::OnMessage (Emit Events)

#### File: [`runtime/reactor/parallel/repository.cpp`](../runtime/reactor/parallel/repository.cpp:1)

**Changes Required:**

```cpp
void Callback::OnMessage(uint64_t id, const Object& message) noexcept {
    debug::runtime_assert(id == expected_id,
                          "received id does not match expected channel id");
    queue->Push(message);
    
    // NEW: Emit message sent event
    // Note: Need access to event emitter - may need to pass it to Callback
    // Alternative: Emit from CycleChannel::Push instead
}
```

**Better approach - emit from CycleChannel::Push:**

```cpp
void CycleChannel::Push(const Object& message) {
    if (!CanAcceptMessages()) {
        debug::runtime_assert(false, "Cannot push to closed channel");
        return;
    }
    
    auto maybe_callback = GetCallback();
    debug::runtime_assert(bool(maybe_callback), "channel callback is not installed");
    
    // NEW: Emit message sent event (need access to event emitter)
    // This requires passing event emitter to channel or storing it
    
    maybe_callback->OnMessage(id_, message);
}
```

---

## Testing Strategy

### Unit Tests

Create test files in `tests/runtime/reactor/`:

#### 1. `test_lifecycle.cpp`

```cpp
#include <runtime/reactor/common/lifecycle.hpp>
#include <gtest/gtest.h>

TEST(ChannelLifecycleTest, InitialState) {
    reactor::ChannelLifecycle lifecycle;
    EXPECT_EQ(lifecycle.GetState(), reactor::ChannelState::Active);
    EXPECT_TRUE(lifecycle.CanAcceptMessages());
    EXPECT_TRUE(lifecycle.CanConsumeMessages());
}

TEST(ChannelLifecycleTest, CloseTransition) {
    reactor::ChannelLifecycle lifecycle;
    lifecycle.Close();
    EXPECT_EQ(lifecycle.GetState(), reactor::ChannelState::Closing);
    EXPECT_FALSE(lifecycle.CanAcceptMessages());
    EXPECT_TRUE(lifecycle.CanConsumeMessages());
}

// Add more tests...
```

#### 2. `test_firing.cpp`

```cpp
#include <runtime/reactor/common/firing.hpp>
#include <gtest/gtest.h>

TEST(FiringModelTest, IDGeneration) {
    auto& gen = reactor::IDGenerator::Instance();
    auto id1 = gen.NextMatchID();
    auto id2 = gen.NextMatchID();
    EXPECT_NE(id1, id2);
    EXPECT_GT(id2, id1);
}

TEST(FiringModelTest, MatchCreation) {
    reactor::Match match{
        .match_id = 1,
        .join_case_id = 100,
        .input_channel_ids = {1, 2, 3},
        .detected_at = std::chrono::steady_clock::now()
    };
    
    EXPECT_EQ(match.match_id, 1);
    EXPECT_EQ(match.join_case_id, 100);
    EXPECT_EQ(match.input_channel_ids.size(), 3);
}

// Add more tests...
```

#### 3. `test_events.cpp`

```cpp
#include <runtime/reactor/common/events.hpp>
#include <runtime/reactor/common/event_logger.hpp>
#include <gtest/gtest.h>

TEST(EventSystemTest, InMemoryLogger) {
    auto logger = std::make_shared<reactor::InMemoryEventLogger>(100);
    
    auto event = reactor::CreateChannelCreatedEvent(
        1, reactor::ChannelMode::Async, reactor::Type::Int());
    
    logger->Log(event);
    
    auto events = logger->GetEvents();
    EXPECT_EQ(events.size(), 1);
    EXPECT_EQ(events[0].type, reactor::RuntimeEventType::ChannelCreated);
}

// Add more tests...
```

#### 4. `test_error_handler.cpp`

```cpp
#include <runtime/reactor/common/error_handler.hpp>
#include <gtest/gtest.h>

TEST(ErrorHandlerTest, IsolateReactionPolicy) {
    reactor::ErrorHandler handler(reactor::ErrorPolicy::IsolateReaction);
    
    // Create a failed reaction
    reactor::ScheduledReaction reaction{/* ... */};
    
    try {
        throw std::runtime_error("Test error");
    } catch (...) {
        // Should not throw - isolates error
        EXPECT_NO_THROW(
            handler.HandleReactionError(reaction, std::current_exception())
        );
    }
    
    EXPECT_TRUE(handler.HasErrors());
    EXPECT_EQ(handler.GetErrorCount(), 1);
}

// Add more tests...
```

### Integration Tests

#### 1. `test_integration_simple.cpp`

Test a