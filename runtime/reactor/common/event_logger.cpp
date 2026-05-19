#include "event_logger.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>

namespace reactor {

// ============================================================================
// InMemoryEventLogger Implementation
// ============================================================================

InMemoryEventLogger::InMemoryEventLogger(size_t max_events)
    : max_events_(max_events) {
    if (max_events == 0) {
        throw std::invalid_argument("max_events must be greater than 0");
    }
}

void InMemoryEventLogger::Log(const RuntimeEvent& event) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // If at capacity, remove oldest event
    if (events_.size() >= max_events_) {
        events_.pop_front();
    }
    
    events_.push_back(event);
}

void InMemoryEventLogger::Flush() {
    // No-op for in-memory logger - events are immediately available
}

std::vector<RuntimeEvent> InMemoryEventLogger::GetEvents() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return std::vector<RuntimeEvent>(events_.begin(), events_.end());
}

std::vector<RuntimeEvent> InMemoryEventLogger::GetEventsByType(RuntimeEventType type) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<RuntimeEvent> result;
    result.reserve(events_.size() / 10);  // Heuristic: assume ~10% match
    
    for (const auto& event : events_) {
        if (event.type == type) {
            result.push_back(event);
        }
    }
    
    return result;
}

std::vector<RuntimeEvent> InMemoryEventLogger::GetEventsInRange(
    std::chrono::steady_clock::time_point start,
    std::chrono::steady_clock::time_point end) const {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<RuntimeEvent> result;
    result.reserve(events_.size() / 2);  // Heuristic: assume ~50% match
    
    for (const auto& event : events_) {
        if (event.timestamp >= start && event.timestamp <= end) {
            result.push_back(event);
        }
    }
    
    return result;
}

std::vector<RuntimeEvent> InMemoryEventLogger::GetEventsWhere(
    std::function<bool(const RuntimeEvent&)> predicate) const {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<RuntimeEvent> result;
    result.reserve(events_.size() / 2);  // Heuristic
    
    for (const auto& event : events_) {
        if (predicate(event)) {
            result.push_back(event);
        }
    }
    
    return result;
}

void InMemoryEventLogger::Clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    events_.clear();
}

size_t InMemoryEventLogger::Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return events_.size();
}

size_t InMemoryEventLogger::Capacity() const noexcept {
    return max_events_;
}

bool InMemoryEventLogger::Empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return events_.empty();
}

// ============================================================================
// CallbackEventLogger Implementation
// ============================================================================

CallbackEventLogger::CallbackEventLogger(Callback callback)
    : callback_(std::move(callback)) {
    if (!callback_) {
        throw std::invalid_argument("callback must not be null");
    }
}

void CallbackEventLogger::Log(const RuntimeEvent& event) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    try {
        callback_(event);
    } catch (...) {
        // Catch and ignore exceptions from callback to prevent disrupting runtime
        // In production, might want to log this error somewhere
    }
}

void CallbackEventLogger::Flush() {
    // No-op for callback logger - events are processed immediately
}

// ============================================================================
// CompositeEventLogger Implementation
// ============================================================================

void CompositeEventLogger::AddLogger(Pointer<EventLogger> logger) {
    if (!logger) {
        throw std::invalid_argument("logger must not be null");
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    loggers_.push_back(std::move(logger));
}

bool CompositeEventLogger::RemoveLogger(Pointer<EventLogger> logger) {
    if (!logger) {
        return false;
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = std::find(loggers_.begin(), loggers_.end(), logger);
    if (it != loggers_.end()) {
        loggers_.erase(it);
        return true;
    }
    
    return false;
}

void CompositeEventLogger::Log(const RuntimeEvent& event) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Forward to all loggers, catching exceptions to ensure all loggers get the event
    for (const auto& logger : loggers_) {
        try {
            logger->Log(event);
        } catch (...) {
            // Catch and ignore exceptions to prevent one logger from affecting others
        }
    }
}

void CompositeEventLogger::Flush() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Flush all loggers
    for (const auto& logger : loggers_) {
        try {
            logger->Flush();
        } catch (...) {
            // Catch and ignore exceptions
        }
    }
}

size_t CompositeEventLogger::LoggerCount() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return loggers_.size();
}

void CompositeEventLogger::Clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    loggers_.clear();
}

// ============================================================================
// FileEventLogger Implementation
// ============================================================================

FileEventLogger::FileEventLogger(const std::string& filename, bool append)
    : filename_(filename), is_open_(false) {
    
    auto mode = append ? (std::ios::out | std::ios::app) : std::ios::out;
    file_.open(filename, mode);
    
    if (!file_.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    
    is_open_ = true;
}

FileEventLogger::~FileEventLogger() noexcept {
    try {
        Close();
    } catch (...) {
        // Ignore exceptions in destructor
    }
}

void FileEventLogger::Log(const RuntimeEvent& event) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!is_open_) {
        return;  // Silently ignore if file is closed
    }
    
    try {
        file_ << event.ToJSON() << '\n';
    } catch (...) {
        // Catch and ignore write errors to prevent disrupting runtime
    }
}

void FileEventLogger::Flush() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!is_open_) {
        return;
    }
    
    try {
        file_.flush();
    } catch (...) {
        // Catch and ignore flush errors
    }
}

void FileEventLogger::Close() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!is_open_) {
        return;
    }
    
    try {
        file_.flush();
        file_.close();
        is_open_ = false;
    } catch (...) {
        is_open_ = false;
        throw;
    }
}

bool FileEventLogger::IsOpen() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return is_open_;
}

}  // namespace reactor
