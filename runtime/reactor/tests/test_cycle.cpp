#include "gtest/gtest.h"

#include <atomic>

#include "logging.hpp"
#include "cycle_impl.hpp"
#include "interface.hpp"

constexpr auto TestRepo = &reactor::CycleRepository::GetRepository;

class TestRunnable: public reactor::Runnable {
public:
    TestRunnable(): calls_count(0) {}

    void operator()(reactor::Objects inputs) override {
        ++(this->calls_count);
    }

    std::atomic<size_t> calls_count;
};

TEST(CycleReactor, TestSuccessAndNoStarvation) {
    auto runnable_1 = TestRunnable();
    auto runnable_2 = TestRunnable();
    auto runnable_3 = TestRunnable();

    TestRepo().Run(std::make_shared<reactor::RunnableOrLambda>([&](reactor::Objects){
        auto shared = TestRepo().NewChannel();

        TestRepo().RegisterJoinCase({shared}, {}, std::make_shared<reactor::RunnableOrLambda>(
            [&runnable_1](reactor::Objects inputs) { runnable_1(inputs); }
        ));
        TestRepo().RegisterJoinCase({shared}, {}, std::make_shared<reactor::RunnableOrLambda>(
            [&runnable_2](reactor::Objects inputs) { runnable_2(inputs); }
        ));
        TestRepo().RegisterJoinCase({shared}, {}, std::make_shared<reactor::RunnableOrLambda>(
            [&runnable_3](reactor::Objects inputs) { runnable_3(inputs); }
        ));

        for (size_t i = 0; i < 9; ++i) {
            shared->Push(reactor::Object());
        }
    }));

    EXPECT_EQ(runnable_1.calls_count.load(), 3);
    EXPECT_EQ(runnable_2.calls_count.load(), 3);
    EXPECT_EQ(runnable_3.calls_count.load(), 3);
}
