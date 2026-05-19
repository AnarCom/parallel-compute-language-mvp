#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/common/type_system.hpp>

namespace reactor {

/**
 * @brief Represents a channel creation during execution.
 * 
 * Stores metadata about a channel that was created but not yet persisted to Redis.
 */
struct ChannelCreation {
    uint64_t temp_id;           ///< Temporary ID assigned during execution
    ChannelMode mode;           ///< Channel mode (Sync or Async)
    Type payload_type;          ///< Type of messages this channel accepts
};

/**
 * @brief Represents a join-case registration during execution.
 * 
 * Stores information about a join-case that was registered but not yet persisted to Redis.
 */
struct JoinCaseRegistration {
    std::vector<uint64_t> input_channel_temp_ids;  ///< Temporary IDs of input channels
    Objects context;                                ///< Context objects for the join-case
    uint64_t runnable_id;                          ///< ID of the runnable to execute
};

/**
 * @brief Represents a message push during execution.
 * 
 * Stores information about a message that was pushed but not yet persisted to Redis.
 */
struct MessagePush {
    uint64_t channel_temp_id;   ///< Temporary ID of the target channel
    Object message;             ///< The message object to push
};

/**
 * @brief Immutable snapshot of all repository actions performed during execution.
 * 
 * ExecutionResult captures all channel creations, join-case registrations, and message
 * pushes that occurred during a callback execution. This result is then used to atomically
 * commit all operations to Redis.
 * 
 * Thread-safety: This class is immutable after construction, making it safe to pass
 * between threads without synchronization.
 */
class ExecutionResult {
public:
    /**
     * @brief Default constructor creates an empty result.
     */
    ExecutionResult() = default;
    
    /**
     * @brief Construct from vectors of actions.
     * 
     * @param channels Vector of channel creations
     * @param join_cases Vector of join-case registrations
     * @param pushes Vector of message pushes
     */
    explicit ExecutionResult(
        std::vector<ChannelCreation> channels,
        std::vector<JoinCaseRegistration> join_cases,
        std::vector<MessagePush> pushes
    );

    /**
     * @brief Get all channel creations.
     * @return Const reference to the vector of channel creations
     */
    [[nodiscard]] const std::vector<ChannelCreation>& GetChannels() const noexcept;

    /**
     * @brief Get all join-case registrations.
     * @return Const reference to the vector of join-case registrations
     */
    [[nodiscard]] const std::vector<JoinCaseRegistration>& GetJoinCases() const noexcept;

    /**
     * @brief Get all message pushes.
     * @return Const reference to the vector of message pushes
     */
    [[nodiscard]] const std::vector<MessagePush>& GetPushes() const noexcept;

    /**
     * @brief Prepare a map of Redis channel IDs to messages for atomic commit.
     * 
     * This method groups all message pushes by their target Redis channel ID,
     * using the provided mapping from temporary IDs to Redis IDs.
     * 
     * @param temp_id_to_redis_id Mapping from temporary channel IDs to Redis channel IDs
     * @return Map from Redis channel ID to vector of messages
     * @throws std::logic_error if a temporary ID is not found in the mapping
     */
    [[nodiscard]] std::map<std::string, Objects> PrepareChannelMessagesMap(
        const std::unordered_map<uint64_t, std::string>& temp_id_to_redis_id
    ) const;

    /**
     * @brief Get the number of channels created.
     * @return Number of channel creations
     */
    [[nodiscard]] size_t GetChannelCount() const noexcept;

    /**
     * @brief Get the number of join-cases registered.
     * @return Number of join-case registrations
     */
    [[nodiscard]] size_t GetJoinCaseCount() const noexcept;

    /**
     * @brief Get the number of messages pushed.
     * @return Number of message pushes
     */
    [[nodiscard]] size_t GetPushCount() const noexcept;

    /**
     * @brief Check if this result is empty (no actions recorded).
     * @return true if no actions were recorded, false otherwise
     */
    [[nodiscard]] bool IsEmpty() const noexcept;

    /**
     * @brief Convert the result to a human-readable string for debugging.
     * @return String representation of the execution result
     */
    [[nodiscard]] std::string ToString() const;

private:
    std::vector<ChannelCreation> channels_;
    std::vector<JoinCaseRegistration> join_cases_;
    std::vector<MessagePush> pushes_;
};

}  // namespace reactor
