#include <string_view>

namespace reactor::redis::scripts {

namespace {
    #include "commit_lua.hpp"
    #include "get_attributes_lua.hpp"
    #include "new_channel_lua.hpp"
    #include "new_exec_queue_lua.hpp"
    #include "push_lua.hpp"
    #include "schedule_lua.hpp"
}  // namespace

constexpr auto kCommitScript = std::string_view(__commit_lua, __commit_lua_len);

constexpr auto kGetAttributesScript = std::string_view(__get_attributes_lua, __get_attributes_lua_len);

constexpr auto kNewChannelScript = std::string_view(__new_channel_lua, __new_channel_lua_len);

constexpr auto kNewExecQueueScript = std::string_view(__new_exec_queue_lua, __new_exec_queue_lua_len);

constexpr auto kPushScript = std::string_view(__push_lua, __push_lua_len);

constexpr auto kScheduleScript = std::string_view(__schedule_lua, __schedule_lua_len);

}  // namespace reactor::redis::scripts
