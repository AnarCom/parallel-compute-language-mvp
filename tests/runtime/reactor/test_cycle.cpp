#include <gtest/gtest.h>

#include <atomic>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/common/logging.hpp>
#include <runtime/reactor/parallel/repository.hpp>

constexpr auto TestRepo = &reactor::CycleRepository::GetRepository;

class TestRunnable: public reactor::Runnable {
public:
    TestRunnable(): calls_count(0) {}

    void operator()(reactor::Objects inputs, reactor::Objects) override {
        ++(this->calls_count);
    }

    std::atomic<size_t> calls_count;
};

class TestRunnable1: public TestRunnable {
    uint64_t GetID() const noexcept override {
        return 1;
    }
};

class TestRunnable2: public TestRunnable {
    uint64_t GetID() const noexcept override {
        return 2;
    }
};

class TestRunnable3: public TestRunnable {
    uint64_t GetID() const noexcept override {
        return 3;
    }
};

class TestMain: public reactor::Runnable {
public:
    TestMain() {}

    void operator()(reactor::Objects inputs, reactor::Objects) override {
        auto shared = TestRepo().NewChannel();

        TestRepo().RegisterJoinCase({shared}, {}, 1);
        TestRepo().RegisterJoinCase({shared}, {}, 2);
        TestRepo().RegisterJoinCase({shared}, {}, 3);

        for (size_t i = 0; i < 9; ++i) {
            shared->Push(reactor::Object());
        }
    }

    uint64_t GetID() const noexcept override {
        return 0;
    }
};

TEST(CycleReactor, TestSuccessAndNoStarvation) {
    std::unordered_map<uint64_t, reactor::Runnable*> runnable_map = {
        {0, new TestMain()},
        {1, new TestRunnable1()},
        {2, new TestRunnable2()},
        {3, new TestRunnable3()},
    };

    // In production code runnable_map is moved
    TestRepo().Run(0, runnable_map);

    EXPECT_EQ(dynamic_cast<TestRunnable1*>(runnable_map[1])->calls_count.load(), 3);
    EXPECT_EQ(dynamic_cast<TestRunnable2*>(runnable_map[2])->calls_count.load(), 3);
    EXPECT_EQ(dynamic_cast<TestRunnable3*>(runnable_map[3])->calls_count.load(), 3);
}
