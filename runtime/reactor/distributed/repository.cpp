#include "repository.hpp"

#include <runtime/reactor/common/logging.hpp>
#include <runtime/reactor/distributed/config.hpp>
#include <runtime/reactor/distributed/redis_client.hpp>
#include "execution_context.hpp"
#include "execution_result.hpp"

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/redis/connection.hpp>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <exception>
#include <future>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace reactor {

namespace {

boost::redis::config MakeBoostRedisConfig(const Config& config) {
    auto redis_config = boost::redis::config{};
    const auto separator = config.RedisAddr.rfind(':');
    if (separator == std::string::npos) {
        throw std::runtime_error("RedisAddr must be formatted as host:port");
    }

    redis_config.addr.host = config.RedisAddr.substr(0, separator);
    redis_config.addr.port = config.RedisAddr.substr(separator + 1);
    redis_config.username = config.RedisUser;
    redis_config.password = config.RedisPassword;
    redis_config.database_index = static_cast<int>(config.RedisDB);
    return redis_config;
}

uint64_t HashKey(std::string_view key) noexcept {
    uint64_t hash = 14695981039346656037ull;
    for (const auto c : key) {
        hash ^= static_cast<unsigned char>(c);
        hash *= 1099511628211ull;
    }
    return hash;
}

constexpr auto kHeartbeatTTL = std::chrono::seconds(3);
constexpr auto kHeartbeatRefreshInterval = std::chrono::seconds(1);
constexpr auto kHeartbeatMonitorInterval = std::chrono::seconds(1);

uint64_t PickNodeByConsistentHash(
    uint64_t reaction_id,
    uint64_t programs_count,
    const std::unordered_set<uint64_t>& excluded_nodes = {}) {
    debug::runtime_assert(programs_count > 0, "consistent hash ring cannot be empty");

    std::vector<std::pair<uint64_t, uint64_t>> ring;
    ring.reserve(programs_count);
    for (uint64_t node_id = 0; node_id != programs_count; ++node_id) {
        if (excluded_nodes.contains(node_id)) {
            continue;
        }
        ring.emplace_back(HashKey("node:" + std::to_string(node_id)), node_id);
    }
    debug::runtime_assert(!ring.empty(), "consistent hash ring cannot contain only failed nodes");
    std::sort(ring.begin(), ring.end());

    const auto reaction_hash = HashKey("reaction:" + std::to_string(reaction_id));
    auto owner = std::lower_bound(
        ring.begin(),
        ring.end(),
        std::pair<uint64_t, uint64_t>{reaction_hash, 0});
    if (owner == ring.end()) {
        owner = ring.begin();
    }

    return owner->second;
}

std::optional<std::string> ConsumeChannelNotification(boost::redis::generic_response& resp) {
    if (resp.has_error() || !resp.has_value()) {
        return {};
    }

    while (!resp.value().empty()) {
        const auto& nodes = resp.value();
        if (nodes.size() >= 4 &&
            nodes[1].value == "message" &&
            nodes[2].value == redis::kChannelMessageNotification) {
            auto channel_id = nodes[3].value;
            boost::redis::consume_one(resp);
            return channel_id;
        }
        boost::redis::consume_one(resp);
    }

    return {};
}

std::optional<std::string> ConsumeReactionNotification(boost::redis::generic_response& resp) {
    if (resp.has_error() || !resp.has_value()) {
        return {};
    }

    while (!resp.value().empty()) {
        const auto& nodes = resp.value();
        if (nodes.size() >= 4 &&
            nodes[1].value == "message" &&
            nodes[2].value == redis::kReactionCreatedNotification) {
            auto reaction_id = nodes[3].value;
            boost::redis::consume_one(resp);
            return reaction_id;
        }
        boost::redis::consume_one(resp);
    }

    return {};
}

std::optional<uint64_t> ParseChannelID(const std::string& channel_id) {
    try {
        return static_cast<uint64_t>(std::stoull(channel_id));
    } catch (std::exception&) {
        return {};
    }
}

DistributedReaction ReactionFromMetadata(const redis::ReactionMetadata& metadata) {
    auto runnable_id = ParseChannelID(metadata.reaction_id);
    if (!runnable_id.has_value()) {
        throw std::runtime_error("reaction id is not numeric: " + metadata.reaction_id);
    }

    IDs input_ids;
    input_ids.reserve(metadata.input_channel_ids.size());
    for (const auto& input_channel_id : metadata.input_channel_ids) {
        auto input_id = ParseChannelID(input_channel_id);
        if (!input_id.has_value()) {
            throw std::runtime_error("reaction input channel id is not numeric: " + input_channel_id);
        }
        input_ids.push_back(*input_id);
    }

    return DistributedReaction{
        .input_ids = std::move(input_ids),
        .context = metadata.context,
        .runnable_id = *runnable_id,
    };
}

template <typename Operation>
void RunRedisOperation(Operation&& operation) {
    boost::asio::io_context redis_ioc;
    auto config = GetConfig();
    auto conn = std::make_shared<boost::redis::connection>(redis_ioc.get_executor());
    auto client = std::make_shared<redis::RedisClient>(conn);
    auto result = std::promise<void>{};
    auto done = result.get_future();

    conn->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);
    boost::asio::co_spawn(
        redis_ioc.get_executor(),
        [conn, client, operation = std::forward<Operation>(operation), &result]() mutable -> boost::asio::awaitable<void> {
            try {
                co_await operation(*client);
                result.set_value();
            } catch (...) {
                result.set_exception(std::current_exception());
            }
            conn->cancel();
            co_return;
        },
        boost::asio::detached);

    redis_ioc.run();
    done.get();
}

} // namespace

RedisChannel::RedisChannel(ChannelMode mode, Type payload_type, uint64_t id) noexcept
    : ChannelBase(mode, std::move(payload_type)), id_(id) {}

void RedisChannel::Push(const Object& message) {
    // Check if we're in execution context (for execution context system)
    if (current_execution_context != nullptr) {
        // Validate message type
        if (!Accepts(message)) {
            throw std::invalid_argument("Message type does not match channel payload type");
        }
        // Record push in context
        current_execution_context->RecordPush(id_, message);
    } else {
        // Direct push to Redis (for distributed system)
        RedisRepository::GetRepository().PushMessage(id_, message);
    }
}

uint64_t RedisChannel::GetID() const noexcept {
    return id_;
}

uint64_t RedisChannel::GetTempID() const noexcept {
    return id_;
}

RedisRepository& RedisRepository::GetRepository() {
    static RedisRepository instance;
    return instance;
}

void RedisRepository::RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) {
    // Check if we're in execution context
    if (current_execution_context != nullptr) {
        // Record join case in execution context
        current_execution_context->RecordJoinCase(inputs, context, runnable_id);
        return;
    }

    // Otherwise, register directly in distributed system
    std::sort(
        inputs.begin(), inputs.end(),
        [](const ChannelPtr& left, const ChannelPtr& right) {
            return left->GetID() < right->GetID();
        });

    IDs input_ids;
    input_ids.reserve(inputs.size());
    for (const auto& input : inputs) {
        debug::runtime_assert(input.use_count() > 0, "case inputs cannot be null when registering case");
        input_ids.push_back(input->GetID());
    }

    auto reaction = DistributedReaction{
        .input_ids = input_ids,
        .context = std::move(context),
        .runnable_id = runnable_id,
    };

    if (IsReactionAssignedToThisProcess(runnable_id)) {
        RegisterReactionLocally(reaction);
    }

    RunRedisOperation([this, input_ids, reaction](redis::RedisClient& client) -> boost::asio::awaitable<void> {
        std::vector<std::string> input_channel_ids;
        input_channel_ids.reserve(input_ids.size());
        for (const auto input_id : input_ids) {
            input_channel_ids.push_back(ChannelKey(input_id));
        }
        co_await client.RegisterReaction(
            std::to_string(reaction.runnable_id),
            ExecQueueKey(reaction.runnable_id),
            input_channel_ids,
            reaction.context);
        co_return;
    });
}

Pointer<ChannelBase> RedisRepository::NewChannel(ChannelMode mode, Type payload_type) {
    // Check if we're in execution context
    if (current_execution_context != nullptr) {
        // Record channel creation in execution context and return the proxy
        return current_execution_context->RecordNewChannel(mode, payload_type);
    }

    // Otherwise, create channel directly in distributed system
    const auto channel_id = next_id_.fetch_add(1, std::memory_order_relaxed);
    RunRedisOperation([this, channel_id](redis::RedisClient& client) -> boost::asio::awaitable<void> {
        co_await client.NewChannel(ChannelKey(channel_id));
        co_return;
    });
    return std::make_shared<RedisChannel>(mode, std::move(payload_type), channel_id);
}

void RedisRepository::Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) {
    runnable_map_ = std::move(runnable_map);
    auto main_runnable_it = runnable_map_.find(main_runnable_id);

    debug::runtime_assert(main_runnable_it != runnable_map_.end(), "main runnable not found");
    debug::runtime_assert(main_runnable_it->second != nullptr, "main runnable pointer is nullptr");
    ioc.restart();
    ioc.run_for(std::chrono::milliseconds(50));
    ioc.stop();
    is_complete_.store(false);
    while (calls_semaphore_.try_acquire()) {}
    {
        auto guard = std::lock_guard(lock_);
        calls_.clear();
        dependent_reactions_.clear();
        reaction_attributes_.clear();
        dead_nodes_.clear();
    }
    ioc.restart();

    bool start_initial_reaction = false;
    {
        boost::asio::io_context barrier_ioc;
        auto config = GetConfig();
        auto conn = std::make_shared<boost::redis::connection>(barrier_ioc.get_executor());
        auto client = std::make_shared<redis::RedisClient>(conn);
        auto barrier_result = std::promise<bool>{};
        auto barrier_done = barrier_result.get_future();

        conn->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);
        boost::asio::co_spawn(
            barrier_ioc.get_executor(),
            [conn, client, config, &barrier_result]() -> boost::asio::awaitable<void> {
                try {
                    barrier_result.set_value(co_await client->Barrier(config->ProgramsCount));
                } catch (...) {
                    barrier_result.set_exception(std::current_exception());
                }
                conn->cancel();
                co_return;
            },
            boost::asio::detached);

        barrier_ioc.run();
        start_initial_reaction = barrier_done.get();
    }

    auto config = GetConfig();
    conn_ = std::make_shared<boost::redis::connection>(ioc.get_executor());
    conn_->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);
    command_conn_ = std::make_shared<boost::redis::connection>(ioc.get_executor());
    redis_client_ = std::make_shared<redis::RedisClient>(command_conn_);
    command_conn_->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);
    reaction_conn_ = std::make_shared<boost::redis::connection>(ioc.get_executor());
    reaction_conn_->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);
    reaction_command_conn_ = std::make_shared<boost::redis::connection>(ioc.get_executor());
    reaction_redis_client_ = std::make_shared<redis::RedisClient>(reaction_command_conn_);
    reaction_command_conn_->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);
    heartbeat_conn_ = std::make_shared<boost::redis::connection>(ioc.get_executor());
    heartbeat_redis_client_ = std::make_shared<redis::RedisClient>(heartbeat_conn_);
    heartbeat_conn_->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);
    fault_monitor_conn_ = std::make_shared<boost::redis::connection>(ioc.get_executor());
    fault_monitor_redis_client_ = std::make_shared<redis::RedisClient>(fault_monitor_conn_);
    fault_monitor_conn_->async_run(MakeBoostRedisConfig(*config), boost::asio::detached);

    auto channel_subscribed = std::make_shared<std::promise<void>>();
    auto channel_subscribed_done = channel_subscribed->get_future();
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::ReceiveChannelNotifications(channel_subscribed), boost::asio::detached);
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::ReceiveReactionNotifications(), boost::asio::detached);
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::RefreshHeartbeat(), boost::asio::detached);
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::MonitorHeartbeats(), boost::asio::detached);
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::ReceiveJoinCase(), boost::asio::detached);
    boost::asio::co_spawn(ioc.get_executor(), RedisRepository::RunSchedulledCall(), boost::asio::detached);

    std::vector<std::thread> ths;
    ths.reserve(max_runner_threads);
    for (int i = 0; i != max_runner_threads; ++i) {
        ths.emplace_back([this] { /* Create threadlocal redis client */ ioc.run(); });
    }

    channel_subscribed_done.get();

    if (start_initial_reaction) {
        auto guard = std::lock_guard(lock_);
        calls_.push_back({Objects{}, Objects{}, main_runnable_it->second});
        calls_semaphore_.release();
    }

    for (auto& th : ths) th.join();

    ioc.restart();
    ioc.run_for(std::chrono::milliseconds(50));
    ioc.stop();
}

void RedisRepository::Stop() noexcept {
    is_complete_.store(true);
    if (conn_) {
        conn_->cancel();
    }
    if (command_conn_) {
        command_conn_->cancel();
    }
    if (reaction_conn_) {
        reaction_conn_->cancel();
    }
    if (reaction_command_conn_) {
        reaction_command_conn_->cancel();
    }
    if (heartbeat_conn_) {
        heartbeat_conn_->cancel();
    }
    if (fault_monitor_conn_) {
        fault_monitor_conn_->cancel();
    }
    calls_semaphore_.release();
    ioc.stop();
}

RedisRepository::RedisRepository()
    : next_id_(0)
    , is_complete_(false)
    , calls_semaphore_(0)
    , current_exec_queue_id_("default_exec_queue")
{}

boost::asio::awaitable<void> RedisRepository::ReceiveChannelNotifications(Pointer<std::promise<void>> subscribed) {
    boost::redis::request subscribe_req;
    subscribe_req.push("SUBSCRIBE", redis::kChannelMessageNotification);
    boost::redis::response<std::vector<std::string>> subscribe_resp;
    co_await conn_->async_exec(subscribe_req, subscribe_resp);

    boost::redis::generic_response pushes;
    conn_->set_receive_response(pushes);
    subscribed->set_value();

    while (true) {
        while (auto channel_key = ConsumeChannelNotification(pushes)) {
            auto channel_id = ParseChannelID(*channel_key);
            if (!channel_id.has_value()) {
                continue;
            }

            for (const auto& reaction : GetReactionsDependentOnChannel(*channel_id)) {
                co_await TryScheduleReaction(reaction);
            }
        }

        boost::system::error_code ec;
        co_await conn_->async_receive(boost::asio::redirect_error(boost::asio::use_awaitable, ec));
        if (ec) {
            if (is_complete_.load()) {
                co_return;
            }
            throw boost::system::system_error(ec);
        }
    }
}

boost::asio::awaitable<void> RedisRepository::ReceiveReactionNotifications() {
    boost::redis::request subscribe_req;
    subscribe_req.push("SUBSCRIBE", redis::kReactionCreatedNotification);
    boost::redis::response<std::vector<std::string>> subscribe_resp;
    co_await reaction_conn_->async_exec(subscribe_req, subscribe_resp);

    boost::redis::generic_response pushes;
    reaction_conn_->set_receive_response(pushes);

    while (true) {
        while (auto reaction_key = ConsumeReactionNotification(pushes)) {
            auto reaction_id = ParseChannelID(*reaction_key);
            if (!reaction_id.has_value()) {
                continue;
            }
            if (!IsReactionAssignedToThisProcess(*reaction_id)) {
                continue;
            }

            auto metadata = co_await reaction_redis_client_->GetReactionMetadata(*reaction_key);
            if (!metadata.input_channel_ids.empty()) {
                RegisterReactionLocally(ReactionFromMetadata(metadata));
            }

            auto attrs = co_await reaction_redis_client_->GetAttributes(
                {ExecQueueKey(*reaction_id)},
                {"head", "tail"});
            auto reaction_attrs = attrs[ExecQueueKey(*reaction_id)];
            if (reaction_attrs.size() < 2) {
                continue;
            }

            auto guard = std::lock_guard(lock_);
            reaction_attributes_.push_back(ReactionAttributes{
                .reaction_id = *reaction_id,
                .head = reaction_attrs[0],
                .tail = reaction_attrs[1],
            });
        }

        boost::system::error_code ec;
        co_await reaction_conn_->async_receive(boost::asio::redirect_error(boost::asio::use_awaitable, ec));
        if (ec) {
            if (is_complete_.load()) {
                co_return;
            }
            throw boost::system::system_error(ec);
        }
    }
}

boost::asio::awaitable<void> RedisRepository::RefreshHeartbeat() {
    auto config = GetConfig();
    auto executor = co_await boost::asio::this_coro::executor;
    boost::asio::steady_timer timer(executor);

    while (!is_complete_.load()) {
        co_await heartbeat_redis_client_->RefreshProcessHeartbeat(config->NodeID, kHeartbeatTTL);

        timer.expires_after(kHeartbeatRefreshInterval);
        boost::system::error_code ec;
        co_await timer.async_wait(boost::asio::redirect_error(boost::asio::use_awaitable, ec));
        if (ec) {
            co_return;
        }
    }

    co_return;
}

boost::asio::awaitable<void> RedisRepository::MonitorHeartbeats() {
    auto config = GetConfig();
    auto executor = co_await boost::asio::this_coro::executor;
    boost::asio::steady_timer timer(executor);

    timer.expires_after(kHeartbeatTTL);
    boost::system::error_code initial_ec;
    co_await timer.async_wait(boost::asio::redirect_error(boost::asio::use_awaitable, initial_ec));
    if (initial_ec) {
        co_return;
    }

    while (!is_complete_.load()) {
        for (uint64_t node_id = 0; node_id != config->ProgramsCount; ++node_id) {
            if (node_id == config->NodeID) {
                continue;
            }

            {
                auto guard = std::lock_guard(lock_);
                if (dead_nodes_.contains(node_id)) {
                    continue;
                }
            }

            const auto is_alive = co_await fault_monitor_redis_client_->IsProcessHeartbeatAlive(node_id);
            if (!is_alive) {
                {
                    auto guard = std::lock_guard(lock_);
                    dead_nodes_.insert(node_id);
                }
                co_await RecoverReactionsForDeadNode(node_id);
            }
        }

        timer.expires_after(kHeartbeatMonitorInterval);
        boost::system::error_code ec;
        co_await timer.async_wait(boost::asio::redirect_error(boost::asio::use_awaitable, ec));
        if (ec) {
            co_return;
        }
    }

    co_return;
}

boost::asio::awaitable<void> RedisRepository::ReceiveJoinCase() {
    // Receive join cases for this node from redis pub/sub
    // Register join case
    // Schedule next iteration of ReceiveJoinCase
    // Should not call RegisterJoinCase, as it is an interface function for generated code
    co_return;
}

boost::asio::awaitable<void> RedisRepository::RunSchedulledCall() {
    while (true) {
        calls_semaphore_.acquire();
        if (is_complete_.load()) {
            co_return;
        }

        SchedulledCall call;
        {
            auto guard = std::lock_guard(lock_);
            debug::runtime_assert(!calls_.empty(), "scheduled routine queue is empty");
            call = std::move(calls_.front());
            calls_.pop_front();
        }

        debug::runtime_assert(call.runnable != nullptr, "scheduled runnable pointer is nullptr");
        
        // Execute runnable and get result (using execution context system)
        ExecutionResult result;
        try {
            result = RunByID(call.runnable->GetID(), std::move(call.inputs), std::move(call.context));
        } catch (const std::exception& e) {
            debug::print("Execution failed for runnable " + 
                        std::to_string(call.runnable->GetID()) + ": " + 
                        std::string(e.what()));
            // Continue to next call (don't crash the worker)
            if (is_complete_.load()) {
                co_return;
            }
            continue;
        }
        
        // Commit result to Redis
        try {
            co_await CommitExecutionResult(result);
        } catch (const std::exception& e) {
            debug::print("Commit failed: " + std::string(e.what()));
            // TODO: Implement retry logic or move to dead-letter queue
        }
        
        if (is_complete_.load()) {
            co_return;
        }
    }
}

ExecutionResult RedisRepository::RunByID(uint64_t runnable_id, Objects inputs, Objects context) {
    // Find runnable
    auto it = runnable_map_.find(runnable_id);
    if (it == runnable_map_.end() || it->second == nullptr) {
        throw std::runtime_error("Runnable not found: " + std::to_string(runnable_id));
    }
    
    // Create execution context
    ExecutionContext exec_context;
    ExecutionContextGuard guard(&exec_context);
    
    // Execute runnable (will record actions in exec_context)
    try {
        it->second->operator()(inputs, context);
    } catch (const std::exception& e) {
        debug::print("Runnable execution failed: " + std::string(e.what()));
        throw;
    }
    
    // Extract and return result
    return exec_context.ExtractResult();
}

boost::asio::awaitable<void> RedisRepository::TryScheduleReaction(const DistributedReaction& reaction) {
    redis::Keys channel_keys;
    channel_keys.reserve(reaction.input_ids.size());
    for (const auto channel_id : reaction.input_ids) {
        channel_keys.push_back(ChannelKey(channel_id));
    }

    auto channel_attrs = co_await redis_client_->GetAttributes(channel_keys, {"head"});

    redis::Keys head_keys;
    head_keys.reserve(channel_keys.size());
    for (const auto& channel_key : channel_keys) {
        auto attrs_it = channel_attrs.find(channel_key);
        if (attrs_it == channel_attrs.end() || attrs_it->second.empty() || attrs_it->second[0].empty()) {
            co_return;
        }
        head_keys.push_back(attrs_it->second[0]);
    }

    auto head_attrs = co_await redis_client_->GetAttributes(head_keys, {"msg"});
    for (const auto& head_key : head_keys) {
        auto attrs_it = head_attrs.find(head_key);
        if (attrs_it == head_attrs.end() || attrs_it->second.empty() || attrs_it->second[0].empty()) {
            co_return;
        }
    }

    auto inputs = co_await redis_client_->ScheduleExecution(ExecQueueKey(reaction.runnable_id), channel_keys);
    if (!inputs.empty()) {
        ScheduleCall(std::move(inputs), reaction.context, reaction.runnable_id);
    }

    co_return;
}

DistributedReactions RedisRepository::GetReactionsDependentOnChannel(uint64_t channel_id) {
    auto guard = std::lock_guard(lock_);
    auto reactions_it = dependent_reactions_.find(channel_id);
    if (reactions_it == dependent_reactions_.end()) {
        return {};
    }
    return reactions_it->second;
}

bool RedisRepository::IsReactionAssignedToThisProcess(uint64_t reaction_id) {
    auto config = GetConfig();
    debug::runtime_assert(
        config->NodeID < config->ProgramsCount,
        "NODE_ID must be less than PROGRAMS_COUNT");

    std::unordered_set<uint64_t> dead_nodes;
    {
        auto guard = std::lock_guard(lock_);
        dead_nodes = dead_nodes_;
    }
    return PickNodeByConsistentHash(reaction_id, config->ProgramsCount, dead_nodes) == config->NodeID;
}

bool RedisRepository::WasReactionAssignedToNode(uint64_t reaction_id, uint64_t node_id) const {
    auto config = GetConfig();
    return PickNodeByConsistentHash(reaction_id, config->ProgramsCount) == node_id;
}

bool RedisRepository::IsReactionAssignedToThisProcessAfterFault(uint64_t reaction_id, uint64_t dead_node_id) {
    auto config = GetConfig();
    std::unordered_set<uint64_t> dead_nodes;
    {
        auto guard = std::lock_guard(lock_);
        dead_nodes = dead_nodes_;
    }
    dead_nodes.insert(dead_node_id);
    return PickNodeByConsistentHash(reaction_id, config->ProgramsCount, dead_nodes) == config->NodeID;
}

void RedisRepository::RegisterReactionLocally(DistributedReaction reaction) {
    auto guard = std::lock_guard(lock_);
    for (const auto channel_id : reaction.input_ids) {
        auto& reactions = dependent_reactions_[channel_id];
        const auto already_registered = std::any_of(
            reactions.begin(),
            reactions.end(),
            [runnable_id = reaction.runnable_id](const DistributedReaction& existing) {
                return existing.runnable_id == runnable_id;
            });
        if (!already_registered) {
            reactions.push_back(reaction);
        }
    }
}

boost::asio::awaitable<void> RedisRepository::RecoverReactionsForDeadNode(uint64_t dead_node_id) {
    auto reaction_ids = co_await fault_monitor_redis_client_->ListReactions();

    for (const auto& reaction_key : reaction_ids) {
        auto reaction_id = ParseChannelID(reaction_key);
        if (!reaction_id.has_value()) {
            continue;
        }
        if (!WasReactionAssignedToNode(*reaction_id, dead_node_id)) {
            continue;
        }
        if (!IsReactionAssignedToThisProcessAfterFault(*reaction_id, dead_node_id)) {
            continue;
        }

        auto metadata = co_await fault_monitor_redis_client_->GetReactionMetadata(reaction_key);
        auto reaction = ReactionFromMetadata(metadata);
        RegisterReactionLocally(reaction);
        co_await TryScheduleReaction(reaction);
    }

    co_return;
}

void RedisRepository::PushMessage(uint64_t channel_id, const Object& message) {
    RunRedisOperation([this, channel_id, message](redis::RedisClient& client) -> boost::asio::awaitable<void> {
        co_await client.PushToChannel(ChannelKey(channel_id), message);
        co_return;
    });

    if (is_complete_.load()) {
        return;
    }

    for (const auto& reaction : GetReactionsDependentOnChannel(channel_id)) {
        Objects inputs;
        RunRedisOperation([this, &reaction, &inputs](redis::RedisClient& client) -> boost::asio::awaitable<void> {
            redis::Keys channel_keys;
            channel_keys.reserve(reaction.input_ids.size());
            for (const auto input_id : reaction.input_ids) {
                channel_keys.push_back(ChannelKey(input_id));
            }
            inputs = co_await client.ScheduleExecution(ExecQueueKey(reaction.runnable_id), channel_keys);
            co_return;
        });
        if (!inputs.empty()) {
            ScheduleCall(std::move(inputs), reaction.context, reaction.runnable_id);
        }
    }
}

void RedisRepository::ScheduleCall(Objects inputs, Objects context, uint64_t runnable_id) noexcept {
    auto runnable_it = runnable_map_.find(runnable_id);
    debug::runtime_assert(runnable_it != runnable_map_.end(), "scheduled runnable not found");
    debug::runtime_assert(runnable_it->second != nullptr, "scheduled runnable pointer is nullptr");

    auto guard = std::lock_guard(lock_);
    calls_.push_back(SchedulledCall{std::move(inputs), std::move(context), runnable_it->second});
    calls_semaphore_.release();
}

std::string RedisRepository::ChannelKey(uint64_t channel_id) const {
    return std::to_string(channel_id);
}

std::string RedisRepository::ExecQueueKey(uint64_t runnable_id) const {
    return "exec:" + std::to_string(runnable_id);
}

// Execution context commit logic
boost::asio::awaitable<void> RedisRepository::CommitExecutionResult(const ExecutionResult& result) {
    // 1. Create channels in Redis and build ID mapping
    std::unordered_map<uint64_t, std::string> temp_id_to_redis_id;
    
    for (const auto& channel_creation : result.GetChannels()) {
        std::string redis_channel_id = GenerateRedisChannelID();
        
        try {
            RunRedisOperation([redis_channel_id](redis::RedisClient& client) -> boost::asio::awaitable<void> {
                co_await client.NewChannel(redis_channel_id);
                co_return;
            });
            temp_id_to_redis_id[channel_creation.temp_id] = redis_channel_id;
        } catch (const std::exception& e) {
            debug::print("Failed to create channel in Redis: " + std::string(e.what()));
            throw;
        }
    }
    
    // 2. Register join-cases created by this execution.
    for (const auto& join_case : result.GetJoinCases()) {
        IDs input_ids;
        std::vector<std::string> input_channel_ids;
        input_ids.reserve(join_case.input_channel_temp_ids.size());
        input_channel_ids.reserve(join_case.input_channel_temp_ids.size());

        for (const auto temp_id : join_case.input_channel_temp_ids) {
            const auto redis_id_it = temp_id_to_redis_id.find(temp_id);
            if (redis_id_it == temp_id_to_redis_id.end()) {
                throw std::logic_error("join-case references unknown temporary channel");
            }
            input_channel_ids.push_back(redis_id_it->second);
            auto parsed_id = ParseChannelID(redis_id_it->second);
            if (!parsed_id.has_value()) {
                throw std::logic_error("generated Redis channel id is not numeric");
            }
            input_ids.push_back(*parsed_id);
        }

        auto reaction = DistributedReaction{
            .input_ids = input_ids,
            .context = join_case.context,
            .runnable_id = join_case.runnable_id,
        };
        if (IsReactionAssignedToThisProcess(join_case.runnable_id)) {
            RegisterReactionLocally(reaction);
        }
        RunRedisOperation([this, input_channel_ids, join_case](redis::RedisClient& client) -> boost::asio::awaitable<void> {
            co_await client.RegisterReaction(
                std::to_string(join_case.runnable_id),
                ExecQueueKey(join_case.runnable_id),
                input_channel_ids,
                join_case.context);
            co_return;
        });
    }

    // 3. Push recorded messages. The Redis schedule script remains the single-consumer guard.
    for (const auto& push : result.GetPushes()) {
        const auto redis_id_it = temp_id_to_redis_id.find(push.channel_temp_id);
        if (redis_id_it == temp_id_to_redis_id.end()) {
            throw std::logic_error("message push references unknown temporary channel");
        }
        RunRedisOperation([channel_id = redis_id_it->second, message = push.message](redis::RedisClient& client) -> boost::asio::awaitable<void> {
            co_await client.PushToChannel(channel_id, message);
            co_return;
        });

        auto parsed_channel_id = ParseChannelID(redis_id_it->second);
        if (parsed_channel_id.has_value()) {
            for (const auto& reaction : GetReactionsDependentOnChannel(*parsed_channel_id)) {
                Objects inputs;
                RunRedisOperation([this, &reaction, &inputs](redis::RedisClient& client) -> boost::asio::awaitable<void> {
                    redis::Keys channel_keys;
                    channel_keys.reserve(reaction.input_ids.size());
                    for (const auto input_id : reaction.input_ids) {
                        channel_keys.push_back(ChannelKey(input_id));
                    }
                    inputs = co_await client.ScheduleExecution(ExecQueueKey(reaction.runnable_id), channel_keys);
                    co_return;
                });
                if (!inputs.empty()) {
                    ScheduleCall(std::move(inputs), reaction.context, reaction.runnable_id);
                }
            }
        }
    }
    
    // Log success
    debug::print("Successfully committed execution result: " + 
                std::to_string(result.GetChannelCount()) + " channels, " +
                std::to_string(result.GetPushCount()) + " messages");
    co_return;
}

std::string RedisRepository::GenerateRedisChannelID() {
    return std::to_string(next_id_.fetch_add(1, std::memory_order_relaxed));
}

std::string RedisRepository::GetCurrentExecQueueID() const {
    // Return current execution queue ID
    return current_exec_queue_id_;
}

}  // namespace reactor
