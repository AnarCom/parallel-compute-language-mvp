#include "gtest/gtest.h"

#include "logging.hpp"
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
    auto channel = std::make_shared<reactor::CycleChannel>();
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
    auto shared = std::make_shared<reactor::CycleChannel>();

    auto channel_1 = std::make_shared<reactor::CycleChannel>();
    auto channel_2 = std::make_shared<reactor::CycleChannel>();
    auto channel_3 = std::make_shared<reactor::CycleChannel>();

    auto runnable_1 = std::make_shared<TestRunnable>();
    auto runnable_2 = std::make_shared<TestRunnable>();
    auto runnable_3 = std::make_shared<TestRunnable>();

    reactor::CycleRepository::GetRepository().RegisterJoinCase({shared, channel_1}, {}, runnable_1);
    reactor::CycleRepository::GetRepository().RegisterJoinCase({shared, channel_2}, {}, runnable_2);
    reactor::CycleRepository::GetRepository().RegisterJoinCase({shared, channel_3}, {}, runnable_3);
    reactor::CycleRepository::GetRepository().CheckCases();

    for (size_t i = 0; i < 9; ++i) {
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
}

class IncrementCounter: public reactor::Runnable {
public:
    void Run(reactor::Objects inputs, reactor::Channels outputs) override {
        // inputs Inc, Val | Outputs Val
        // inputs[0] is ignored
        auto value = inputs[1];
        value.integer += 1;
        outputs[0]->Push(value);
    }
};

class GetCounter: public reactor::Runnable {
public:
    void Run(reactor::Objects inputs, reactor::Channels outputs) override {
        // inputs ReplyCh, Val | Outputs Val
        auto reply_channel = inputs[0].channel;
        auto value = inputs[1];
        outputs[0]->Push(value);
        reply_channel->Push(value);
    }
};

// Main
class Consumer: public std::enable_shared_from_this<Consumer>, public reactor::Runnable {
public:
    Consumer(): count(0) {}

    void Run(reactor::Objects inputs, reactor::Channels outputs) override {
        // inputs GetResult | Output Get
        count += inputs[0].integer;
        reactor::Object reply_channel;
        reply_channel.channel = std::make_shared<reactor::CycleChannel>();
        reactor::CycleRepository::GetRepository().RegisterJoinCase({reply_channel.channel}, outputs, shared_from_this());
        outputs[0]->Push(reply_channel);
    }

    size_t count;
};

TEST(CycleReactor, TestExample) {
    auto main = std::make_shared<Consumer>();
    {
        auto val = std::make_shared<reactor::CycleChannel>();
        auto inc = std::make_shared<reactor::CycleChannel>();
        auto get = std::make_shared<reactor::CycleChannel>();

        auto incrementer = std::make_shared<IncrementCounter>();
        auto getter = std::make_shared<GetCounter>();

        reactor::CycleRepository::GetRepository().RegisterJoinCase({inc, val}, {val}, incrementer);
        reactor::CycleRepository::GetRepository().RegisterJoinCase({get, val}, {val}, getter);

        auto entry = std::make_shared<reactor::CycleChannel>();
        reactor::CycleRepository::GetRepository().RegisterJoinCase({entry}, {get}, main);

        reactor::Object initial;
        initial.integer = 0;
        val->Push(initial);
        entry->Push(initial);

        for (int i = 0; i < 10; ++i) {
            inc->Push(reactor::Object());
        }
    }

    for (int i = 0; i < 1000; ++i) {
        reactor::CycleRepository::GetRepository().CheckCases();
    }

    ASSERT_EQ(main->count, 10);
}

// You do not need to write a main() function if you link to GTest::Main
