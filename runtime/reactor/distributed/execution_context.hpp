#pragma once

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/common/type_system.hpp>
#include <runtime/reactor/distributed/execution_result.hpp>

namespace reactor {

// Forward declaration
class RedisChannel;

/**
 * @brief Represents a channel created during execution (not yet in Redis).
 * 
 * Stores metadata about a channel that exists only within the execution context
 * until it is committed to Redis.
 */
struct PendingChannel {
    uint64_t temp_id;           ///< Temporary ID (local to this execution)
    ChannelMode mode;           ///< Channel mode (Sync or Async)
    Type payload_type;          ///< Type of messages this channel accepts
    std::string redis_id;       ///< Will be assigned during commit (initially empty)
};

/**
 * @brief Represents a join-case registered during execution.
 * 
 * References channels by their temporary IDs since they may not yet exist in Redis.
 */
struct PendingJoinCase {
    std::vector<uint64_t> input_channel_temp_ids;  ///< References to PendingChannel temp_ids
    Objects context;                                ///< Context objects for the join-case
    uint64_t runnable_id;                          ///< ID of the runnable to execute
};

/**
 * @brief Represents a message pushed during execution.
 * 
 * References the target channel by its temporary ID.
 */
struct PendingPush {
    uint64_t channel_temp_id;   ///< References PendingChannel temp_id
    Object message;             ///< The message object to push
};

/**
 * @brief Thread-local context that records all repository actions during callback execution.
 * 
 * ExecutionContext captures all operations (channel creation, join-case registration,
 * message pushes) performed during a single callback execution. These operations are
 * recorded in memory and later extracted as an ExecutionResult for atomic commit to Redis.
 * 
 * Thread-safety: This class uses a mutex to protect internal state. It is designed to be
 * used via thread-local storage, with one instance per execution thread.
 * 
 * Usage:
 * @code
 * ExecutionContext ctx;
 * ExecutionContextGuard guard(&ctx);  // Sets thread-local context
 * 
 * // Execute callback - all repository operations are recorded
 * runnable->operator()(inputs, context);
 * 
 * // Extract result for commit
 * ExecutionResult result = ctx.ExtractResult();
 * // guard destructor clears thread-local context
 * @endcode
 */
class ExecutionContext {
public:
    /**
     * @brief Construct a new execution context.
     * 
     * Initializes the context with no recorded actions and temp_id counter at 1.
     */
    ExecutionContext();

    /**
     * @brief Destructor.
     */
    ~ExecutionContext();

    /**
     * @brief Record a new channel creation.
     * 
     * Creates a temporary channel proxy that records pushes to this context.
     * The channel does not exist in Redis until the execution is committed.
     * 
     * @param mode Channel mode (Sync or Async)
     * @param payload_type Type of messages this channel accepts
     * @return Pointer to a RedisChannel proxy
     * 
     * Thread-safety: This method is thread-safe.
     */
    Pointer<ChannelBase> RecordNewChannel(ChannelMode mode, Type payload_type);

    /**
     * @brief Record a join-case registration.
     * 
     * Extracts temporary IDs from the input channels and stores the join-case
     * for later registration in Redis.
     * 
     * @param inputs Vector of input channels (must be RedisChannel instances)
     * @param context Context objects for the join-case
     * @param runnable_id ID of the runnable to execute when the join-case fires
     * 
     * @throws std::invalid_argument if any input channel is not a RedisChannel
     * 
     * Thread-safety: This method is thread-safe.
     */
    void RecordJoinCase(const Channels& inputs, const Objects& context, uint64_t runnable_id);

    /**
     * @brief Record a message push.
     * 
     * Stores the message for later push to Redis when the execution is committed.
     * 
     * @param channel_temp_id Temporary ID of the target channel
     * @param message The message object to push
     * 
     * @throws std::invalid_argument if the channel_temp_id is not found
     * 
     * Thread-safety: This method is thread-safe.
     */
    void RecordPush(uint64_t channel_temp_id, const Object& message);

    /**
     * @brief Extract the execution result.
     * 
     * Converts all recorded actions into an immutable ExecutionResult and clears
     * the internal state. This method should be called once after execution completes.
     * 
     * @return ExecutionResult containing all recorded actions
     * 
     * Thread-safety: This method is thread-safe.
     */
    ExecutionResult ExtractResult();

    /**
     * @brief Check if a channel with the given temp_id exists.
     * 
     * @param temp_id Temporary channel ID to check
     * @return true if the channel exists, false otherwise
     * 
     * Thread-safety: This method is thread-safe.
     */
    [[nodiscard]] bool HasChannel(uint64_t temp_id) const;

    /**
     * @brief Get a pending channel by its temporary ID.
     * 
     * @param temp_id Temporary channel ID
     * @return Const reference to the PendingChannel
     * 
     * @throws std::out_of_range if the temp_id is not found
     * 
     * Thread-safety: This method is thread-safe.
     */
    [[nodiscard]] const PendingChannel& GetChannel(uint64_t temp_id) const;

private:
    uint64_t next_temp_id_;                                     ///< Counter for generating temporary IDs
    std::unordered_map<uint64_t, PendingChannel> pending_channels_;  ///< Map of temp_id to pending channel
    std::vector<PendingJoinCase> pending_join_cases_;           ///< List of pending join-cases
    std::vector<PendingPush> pending_pushes_;                   ///< List of pending message pushes
    
    mutable std::mutex mutex_;                                  ///< Protects all internal state
};

/**
 * @brief Thread-local pointer to the current execution context.
 * 
 * This is set by ExecutionContextGuard and used by repository methods to record actions.
 * It is nullptr when not executing within a context.
 */
extern thread_local ExecutionContext* current_execution_context;

/**
 * @brief RAII helper to set and clear the current execution context.
 * 
 * This guard sets the thread-local current_execution_context pointer on construction
 * and restores the previous value on destruction. This ensures proper cleanup even
 * if exceptions are thrown during execution.
 * 
 * Usage:
 * @code
 * ExecutionContext ctx;
 * {
 *     ExecutionContextGuard guard(&ctx);
 *     // current_execution_context is now &ctx
 *     // ... execute callback ...
 * }  // guard destructor restores previous context
 * @endcode
 */
class ExecutionContextGuard {
public:
    /**
     * @brief Construct a guard and set the current execution context.
     * 
     * @param ctx Pointer to the execution context to set (can be nullptr)
     */
    explicit ExecutionContextGuard(ExecutionContext* ctx);

    /**
     * @brief Destructor restores the previous execution context.
     */
    ~ExecutionContextGuard();

    // Non-copyable and non-movable
    ExecutionContextGuard(const ExecutionContextGuard&) = delete;
    ExecutionContextGuard& operator=(const ExecutionContextGuard&) = delete;
    ExecutionContextGuard(ExecutionContextGuard&&) = delete;
    ExecutionContextGuard& operator=(ExecutionContextGuard&&) = delete;

private:
    ExecutionContext* previous_context_;  ///< Previous context to restore on destruction
};

}  // namespace reactor
