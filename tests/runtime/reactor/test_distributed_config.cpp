#include <gtest/gtest.h>

#include <stdexcept>
#include <stdlib.h>

#include <runtime/reactor/distributed/config.hpp>

struct EnvGuard {
    EnvGuard(const std::string& key, const std::string& value) noexcept: key_(key) {
        setenv(key_.c_str(), value.c_str(), 0);
    }

    ~EnvGuard() noexcept {
        unsetenv(key_.c_str());
    }

private:
    const std::string& key_;
};

TEST(DistributedConfiguration, TestSuccess) {
    auto redit_host_guard = EnvGuard("REDIS_HOST", "testhost");
    auto redit_port_guard = EnvGuard("REDIS_PORT", "12345");
    auto redit_user_guard = EnvGuard("REDIS_USER", "testuser");
    auto redit_password_guard = EnvGuard("REDIS_PASSWORD", "testpass");

    auto required_config = reactor::GetConfig();

    EXPECT_EQ(required_config->NodeID, 0ull);
    EXPECT_EQ(required_config->RedisAddr, "testhost:12345");
    EXPECT_EQ(required_config->RedisUser, "testuser");
    EXPECT_EQ(required_config->RedisPassword, "testpass");
    EXPECT_EQ(required_config->RedisDB, 0ull);

    auto node_id_guard = EnvGuard("NODE_ID", "123");
    auto redit_db_guard = EnvGuard("REDIS_DB", "456");

    auto full_config = reactor::GetConfig();

    EXPECT_EQ(full_config->NodeID, 123ull);
    EXPECT_EQ(full_config->RedisAddr, "testhost:12345");
    EXPECT_EQ(full_config->RedisUser, "testuser");
    EXPECT_EQ(full_config->RedisPassword, "testpass");
    EXPECT_EQ(full_config->RedisDB, 456ull);
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
}
