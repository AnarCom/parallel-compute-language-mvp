#pragma once

#include <deque>
#include <fstream>
#include <functional>
#include <mutex>
#include <vector>

#include "events.hpp"
#include "helpers.hpp"

namespace reactor {

/**
 * @brief Abstract interface for event logging.
 * 
 * EventLogger defines the contract for logging runtime events. Implementations
 * can store events in memory, write to files, send to external systems, or
 * invoke callbacks.
 * 
 * Thread Safety: Implementations must be thread-safe as events can be logged
 * from multiple threads concurrently.
 */
class EventLogger {
public:
    /**
     * @brief Virtual destructor for proper cleanup.
     */
    virtual ~EventLogger() noexcept = default;
    
    /**
     * @brief Log a runtime event.
     * 
     * This method must be thread-safe and should not block for extended periods.
     * 
     * @param event The event to log.
     */
    virtual void Log(const RuntimeEvent& event) = 0;
    
    /**
     * @brief Flush any buffered events.
     * 
     * Ensures all logged events are persisted or processed. This may block
     * until all pending events are handled.
     */
    virtual void Flush() = 0;
};

/**
 * @brief In-memory event logger with bounded storage.
 * 
 * InMemoryEventLogger stores events in a thread-safe deque with a maximum
 * capacity. When the capacity is reached, the oldest events are discarded
 * (FIFO behavior).
 * 
 * This logger is suitable for:
 * - Development and debugging
 * - Short-lived programs
 * - Post-mortem analysis of recent events
 * 
 * Thread Safety: All methods are thread-safe using mutex protection.
 * 
 * Example:
 * @code
 * auto logger = std::make_shared<InMemoryEventLogger>(1000);
 * // ... log events ...
 * auto events = logger->GetEvents();
 * for (const auto& event : events) {
 *     std::cout << event.ToString() << std::endl;
 * }
 * @endcode
 */
class InMemoryEventLogger : public EventLogger {
public:
    /**
     * @brief Construct an in-memory logger with specified capacity.
     * 
     * @param max_events Maximum number of events to store. When exceeded,
     *                   oldest events are discarded. Default is 10000.
     */
    explicit InMemoryEventLogger(size_t max_events = 10000);
    
    /**
     * @brief Destructor.
     */
    ~InMemoryEventLogger() noexcept override = default;
    
    /**
     * @brief Log an event to memory.
     * 
     * Thread-safe. If capacity is reached, the oldest event is removed.
     * 
     * @param event The event to log.
     */
    void Log(const RuntimeEvent& event) override;
    
    /**
     * @brief Flush is a no-op for in-memory logger.
     * 
     * Events are immediately available after Log() is called.
     */
    void Flush() override;
    
    /**
     * @brief Get all stored events.
     * 
     * Returns a copy of all events currently in the logger.
     * Thread-safe.
     * 
     * @return Vector of all stored events in chronological order.
     */
    std::vector<RuntimeEvent> GetEvents() const;
    
    /**
     * @brief Get events of a specific type.
     * 
     * Filters and returns only events matching the specified type.
     * Thread-safe.
     * 
     * @param type The event type to filter by.
     * @return Vector of matching events in chronological order.
     */
    std::vector<RuntimeEvent> GetEventsByType(RuntimeEventType type) const;
    
    /**
     * @brief Get events within a time range.
     * 
     * Returns events that occurred between start and end timestamps (inclusive).
     * Thread-safe.
     * 
     * @param start Start of time range.
     * @param end End of time range.
     * @return Vector of events within the time range in chronological order.
     */
    std::vector<RuntimeEvent> GetEventsInRange(
        std::chrono::steady_clock::time_point start,
        std::chrono::steady_clock::time_point end) const;
    
    /**
     * @brief Get events matching a predicate.
     * 
     * Returns events for which the predicate returns true.
     * Thread-safe.
     * 
     * @param predicate Function that returns true for events to include.
     * @return Vector of matching events in chronological order.
     */
    std::vector<RuntimeEvent> GetEventsWhere(
        std::function<bool(const RuntimeEvent&)> predicate) const;
    
    /**
     * @brief Clear all stored events.
     * 
     * Thread-safe.
     */
    void Clear();
    
    /**
     * @brief Get the current number of stored events.
     * 
     * Thread-safe.
     * 
     * @return Number of events currently stored.
     */
    size_t Size() const;
    
    /**
     * @brief Get the maximum capacity.
     * 
     * @return Maximum number of events that can be stored.
     */
    size_t Capacity() const noexcept;
    
    /**
     * @brief Check if the logger is empty.
     * 
     * Thread-safe.
     * 
     * @return True if no events are stored, false otherwise.
     */
    bool Empty() const;

private:
    mutable std::mutex mutex_;
    std::deque<RuntimeEvent> events_;
    size_t max_events_;
};

/**
 * @brief Event logger that invokes a callback for each event.
 * 
 * CallbackEventLogger allows custom event processing by invoking a user-provided
 * callback function for each logged event. This is useful for:
 * - Writing events to files
 * - Sending events to external monitoring systems
 * - Custom filtering and processing
 * - Real-time event notifications
 * 
 * Thread Safety: The callback is invoked synchronously within Log(), so the
 * callback itself must be thread-safe if events are logged from multiple threads.
 * 
 * Example:
 * @code
 * auto logger = std::make_shared<CallbackEventLogger>(
 *     [](const RuntimeEvent& event) {
 *         std::cout << event.ToJSON() << std::endl;
 *     }
 * );
 * @endcode
 */
class CallbackEventLogger : public EventLogger {
public:
    /**
     * @brief Callback function type.
     * 
     * The callback receives a const reference to each logged event.
     * It should not throw exceptions.
     */
    using Callback = std::function<void(const RuntimeEvent&)>;
    
    /**
     * @brief Construct a callback logger.
     * 
     * @param callback Function to invoke for each logged event.
     *                 Must not be null.
     */
    explicit CallbackEventLogger(Callback callback);
    
    /**
     * @brief Destructor.
     */
    ~CallbackEventLogger() noexcept override = default;
    
    /**
     * @brief Log an event by invoking the callback.
     * 
     * The callback is invoked synchronously. If the callback throws,
     * the exception is caught and ignored to prevent disrupting the runtime.
     * 
     * @param event The event to log.
     */
    void Log(const RuntimeEvent& event) override;
    
    /**
     * @brief Flush is a no-op for callback logger.
     * 
     * Events are processed immediately in Log().
     */
    void Flush() override;

private:
    Callback callback_;
    mutable std::mutex mutex_;
};

/**
 * @brief Event logger that forwards events to multiple loggers.
 * 
 * CompositeEventLogger allows combining multiple event loggers, forwarding
 * each event to all registered loggers. This is useful for:
 * - Logging to multiple destinations simultaneously
 * - Combining in-memory logging with file logging
 * - Separating concerns (e.g., one logger for metrics, one for debugging)
 * 
 * Thread Safety: All methods are thread-safe. Events are forwarded to child
 * loggers sequentially while holding a lock.
 * 
 * Example:
 * @code
 * auto composite = std::make_shared<CompositeEventLogger>();
 * composite->AddLogger(std::make_shared<InMemoryEventLogger>());
 * composite->AddLogger(std::make_shared<CallbackEventLogger>(
 *     [](const auto& e) { std::cout << e.ToJSON() << std::endl; }
 * ));
 * @endcode
 */
class CompositeEventLogger : public EventLogger {
public:
    /**
     * @brief Construct an empty composite logger.
     */
    CompositeEventLogger() = default;
    
    /**
     * @brief Destructor.
     */
    ~CompositeEventLogger() noexcept override = default;
    
    /**
     * @brief Add a logger to the composite.
     * 
     * The logger will receive all future events. Thread-safe.
     * 
     * @param logger The logger to add. Must not be null.
     */
    void AddLogger(Pointer<EventLogger> logger);
    
    /**
     * @brief Remove a logger from the composite.
     * 
     * The logger will no longer receive events. Thread-safe.
     * 
     * @param logger The logger to remove.
     * @return True if the logger was found and removed, false otherwise.
     */
    bool RemoveLogger(Pointer<EventLogger> logger);
    
    /**
     * @brief Log an event to all registered loggers.
     * 
     * Events are forwarded to loggers sequentially. If a logger throws,
     * the exception is caught and ignored, and remaining loggers still
     * receive the event.
     * 
     * Thread-safe.
     * 
     * @param event The event to log.
     */
    void Log(const RuntimeEvent& event) override;
    
    /**
     * @brief Flush all registered loggers.
     * 
     * Calls Flush() on each logger sequentially. Thread-safe.
     */
    void Flush() override;
    
    /**
     * @brief Get the number of registered loggers.
     * 
     * Thread-safe.
     * 
     * @return Number of loggers in the composite.
     */
    size_t LoggerCount() const;
    
    /**
     * @brief Clear all registered loggers.
     * 
     * Thread-safe.
     */
    void Clear();

private:
    std::vector<Pointer<EventLogger>> loggers_;
    mutable std::mutex mutex_;
};

/**
 * @brief File-based event logger that writes events to a file.
 * 
 * FileEventLogger writes events to a file in JSON format, one event per line.
 * This is useful for:
 * - Persistent event storage
 * - Post-mortem analysis
 * - Integration with external analysis tools
 * 
 * Thread Safety: All methods are thread-safe using mutex protection.
 * 
 * Example:
 * @code
 * auto logger = std::make_shared<FileEventLogger>("events.jsonl");
 * // ... log events ...
 * logger->Flush();  // Ensure all events are written
 * @endcode
 */
class FileEventLogger : public EventLogger {
public:
    /**
     * @brief Construct a file logger.
     * 
     * Opens the specified file for writing. If the file exists, it is truncated.
     * If the file cannot be opened, an exception is thrown.
     * 
     * @param filename Path to the output file.
     * @param append If true, append to existing file. If false, truncate file.
     * @throws std::runtime_error if the file cannot be opened.
     */
    explicit FileEventLogger(const std::string& filename, bool append = false);
    
    /**
     * @brief Destructor.
     * 
     * Flushes and closes the file.
     */
    ~FileEventLogger() noexcept override;
    
    /**
     * @brief Log an event to the file.
     * 
     * Writes the event as a JSON line. Thread-safe.
     * 
     * @param event The event to log.
     */
    void Log(const RuntimeEvent& event) override;
    
    /**
     * @brief Flush the file buffer.
     * 
     * Ensures all buffered events are written to disk. Thread-safe.
     */
    void Flush() override;
    
    /**
     * @brief Close the file.
     * 
     * Flushes and closes the file. After closing, Log() calls will be ignored.
     * Thread-safe.
     */
    void Close();
    
    /**
     * @brief Check if the file is open.
     * 
     * Thread-safe.
     * 
     * @return True if the file is open, false otherwise.
     */
    bool IsOpen() const;

private:
    std::string filename_;
    std::ofstream file_;
    mutable std::mutex mutex_;
    bool is_open_;
};

}  // namespace reactor
