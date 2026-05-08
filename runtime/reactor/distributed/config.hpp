#pragma once

#include <boost/redis/config.hpp>

#include <string>

#include <runtime/reactor/common/helpers.hpp>

namespace reactor {

struct Config {
    uint64_t NodeID;

    std::string RedisAddr;
    std::string RedisUser;
    std::string RedisPassword;
    uint64_t RedisDB;
};

const Pointer<Config> GetConfig();

}  // namespace reactor
