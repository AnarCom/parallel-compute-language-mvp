#pragma once

#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/redis/connection.hpp>

#include <runtime/reactor/common/helpers.hpp>
#include <runtime/reactor/common/type_system.hpp>

#include <map>
#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

using boost::asio::awaitable;
using boost::redis::connection;
using boost::redis::request;
using boost::redis::response;

namespace reactor::redis {

inline constexpr auto kChannelMessageNotification = "gojo:channel:messages";
inline constexpr auto kReactionCreatedNotification = "gojo:reaction:created";

using Keys = std::vector<std::string>;
using AttrNames = std::vector<std::string>;
using Attributes = std::vector<std::string>;
using KeyToAttrsMap = std::map<std::string, Attributes>;

struct ReactionMetadata {
    std::string reaction_id;
    std::string exec_queue_id;
    std::vector<std::string> input_channel_ids;
    Objects context;
};

class RedisClient {
public:
    explicit RedisClient(Pointer<connection> conn_ptr);

    awaitable<void> NewChannel(const std::string& channel_id);
    awaitable<void> PushToChannel(const std::string& channel_id, const Object& object);

    awaitable<void> NewExecQueue(const std::string& exec_queue_id);
    awaitable<void> RegisterReaction(const std::string& reaction_id, const std::string& exec_queue_id);
    awaitable<void> RegisterReaction(
        const std::string& reaction_id,
        const std::string& exec_queue_id,
        const std::vector<std::string>& input_channel_ids,
        const Objects& context);
    awaitable<std::vector<std::string>> ListReactions();
    awaitable<ReactionMetadata> GetReactionMetadata(const std::string& reaction_id);

    awaitable<void> RefreshProcessHeartbeat(uint64_t node_id, std::chrono::seconds ttl);
    awaitable<bool> IsProcessHeartbeatAlive(uint64_t node_id);
    awaitable<void> ClearProcessHeartbeat(uint64_t node_id);

    awaitable<Objects> ScheduleExecution(const std::string& exec_queue_id, const std::vector<std::string>& channel_ids);
    awaitable<void> CommitExecution(const std::string& exec_queue_id, const std::map<std::string, Objects>& channel_msgs_map);

    awaitable<KeyToAttrsMap> GetAttributes(const Keys& keys, const AttrNames& attribute_names);

    awaitable<bool> Barrier(std::size_t expected_processes);

private:
    Pointer<connection> conn_ptr_;
};

}  // namespace reactor::redis
