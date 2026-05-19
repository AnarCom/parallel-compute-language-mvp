#include "lifecycle.hpp"

#include <stdexcept>

namespace reactor {

// ============================================================================
// ChannelLifecycle Implementation
// ============================================================================

ChannelLifecycle::ChannelLifecycle()
    : state_(ChannelState::Active) {
}

ChannelState ChannelLifecycle::GetState() const noexcept {
    return state_.load(std::memory_order_acquire);
}

bool ChannelLifecycle::CanAcceptMessages() const noexcept {
    return GetState() == ChannelState::Active;
}

bool ChannelLifecycle::CanConsumeMessages() const noexcept {
    ChannelState current = GetState();
    return current == ChannelState::Active ||
           current == ChannelState::Closing ||
           current == ChannelState::Draining;
}

void ChannelLifecycle::Close() noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    ChannelState current = state_.load(std::memory_order_acquire);
    
    // Valid transitions:
    // Active -> Closing
    // Active -> Closed (if queue is empty, handled by caller via OnQueueEmpty)
    // Already Closing/Draining/Closed -> no-op (idempotent)
    
    if (current == ChannelState::Active) {
        state_.store(ChannelState::Closing, std::memory_order_release);
    }
    // If already in Closing, Draining, or Closed state, do nothing (idempotent)
}

void ChannelLifecycle::OnLastReferenceDropped() noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    ChannelState current = state_.load(std::memory_order_acquire);
    
    // Valid transitions:
    // Active -> Draining
    // Closing -> Draining
    // Already Draining/Closed -> no-op (idempotent)
    
    if (current == ChannelState::Active || current == ChannelState::Closing) {
        state_.store(ChannelState::Draining, std::memory_order_release);
    }
    // If already in Draining or Closed state, do nothing (idempotent)
}

void ChannelLifecycle::OnQueueEmpty() noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    ChannelState current = state_.load(std::memory_order_acquire);
    
    // Valid transitions:
    // Draining -> Closed
    // Closing -> Closed
    // Active -> Closed (if Close() was called and queue is now empty)
    // Already Closed -> no-op (idempotent)
    
    if (current == ChannelState::Draining ||
        current == ChannelState::Closing ||
        current == ChannelState::Active) {
        state_.store(ChannelState::Closed, std::memory_order_release);
    }
    // If already in Closed state, do nothing (idempotent)
}

bool ChannelLifecycle::IsActive() const noexcept {
    return GetState() == ChannelState::Active;
}

bool ChannelLifecycle::IsClosed() const noexcept {
    return GetState() == ChannelState::Closed;
}

// ============================================================================
// RepositoryLifecycle Implementation
// ============================================================================

RepositoryLifecycle::RepositoryLifecycle()
    : state_(RepositoryState::Initializing),
      failure_reason_(std::nullopt) {
}

RepositoryState RepositoryLifecycle::GetState() const noexcept {
    return state_.load(std::memory_order_acquire);
}

void RepositoryLifecycle::Start() noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    RepositoryState current = state_.load(std::memory_order_acquire);
    
    // Valid transitions:
    // Initializing -> Running
    // Already Running -> no-op (idempotent)
    
    if (current == RepositoryState::Initializing) {
        state_.store(RepositoryState::Running, std::memory_order_release);
    }
    // If already in Running state, do nothing (idempotent)
}

void RepositoryLifecycle::BeginShutdown() noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    RepositoryState current = state_.load(std::memory_order_acquire);
    
    // Valid transitions:
    // Running -> ShuttingDown
    // Already ShuttingDown/Completed/Failed -> no-op (idempotent)
    
    if (current == RepositoryState::Running) {
        state_.store(RepositoryState::ShuttingDown, std::memory_order_release);
    }
    // If already in ShuttingDown, Completed, or Failed state, do nothing (idempotent)
}

void RepositoryLifecycle::MarkCompleted() noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    RepositoryState current = state_.load(std::memory_order_acquire);
    
    // Valid transitions:
    // ShuttingDown -> Completed
    // Already Completed -> no-op (idempotent)
    
    if (current == RepositoryState::ShuttingDown) {
        state_.store(RepositoryState::Completed, std::memory_order_release);
    }
    // If already in Completed state, do nothing (idempotent)
}

void RepositoryLifecycle::MarkFailed(std::string reason) noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Valid transitions:
    // Any state -> Failed
    // This is the only transition that can happen from any state
    
    state_.store(RepositoryState::Failed, std::memory_order_release);
    failure_reason_ = std::move(reason);
}

bool RepositoryLifecycle::IsRunning() const noexcept {
    return GetState() == RepositoryState::Running;
}

bool RepositoryLifecycle::ShouldTerminate() const noexcept {
    RepositoryState current = GetState();
    return current == RepositoryState::ShuttingDown ||
           current == RepositoryState::Completed ||
           current == RepositoryState::Failed;
}

Maybe<std::string> RepositoryLifecycle::GetFailureReason() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Only return failure reason if in Failed state
    if (state_.load(std::memory_order_acquire) == RepositoryState::Failed) {
        return failure_reason_;
    }
    
    return std::nullopt;
}

// ============================================================================
// ToString Functions
// ============================================================================

std::string ToString(ChannelState state) {
    switch (state) {
        case ChannelState::Active:
            return "Active";
        case ChannelState::Closing:
            return "Closing";
        case ChannelState::Draining:
            return "Draining";
        case ChannelState::Closed:
            return "Closed";
        default:
            return "Unknown";
    }
}

std::string ToString(RepositoryState state) {
    switch (state) {
        case RepositoryState::Initializing:
            return "Initializing";
        case RepositoryState::Running:
            return "Running";
        case RepositoryState::ShuttingDown:
            return "ShuttingDown";
        case RepositoryState::Completed:
            return "Completed";
        case RepositoryState::Failed:
            return "Failed";
        default:
            return "Unknown";
    }
}

}  // namespace reactor
