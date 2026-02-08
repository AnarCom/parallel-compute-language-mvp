#include "gtest/gtest.h"

#include "cycle_impl.hpp"
#include "interface.hpp"

class TestRunnable: public reactor::Runnable {
public:
    TestRunnable(): calls_count(0) {}

    void Run(reactor::Objects inputs, reactor::Channels outputs) override {
        ++(this->calls_count);
    }

    size_t calls_count;
};

TEST(CycleReactor, TestSuccess) {
    auto channel = std::make_shared<reactor::ChannelBase>();
    auto runnable = std::make_shared<TestRunnable>();
    reactor::CycleRepository::GetRepository().RegisterJoinCase({channel}, {}, runnable);
    reactor::CycleRepository::GetRepository().CheckCases();

    channel->Push(reactor::Object());
    reactor::CycleRepository::GetRepository().CheckCases();
    EXPECT_EQ(runnable->calls_count, 1);

    channel->Push(reactor::Object());
    reactor::CycleRepository::GetRepository().CheckCases();
    EXPECT_EQ(runnable->calls_count, 2);
}

TEST(CycleReactor, TestNoStarvation) {
    auto shared = std::make_shared<reactor::ChannelBase>();

    auto channel_1 = std::make_shared<reactor::ChannelBase>();
    auto channel_2 = std::make_shared<reactor::ChannelBase>();
    auto channel_3 = std::make_shared<reactor::ChannelBase>();

    auto runnable_1 = std::make_shared<TestRunnable>();
    auto runnable_2 = std::make_shared<TestRunnable>();
    auto runnable_3 = std::make_shared<TestRunnable>();

    reactor::CycleRepository::GetRepository().RegisterJoinCase({shared, channel_1}, {}, runnable_1);
    reactor::CycleRepository::GetRepository().RegisterJoinCase({shared, channel_2}, {}, runnable_2);
    reactor::CycleRepository::GetRepository().RegisterJoinCase({shared, channel_3}, {}, runnable_3);
    reactor::CycleRepository::GetRepository().CheckCases();

    for (size_t i = 0; i < 10; ++i) {
        shared->Push(reactor::Object());
    }

    for (size_t i = 0; i < 3; ++i) {
        channel_1->Push(reactor::Object());
        reactor::CycleRepository::GetRepository().CheckCases();

        channel_2->Push(reactor::Object());
        reactor::CycleRepository::GetRepository().CheckCases();

        channel_3->Push(reactor::Object());
        reactor::CycleRepository::GetRepository().CheckCases();
    }

    EXPECT_EQ(runnable_1->calls_count, 3);
    EXPECT_EQ(runnable_2->calls_count, 3);
    EXPECT_EQ(runnable_3->calls_count, 3);

    EXPECT_EQ(shared->Length(), 1);
}

// You do not need to write a main() function if you link to GTest::Main
