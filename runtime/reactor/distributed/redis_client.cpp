#include "redis_client.hpp"
#include "redis_scripts/_headers/_scripts.hpp"

#include <boost/asio/use_future.hpp>
// do not include this in any other .cpp or .hpp file
#include <boost/redis/src.hpp>

#include <iostream>
#include <atomic>
#include <vector>

namespace reactor::redis {

namespace {

inline std::string SerializeObject(const Object& obj) {
    return obj.Serialize();
}

inline Object DeserializeObject(const std::string& str) {
    return Object::Deserialize(str);
}

// TODO: Add better node generator
inline std::string GenNode(const std::string& base) {
    static std::atomic<uint64_t> counter{0};
    return base + ":node:" + std::to_string(counter++);
}

} // namespace

RedisClient::RedisClient(Pointer<connection> conn_ptr)
    : conn_ptr_(conn_ptr) {}

awaitable<void> RedisClient::NewChannel(const std::string& channel_id) {
    auto node = GenNode(channel_id);

    request req;
    req.push("EVAL", scripts::kNewChannelScript, "2", channel_id, node);
    response<bool> resp;

    co_await conn_ptr_->async_exec(req, resp);
    co_return;
}

awaitable<void> RedisClient::PushToChannel(const std::string& channel_id, const Object& object) {
    auto attrs = co_await GetAttributes({channel_id}, {"tail"});
    auto expected_tail = attrs[channel_id][0];
    auto new_tail = GenNode(channel_id);

    request req;
    req.push("EVAL", scripts::kPushScript, "3", expected_tail, new_tail, channel_id, SerializeObject(object));

    response<bool> resp;
    co_await conn_ptr_->async_exec(req, resp);
    // TODO: check resp & retry
    co_return;
}

awaitable<void> RedisClient::NewExecQueue(const std::string& exec_queue_id) {
    request req;

    auto node = GenNode(exec_queue_id);

    req.push("EVAL", scripts::kNewExecQueueScript, "2", exec_queue_id, node);

    response<bool> resp;
    co_await conn_ptr_->async_exec(req, resp);
    co_return;
}

awaitable<Objects> RedisClient::ScheduleExecution(
    const std::string& exec_queue_id,
    const std::vector<std::string>& channel_ids
) {
    // TODO: check for errors
    Objects result;
    std::vector<std::string> raw_result;

    {
        // TODO: reserve correct size
        std::vector<std::string_view> command;
        command.push_back(scripts::kScheduleScript);

        int key_count = 3 + static_cast<int>(channel_ids.size()) * 2;
        auto key_count_as_string = std::to_string(key_count);
        command.push_back(key_count_as_string);

        auto exec_queue_attrs = co_await GetAttributes({exec_queue_id}, {"tail"});
        command.push_back(exec_queue_attrs[exec_queue_id][0]);
        auto new_node = GenNode(exec_queue_id);
        command.push_back(new_node);
        command.push_back(exec_queue_id);

        auto channels_attrs = co_await GetAttributes(channel_ids, {"head"});
        for (auto& channel_id : channel_ids) {
            command.push_back(channels_attrs[channel_id][0]);
            command.push_back(channel_id);
        }

        request req;
        req.push_range("EVAL", command);
        response<std::vector<std::string>> resp;

        co_await conn_ptr_->async_exec(req, resp);
        raw_result = std::move(std::get<0>(resp).value());
    }

    result.reserve(raw_result.size());
    for (const auto& raw_result_entry : raw_result) {
        result.emplace_back(DeserializeObject(raw_result_entry));
    }

    co_return result;
}

awaitable<void> RedisClient::CommitExecution(
    const std::string& exec_queue_id,
    const std::map<std::string, Objects>& channel_msgs_map
) {
    // TODO: check for errors

    // TODO: reserve correct size
    std::vector<std::string_view> command;

    size_t n = channel_msgs_map.size();
    size_t k = 0;
    std::vector<std::string> channel_ids;
    channel_ids.reserve(channel_msgs_map.size());
    for (const auto& [channel_id, msgs] : channel_msgs_map) {
        channel_ids.push_back(channel_id);
        k += msgs.size();
    }

    command.push_back(scripts::kCommitScript);

    size_t key_count = 2 + n * 2 + k;
    auto key_count_as_string = std::to_string(key_count);
    command.push_back(key_count_as_string);

    // exec queue
    auto exec_queue_attrs = co_await GetAttributes({exec_queue_id}, {"head"});
    command.push_back(exec_queue_attrs[exec_queue_id][0]);
    command.push_back(exec_queue_id);

    auto channels_attrs = co_await GetAttributes(channel_ids, {"tail"});
    for (const auto& channel_id : channel_ids) {
        command.push_back(channels_attrs[channel_id][0]);
        command.push_back(channel_id);
    }

    std::vector<std::string> new_nodes;
    for (auto& [channel, _] : channel_msgs_map) {
        new_nodes.push_back(GenNode(channel));
        command.push_back(new_nodes.back());
    }

    auto channel_count_as_string = std::to_string(n);
    command.push_back(channel_count_as_string);

    std::vector<std::string> serialized_objects;
    for (const auto& [_, msgs] : channel_msgs_map) {
        for (const auto& msg : msgs) {
            serialized_objects.push_back(SerializeObject(msg));
            command.push_back(serialized_objects.back());
        }
    }

    request req;
    req.push_range("EVAL", command);
    response<bool> resp;
    co_await conn_ptr_->async_exec(req, resp);
    co_return;
}

awaitable<KeyToAttrsMap> RedisClient::GetAttributes(const Keys& keys, const AttrNames& attribute_names) {
    KeyToAttrsMap result;
    std::vector<std::string> raw_result;

    {
        // TODO: reserve correct size
        std::vector<std::string_view> command;
        command.push_back(scripts::kGetAttributesScript);
        auto key_count_as_string = std::to_string(keys.size());
        command.push_back(key_count_as_string);
        for (const auto& key : keys) {
            command.push_back(key);
        }
        for (const auto& attribute : attribute_names) {
            command.push_back(attribute);
        }

        request req;
        req.push_range("EVAL", command);
        boost::redis::response<std::vector<std::string>> resp;

        co_await conn_ptr_->async_exec(req, resp);

        raw_result = std::move(std::get<0>(resp).value());
    }

    size_t index = 0;
    for (const auto& key : keys) {
        for (const auto& _ : attribute_names) {
            result[key].push_back(raw_result[index]);
            ++index;
        }
    }

    co_return result;
}

} // namespace reactor::redis