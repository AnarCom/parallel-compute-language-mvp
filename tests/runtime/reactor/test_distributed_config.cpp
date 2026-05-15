#include <gtest/gtest.h>

#include <optional>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <utility>

#include <runtime/reactor/distributed/config.hpp>

struct EnvGuard {
    EnvGuard(std::string key, const std::string& value) noexcept: key_(std::move(key)) {
        if (const auto* previous = getenv(key_.c_str())) {
            previous_value_ = previous;
        }
        setenv(key_.c_str(), value.c_str(), 1);
    }

    ~EnvGuard() noexcept {
        if (previous_value_.has_value()) {
            setenv(key_.c_str(), previous_value_->c_str(), 1);
        } else {
            unsetenv(key_.c_str());
        }
    }

private:
    std::string key_;
    std::optional<std::string> previous_value_;
};

TEST(DistributedConfiguration, TestSuccess) {
    auto redit_host_guard = EnvGuard("REDIS_HOST", "testhost");
    auto redit_port_guard = EnvGuard("REDIS_PORT", "12345");
    auto redit_user_guard = EnvGuard("REDIS_USER", "testuser");
    auto redit_password_guard = EnvGuard("REDIS_PASSWORD", "testpass");
    auto default_node_id_guard = EnvGuard("NODE_ID", "0");

    auto required_config = reactor::GetConfig();

    EXPECT_EQ(required_config->NodeID, 0ull);
    EXPECT_EQ(required_config->ProgramsCount, 1ull);
    EXPECT_EQ(required_config->RedisAddr, "testhost:12345");
    EXPECT_EQ(required_config->RedisUser, "testuser");
    EXPECT_EQ(required_config->RedisPassword, "testpass");
    EXPECT_EQ(required_config->RedisDB, 0ull);

    auto node_id_guard = EnvGuard("NODE_ID", "3");
    auto programs_count_guard = EnvGuard("PROGRAMS_COUNT", "7");
    auto redit_db_guard = EnvGuard("REDIS_DB", "456");

    auto full_config = reactor::GetConfig();

    EXPECT_EQ(full_config->NodeID, 3ull);
    EXPECT_EQ(full_config->ProgramsCount, 7ull);
    EXPECT_EQ(full_config->RedisAddr, "testhost:12345");
    EXPECT_EQ(full_config->RedisUser, "testuser");
    EXPECT_EQ(full_config->RedisPassword, "testpass");
    EXPECT_EQ(full_config->RedisDB, 456ull);

    unsetenv("PROGRAMS_COUNT");
    auto legacy_programms_count_guard = EnvGuard("PROGRAMMS_COUNT", "8");
    auto legacy_config = reactor::GetConfig();

    EXPECT_EQ(legacy_config->ProgramsCount, 8ull);
}

TEST(DistributedConfiguration, TestFailure) {
    {
        auto redit_host_guard = EnvGuard("REDIS_HOST", "testhost");
        auto redit_port_guard = EnvGuard("REDIS_PORT", "12345");
        auto redit_user_guard = EnvGuard("REDIS_USER", "testuser");

        EXPECT_THROW(reactor::GetConfig(), std::runtime_error);
    }

    {
        auto redit_host_guard = EnvGuard("REDIS_HOST", "testhost");
        auto redit_port_guard = EnvGuard("REDIS_PORT", "-12345");
        auto redit_user_guard = EnvGuard("REDIS_USER", "testuser");
        auto redit_password_guard = EnvGuard("REDIS_PASSWORD", "testpass");

        EXPECT_THROW(reactor::GetConfig(), std::runtime_error);
    }

    {
        auto redit_host_guard = EnvGuard("REDIS_HOST", "testhost");
        auto redit_port_guard = EnvGuard("REDIS_PORT", "NAN");
        auto redit_user_guard = EnvGuard("REDIS_USER", "testuser");
        auto redit_password_guard = EnvGuard("REDIS_PASSWORD", "testpass");

        EXPECT_THROW(reactor::GetConfig(), std::runtime_error);
    }

    {
        auto redit_host_guard = EnvGuard("REDIS_HOST", "testhost");
        auto redit_port_guard = EnvGuard("REDIS_PORT", "12345");
        auto redit_user_guard = EnvGuard("REDIS_USER", "testuser");
        auto redit_password_guard = EnvGuard("REDIS_PASSWORD", "testpass");
        auto programs_count_guard = EnvGuard("PROGRAMS_COUNT", "0");

        EXPECT_THROW(reactor::GetConfig(), std::runtime_error);
    }

    {
        auto redit_host_guard = EnvGuard("REDIS_HOST", "testhost");
        auto redit_port_guard = EnvGuard("REDIS_PORT", "12345");
        auto redit_user_guard = EnvGuard("REDIS_USER", "testuser");
        auto redit_password_guard = EnvGuard("REDIS_PASSWORD", "testpass");
        auto node_id_guard = EnvGuard("NODE_ID", "2");
        auto programs_count_guard = EnvGuard("PROGRAMS_COUNT", "2");

        EXPECT_THROW(reactor::GetConfig(), std::runtime_error);
    }
}
