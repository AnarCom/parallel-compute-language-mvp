#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/parallel_improved/repository.hpp>

constexpr auto GetRepo = &reactor::ImprovedRepository::GetRepository;
constexpr size_t TextSize = 5'000'000;

static std::chrono::time_point<std::chrono::steady_clock> start;
static std::int64_t baseline_checksum = 0;
static std::int64_t baseline_max_z = 0;

namespace {

constexpr uint64_t ComputeZFunctionID = 0;
constexpr uint64_t PrintID = 1;
constexpr uint64_t TestMainID = 2;

std::string GenerateText(size_t size = TextSize) {
    std::string text;
    text.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        text.push_back(i % 997 == 0 ? 'b' : 'a');
    }
    return text;
}

std::vector<std::int64_t> CalculateZFunction(const std::string& text) {
    std::vector<std::int64_t> z(text.size(), 0);
    size_t left = 0;
    size_t right = 0;

    for (size_t i = 1; i < text.size(); ++i) {
        if (i <= right) {
            z[i] = static_cast<std::int64_t>(std::min(right - i + 1, static_cast<size_t>(z[i - left])));
        }

        while (i + static_cast<size_t>(z[i]) < text.size()
            && text[static_cast<size_t>(z[i])] == text[i + static_cast<size_t>(z[i])]) {
            ++z[i];
        }

        if (i + static_cast<size_t>(z[i]) > right + 1) {
            left = i;
            right = i + static_cast<size_t>(z[i]) - 1;
        }
    }

    return z;
}

std::int64_t Checksum(const std::vector<std::int64_t>& z) {
    return std::accumulate(z.begin(), z.end(), std::int64_t{0});
}

std::int64_t MaxZ(const std::vector<std::int64_t>& z) {
    return z.empty() ? 0 : *std::max_element(z.begin(), z.end());
}

}  // namespace

class ComputeZFunction: public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects) override {
        auto text = inputs[0].AsTuple()[0].AsString();
        auto reply = inputs[0].AsTuple()[1].AsChannel();

        auto z = CalculateZFunction(text);
        reply->Push(reactor::Object::Tuple({
            reactor::Object::Int(Checksum(z)),
            reactor::Object::Int(MaxZ(z)),
        }));
    }

    uint64_t GetID() const noexcept override {
        return ComputeZFunctionID;
    }
};

class Print: public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects) override {
        auto duration = std::chrono::steady_clock::now() - start;
        auto checksum = inputs[0].AsTuple()[0].AsInt();
        auto max_z = inputs[0].AsTuple()[1].AsInt();

        std::cout << "gojo duration:       " << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << std::endl;
        std::cout << "gojo checksum match: " << (checksum == baseline_checksum) << std::endl;
        std::cout << "gojo max z match:    " << (max_z == baseline_max_z) << std::endl;
        std::exit(0);
    }

    uint64_t GetID() const noexcept override {
        return PrintID;
    }
};

class TestMain: public reactor::Runnable {
public:
    void operator()(reactor::Objects, reactor::Objects) override {
        auto text = GenerateText();

        start = std::chrono::steady_clock::now();
        auto reply = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({reply}, {}, PrintID);

        auto compute = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({compute}, {}, ComputeZFunctionID);
        compute->Push(reactor::Object::Tuple({
            reactor::Object::String(text),
            reactor::Object::Channel(reply),
        }));
    }

    uint64_t GetID() const noexcept override {
        return TestMainID;
    }
};

void ZFunctionBaseline() {
    auto text = GenerateText();

    auto baseline_start = std::chrono::steady_clock::now();
    auto z = CalculateZFunction(text);

    auto baseline_duration = std::chrono::steady_clock::now() - baseline_start;
    baseline_checksum = Checksum(z);
    baseline_max_z = MaxZ(z);

    std::cout << "baseline duration:   " << std::chrono::duration_cast<std::chrono::milliseconds>(baseline_duration) << std::endl;
    std::cout << "baseline checksum:   " << baseline_checksum << std::endl;
    std::cout << "baseline max z:      " << baseline_max_z << "\n" << std::endl;
}

int main() {
    ZFunctionBaseline();

    std::unordered_map<uint64_t, reactor::Runnable*> runnable_map = {
        {ComputeZFunctionID, new ComputeZFunction()},
        {PrintID, new Print()},
        {TestMainID, new TestMain()},
    };

    GetRepo().Run(TestMainID, runnable_map);
    return 0;
}
