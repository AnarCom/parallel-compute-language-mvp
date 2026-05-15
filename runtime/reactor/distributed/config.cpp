#include "config.hpp"

#include <cstdlib>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace reactor {

auto OptionalParam(auto getter, const std::string& key) noexcept -> Maybe<decltype(getter(key))> {
    try {
        return {getter(key)};
    } catch(std::runtime_error&) {
        return {};
    }
}

std::string GetString(const std::string& key) {
    const char* value = std::getenv(key.c_str());
    if (value == nullptr) {
        throw std::runtime_error(std::format("Param {} is required via ENV", key));
    }
    return std::string(value);
}

int64_t GetInt(const std::string& key) {
    try {
        return std::stoll(GetString(key));
    } catch (std::exception&) {
        throw std::runtime_error(std::format("Param {} is not a valid integer", key));
    }
}

uint64_t GetPositiveInt(const std::string& key) {
    auto value = GetInt(key);
    if (value < 0) {
        throw std::runtime_error(std::format("Param {} is not a positive integer", key));
    }
    return static_cast<uint64_t>(value);
}

uint64_t GetStrictPositiveInt(const std::string& key) {
    auto value = GetPositiveInt(key);
    if (value == 0) {
        throw std::runtime_error(std::format("Param {} must be greater than zero", key));
    }
    return value;
}

const Pointer<Config> GetConfig() {
    auto config = std::make_shared<Config>();

    config->NodeID = OptionalParam(GetPositiveInt, "NODE_ID").value_or(0);
    if (std::getenv("PROGRAMS_COUNT") != nullptr) {
        config->ProgramsCount = GetStrictPositiveInt("PROGRAMS_COUNT");
    } else if (std::getenv("PROGRAMMS_COUNT") != nullptr) {
        config->ProgramsCount = GetStrictPositiveInt("PROGRAMMS_COUNT");
    } else {
        config->ProgramsCount = 1;
    }
    if (config->NodeID >= config->ProgramsCount) {
        throw std::runtime_error("Param NODE_ID must be less than PROGRAMS_COUNT");
    }

    config->RedisAddr = std::format("{}:{}", GetString("REDIS_HOST"), GetPositiveInt("REDIS_PORT"));
    config->RedisUser = GetString("REDIS_USER");
    config->RedisPassword = GetString("REDIS_PASSWORD");
    config->RedisDB = OptionalParam(GetPositiveInt, "REDIS_DB").value_or(0);

    return config;
}

}  // namespace reactor
