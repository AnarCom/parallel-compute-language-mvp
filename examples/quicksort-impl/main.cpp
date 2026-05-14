#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <tuple>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/common/logging.hpp>
#include <runtime/reactor/parallel_improved/repository.hpp>

constexpr auto GetRepo = &reactor::ImprovedRepository::GetRepository;
static std::mutex lock;
static std::chrono::time_point<std::chrono::steady_clock> start;

std::tuple<reactor::Object, reactor::Object, reactor::Object> partition(const reactor::Object& values) noexcept {
    auto value_it = values.AsList().begin();
    auto values_end = values.AsList().end();
    auto pivot = *value_it;
    reactor::Objects left, right;
    std::advance(value_it, 1);
    while (value_it != values_end) {
        if (value_it->AsInt() <= pivot.AsInt()) {
            left.push_back(*value_it);
        } else {
            right.push_back(*value_it);
        }
        std::advance(value_it, 1);
    }
    return {reactor::Object::List(std::move(left), reactor::Type::Int()), pivot, reactor::Object::List(std::move(right), reactor::Type::Int())};
}

reactor::Object concat(const reactor::Object& left, const reactor::Object& pivot, const reactor::Object& right) noexcept {
    reactor::Objects merged;
    for (const auto& value : left.AsList()) {
        merged.push_back(value);
    }
    merged.push_back(pivot);
    for (const auto& value : right.AsList()) {
        merged.push_back(value);
    }
    return reactor::Object::List(std::move(merged), reactor::Type::Int());
}

class Split: public reactor::Runnable {
public:
    Split() {}

    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        auto values = inputs[0].AsTuple()[0];
        auto reply = inputs[0].AsTuple()[1];
        auto split = context[0];

        if (values.AsList().size() <= 1000) {
            auto values_copy = values.AsList();
            std::sort(
                values_copy.begin(), values_copy.end(),
                [](const reactor::Object& left, const reactor::Object& right){ return left.AsInt() < right.AsInt(); }
            );
            reply.AsChannel()->Push(reactor::Object::List(values_copy));
            return;
        }

        auto [left, pivot, right] = partition(values);
        auto leftReply = GetRepo().NewChannel();
        auto rightReply = GetRepo().NewChannel();

        GetRepo().RegisterJoinCase({leftReply, rightReply}, {reply, pivot}, 1);

        if (left.AsList().size() > 1) {
            split.AsChannel()->Push(reactor::Object::Tuple({left, reactor::Object::Channel(leftReply)}));
        } else {
            leftReply->Push(left);
        }

        if (right.AsList().size() > 1) {
            split.AsChannel()->Push(reactor::Object::Tuple({right, reactor::Object::Channel(rightReply)}));
        } else {
            rightReply->Push(right);
        }
    }

    uint64_t GetID() const noexcept override {
        return 0;
    }
};

class MergeSorted: public reactor::Runnable {
public:
    MergeSorted() {}

    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        auto leftSorted = inputs[0];
        auto rigthSorted = inputs[1];
        context[0].AsChannel()->Push(concat(leftSorted, context[1], rigthSorted));
    }

    uint64_t GetID() const noexcept override {
        return 1;
    }
};

class Print: public reactor::Runnable {
public:
    Print() {}

    void operator()(reactor::Objects inputs, reactor::Objects) override {
        auto duration = std::chrono::steady_clock::now() - start;
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << std::endl;
        std::cout << "total calls: " << GetRepo().total_calls.load() << std::endl;
        std::cout << "calls per thread" << std::endl;
        for (size_t i = 0; i < reactor::max_runner_threads; ++i) {
            std::cout << "thread " << i << " calls " << GetRepo().calls_per_thread[i] << std::endl;
        }
        std::cout << "is sorted: " << std::is_sorted(
            inputs.begin(), inputs.end(),
            [](const reactor::Object& left, const reactor::Object& right){ return left.AsInt() < right.AsInt(); }
        ) << std::endl;
        std::exit(0);
    }

    uint64_t GetID() const noexcept override {
        return 2;
    }
};

class TestMain: public reactor::Runnable {
public:
    TestMain() {}

    void operator()(reactor::Objects inputs, reactor::Objects) override {
        std::random_device rnd_device;
        std::mt19937 mersenne_engine {rnd_device()};
        std::uniform_int_distribution<int> dist {1, 100000};
        auto gen = [&](){ return dist(mersenne_engine); };
        std::vector<int> raw_values(1000000);
        std::generate(raw_values.begin(), raw_values.end(), gen);

        reactor::Objects obj_values(raw_values.size());
        std::transform(raw_values.begin(), raw_values.end(), obj_values.begin(), &reactor::Object::Int);
        auto values = reactor::Object::List(std::move(obj_values), reactor::Type::Int());

        auto reply = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({reply}, {}, 2);

        auto split = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({split}, {reactor::Object::Channel(split)}, 0);
        start = std::chrono::steady_clock::now();
        split->Push(reactor::Object::Tuple({values, reactor::Object::Channel(reply)}));
    }

    uint64_t GetID() const noexcept override {
        return 3;
    }
};

int main() {
    std::unordered_map<uint64_t, reactor::Runnable*> runnable_map = {
        {0, new Split()},
        {1, new MergeSorted()},
        {2, new Print()},
        {3, new TestMain()},
    };

    // In production code runnable_map is moved
    GetRepo().Run(3, runnable_map);
    return 0;
}
