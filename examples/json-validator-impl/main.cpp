#include <chrono>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/parallel_improved/repository.hpp>

constexpr auto GetRepo = &reactor::ImprovedRepository::GetRepository;
constexpr size_t JsonItemsCount = 1'000;
constexpr size_t JsonNumberDigits = 100'000;

static std::chrono::time_point<std::chrono::steady_clock> start;
static std::string input_json;

namespace {

constexpr uint64_t ValidateJsonID = 0;
constexpr uint64_t CountRepliesID = 1;
constexpr uint64_t PrintID = 2;
constexpr uint64_t TestMainID = 3;

std::string Trim(std::string_view value) {
    size_t begin = 0;
    while (begin < value.size() && std::isspace(static_cast<unsigned char>(value[begin]))) {
        ++begin;
    }

    size_t end = value.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }

    return std::string(value.substr(begin, end - begin));
}

std::vector<std::string> SplitByComma(std::string_view value) {
    std::vector<std::string> parts;
    size_t begin = 0;
    while (begin <= value.size()) {
        auto comma = value.find(',', begin);
        if (comma == std::string_view::npos) {
            parts.push_back(Trim(value.substr(begin)));
            break;
        }
        parts.push_back(Trim(value.substr(begin, comma - begin)));
        begin = comma + 1;
    }
    return parts;
}

bool IsQuotedString(std::string_view value) {
    return value.size() >= 2 && value.front() == '"' && value.back() == '"';
}

bool IsNumber(std::string_view value) {
    if (value.empty()) {
        return false;
    }

    size_t pos = 0;
    if (value[pos] == '-') {
        ++pos;
    }

    if (pos == value.size() || !std::isdigit(static_cast<unsigned char>(value[pos]))) {
        return false;
    }

    while (pos < value.size() && std::isdigit(static_cast<unsigned char>(value[pos]))) {
        ++pos;
    }

    if (pos < value.size() && value[pos] == '.') {
        ++pos;
        if (pos == value.size() || !std::isdigit(static_cast<unsigned char>(value[pos]))) {
            return false;
        }
        while (pos < value.size() && std::isdigit(static_cast<unsigned char>(value[pos]))) {
            ++pos;
        }
    }

    if (pos < value.size() && (value[pos] == 'e' || value[pos] == 'E')) {
        ++pos;
        if (pos < value.size() && (value[pos] == '+' || value[pos] == '-')) {
            ++pos;
        }
        if (pos == value.size() || !std::isdigit(static_cast<unsigned char>(value[pos]))) {
            return false;
        }
        while (pos < value.size() && std::isdigit(static_cast<unsigned char>(value[pos]))) {
            ++pos;
        }
    }

    return pos == value.size();
}

std::vector<std::string> ChildrenForValidation(const std::string& json) {
    if (json.size() < 2) {
        return {};
    }

    if (json.front() == '[' && json.back() == ']') {
        auto body = Trim(std::string_view(json).substr(1, json.size() - 2));
        if (body.empty()) {
            return {};
        }
        return SplitByComma(body);
    }

    if (json.front() == '{' && json.back() == '}') {
        auto body = Trim(std::string_view(json).substr(1, json.size() - 2));
        if (body.empty()) {
            return {};
        }
        return SplitByComma(body);
    }

    auto colon = json.find(':');
    if (colon != std::string::npos) {
        auto key = Trim(std::string_view(json).substr(0, colon));
        auto value = Trim(std::string_view(json).substr(colon + 1));
        if (!IsQuotedString(key) || value.empty()) {
            return {};
        }
        return {value};
    }

    return {};
}

bool IsContainerOrMember(const std::string& json) {
    if (json.size() >= 2) {
        if ((json.front() == '[' && json.back() == ']') || (json.front() == '{' && json.back() == '}')) {
            return true;
        }
    }
    return json.find(':') != std::string::npos;
}

bool IsValidScalar(const std::string& json) {
    return IsQuotedString(json)
        || IsNumber(json)
        || json == "true"
        || json == "false"
        || json == "null";
}

bool HasValidContainerShape(const std::string& json) {
    if (json.empty()) {
        return false;
    }

    if (json.front() == '[' || json.back() == ']') {
        return json.size() >= 2 && json.front() == '[' && json.back() == ']';
    }

    if (json.front() == '{' || json.back() == '}') {
        return json.size() >= 2 && json.front() == '{' && json.back() == '}';
    }

    auto colon = json.find(':');
    if (colon == std::string::npos) {
        return false;
    }

    auto key = Trim(std::string_view(json).substr(0, colon));
    auto value = Trim(std::string_view(json).substr(colon + 1));
    return IsQuotedString(key) && !value.empty();
}

std::string GenerateJson(size_t size = JsonItemsCount) {
    std::string json = "[";
    const auto number = std::string(JsonNumberDigits, '1');
    for (size_t i = 0; i < size; ++i) {
        if (i != 0) {
            json += ",";
        }
        json += number;
    }
    json += "]";
    return json;
}

}  // namespace

class ValidateJson: public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        auto json = Trim(inputs[0].AsTuple()[0].AsString());
        auto reply = inputs[0].AsTuple()[1].AsChannel();
        auto validate = context[0].AsChannel();

        if (!IsContainerOrMember(json)) {
            reply->Push(reactor::Object::Bool(IsValidScalar(json)));
            return;
        }

        if (!HasValidContainerShape(json)) {
            reply->Push(reactor::Object::Bool(false));
            return;
        }

        auto children = ChildrenForValidation(json);
        if (children.empty()) {
            reply->Push(reactor::Object::Bool(true));
            return;
        }

        reactor::Channels child_replies;
        child_replies.reserve(children.size());
        for (size_t i = 0; i < children.size(); ++i) {
            child_replies.push_back(GetRepo().NewChannel());
        }

        auto count = GetRepo().NewChannel();
        for (const auto& child_reply : child_replies) {
            GetRepo().RegisterJoinCase(
                {child_reply, count},
                {reactor::Object::Channel(reply), reactor::Object::Channel(count)},
                CountRepliesID);
        }

        for (size_t i = 0; i < children.size(); ++i) {
            validate->Push(reactor::Object::Tuple({
                reactor::Object::String(children[i]),
                reactor::Object::Channel(child_replies[i]),
            }));
        }

        count->Push(reactor::Object::Int(static_cast<std::int64_t>(children.size() - 1)));
    }

    uint64_t GetID() const noexcept override {
        return ValidateJsonID;
    }
};

class CountReplies: public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        auto child_valid = inputs[0].AsBool();
        auto count = inputs[1].AsInt();
        auto reply = context[0].AsChannel();
        auto count_channel = context[1].AsChannel();

        if (!child_valid) {
            reply->Push(reactor::Object::Bool(false));
            return;
        }

        if (count == 0) {
            reply->Push(reactor::Object::Bool(true));
            return;
        }

        count_channel->Push(reactor::Object::Int(count - 1));
    }

    uint64_t GetID() const noexcept override {
        return CountRepliesID;
    }
};

class Print: public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects) override {
        auto duration = std::chrono::steady_clock::now() - start;
        std::cout << "gojo duration:  " << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << std::endl;
        std::cout << "gojo is valid:  " << inputs[0].AsBool() << std::endl;
        std::exit(0);
    }

    uint64_t GetID() const noexcept override {
        return PrintID;
    }
};

class TestMain: public reactor::Runnable {
public:
    void operator()(reactor::Objects, reactor::Objects) override {
        start = std::chrono::steady_clock::now();
        auto reply = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({reply}, {}, PrintID);

        auto validate = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({validate}, {reactor::Object::Channel(validate)}, ValidateJsonID);
        validate->Push(reactor::Object::Tuple({
            reactor::Object::String(input_json),
            reactor::Object::Channel(reply),
        }));
    }

    uint64_t GetID() const noexcept override {
        return TestMainID;
    }
};

bool ValidateJsonBaseline(const std::string& raw_json) {
    auto json = Trim(raw_json);

    if (!IsContainerOrMember(json)) {
        return IsValidScalar(json);
    }

    if (!HasValidContainerShape(json)) {
        return false;
    }

    auto children = ChildrenForValidation(json);
    for (const auto& child : children) {
        if (!ValidateJsonBaseline(child)) {
            return false;
        }
    }
    return true;
}

void JsonValidatorBaseline(const std::string& json) {
    auto baseline_start = std::chrono::steady_clock::now();
    auto valid = ValidateJsonBaseline(json);

    auto baseline_duration = std::chrono::steady_clock::now() - baseline_start;
    std::cout << "baseline duration:  " << std::chrono::duration_cast<std::chrono::milliseconds>(baseline_duration) << std::endl;
    std::cout << "baseline is valid:  " << valid << "\n" << std::endl;
}

int main(int argc, char** argv) {
    input_json = argc > 1 ? argv[1] : GenerateJson();

    JsonValidatorBaseline(input_json);

    std::unordered_map<uint64_t, reactor::Runnable*> runnable_map = {
        {ValidateJsonID, new ValidateJson()},
        {CountRepliesID, new CountReplies()},
        {PrintID, new Print()},
        {TestMainID, new TestMain()},
    };

    GetRepo().Run(TestMainID, runnable_map);
    return 0;
}
