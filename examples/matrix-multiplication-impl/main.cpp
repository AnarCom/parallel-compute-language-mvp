#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <runtime/reactor/common/interface.hpp>
#include <runtime/reactor/parallel_improved/repository.hpp>

constexpr auto GetRepo = &reactor::ImprovedRepository::GetRepository;
constexpr size_t MatrixSize = 512;
constexpr size_t RowsPerTask = 4;

using Matrix = std::vector<std::int64_t>;

static Matrix left_matrix;
static Matrix right_matrix;
static Matrix result_matrix;
static std::int64_t baseline_checksum = 0;
static std::chrono::time_point<std::chrono::steady_clock> start;

namespace {

constexpr uint64_t MultiplyBlockID = 0;
constexpr uint64_t CountRepliesID = 1;
constexpr uint64_t PrintID = 2;
constexpr uint64_t TestMainID = 3;

std::int64_t ValueAt(const Matrix& matrix, size_t row, size_t col) {
    return matrix[row * MatrixSize + col];
}

std::int64_t& ValueAt(Matrix& matrix, size_t row, size_t col) {
    return matrix[row * MatrixSize + col];
}

Matrix GenerateLeftMatrix() {
    Matrix matrix(MatrixSize * MatrixSize);
    for (size_t row = 0; row < MatrixSize; ++row) {
        for (size_t col = 0; col < MatrixSize; ++col) {
            ValueAt(matrix, row, col) = static_cast<std::int64_t>((row + col) % 17);
        }
    }
    return matrix;
}

Matrix GenerateRightMatrix() {
    Matrix matrix(MatrixSize * MatrixSize);
    for (size_t row = 0; row < MatrixSize; ++row) {
        for (size_t col = 0; col < MatrixSize; ++col) {
            ValueAt(matrix, row, col) = static_cast<std::int64_t>((row * 3 + col * 5) % 19);
        }
    }
    return matrix;
}

void MultiplyRows(size_t row_begin, size_t row_end, Matrix& output) {
    for (size_t row = row_begin; row < row_end; ++row) {
        for (size_t col = 0; col < MatrixSize; ++col) {
            std::int64_t sum = 0;
            for (size_t mid = 0; mid < MatrixSize; ++mid) {
                sum += ValueAt(left_matrix, row, mid) * ValueAt(right_matrix, mid, col);
            }
            ValueAt(output, row, col) = sum;
        }
    }
}

std::int64_t Checksum(const Matrix& matrix) {
    std::int64_t checksum = 0;
    for (auto value : matrix) {
        checksum += value;
    }
    return checksum;
}

}  // namespace

class MultiplyBlock: public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects) override {
        auto row_begin = static_cast<size_t>(inputs[0].AsTuple()[0].AsInt());
        auto row_end = static_cast<size_t>(inputs[0].AsTuple()[1].AsInt());
        auto reply = inputs[0].AsTuple()[2].AsChannel();

        MultiplyRows(row_begin, row_end, result_matrix);
        reply->Push(reactor::Object::Bool(true));
    }

    uint64_t GetID() const noexcept override {
        return MultiplyBlockID;
    }
};

class CountReplies: public reactor::Runnable {
public:
    void operator()(reactor::Objects inputs, reactor::Objects context) override {
        auto block_done = inputs[0].AsBool();
        auto count = inputs[1].AsInt();
        auto reply = context[0].AsChannel();
        auto count_channel = context[1].AsChannel();

        if (!block_done) {
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
        auto checksum = Checksum(result_matrix);

        std::cout << "gojo duration:        " << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << std::endl;
        std::cout << "gojo completed:       " << inputs[0].AsBool() << std::endl;
        std::cout << "gojo checksum match:  " << (checksum == baseline_checksum) << std::endl;
        std::exit(0);
    }

    uint64_t GetID() const noexcept override {
        return PrintID;
    }
};

class TestMain: public reactor::Runnable {
public:
    void operator()(reactor::Objects, reactor::Objects) override {
        result_matrix.assign(MatrixSize * MatrixSize, 0);

        start = std::chrono::steady_clock::now();
        auto reply = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({reply}, {}, PrintID);

        reactor::Channels block_replies;
        for (size_t row = 0; row < MatrixSize; row += RowsPerTask) {
            block_replies.push_back(GetRepo().NewChannel());
        }

        auto count = GetRepo().NewChannel();
        for (const auto& block_reply : block_replies) {
            GetRepo().RegisterJoinCase(
                {block_reply, count},
                {reactor::Object::Channel(reply), reactor::Object::Channel(count)},
                CountRepliesID);
        }

        auto multiply = GetRepo().NewChannel();
        GetRepo().RegisterJoinCase({multiply}, {}, MultiplyBlockID);

        size_t block_index = 0;
        for (size_t row = 0; row < MatrixSize; row += RowsPerTask) {
            auto row_end = std::min(row + RowsPerTask, MatrixSize);
            multiply->Push(reactor::Object::Tuple({
                reactor::Object::Int(static_cast<std::int64_t>(row)),
                reactor::Object::Int(static_cast<std::int64_t>(row_end)),
                reactor::Object::Channel(block_replies[block_index]),
            }));
            ++block_index;
        }

        count->Push(reactor::Object::Int(static_cast<std::int64_t>(block_replies.size() - 1)));
    }

    uint64_t GetID() const noexcept override {
        return TestMainID;
    }
};

void MatrixMultiplicationBaseline() {
    Matrix output(MatrixSize * MatrixSize, 0);

    auto baseline_start = std::chrono::steady_clock::now();
    MultiplyRows(0, MatrixSize, output);

    auto baseline_duration = std::chrono::steady_clock::now() - baseline_start;
    baseline_checksum = Checksum(output);

    std::cout << "baseline duration:    " << std::chrono::duration_cast<std::chrono::milliseconds>(baseline_duration) << std::endl;
    std::cout << "baseline checksum:    " << baseline_checksum << "\n" << std::endl;
}

int main() {
    left_matrix = GenerateLeftMatrix();
    right_matrix = GenerateRightMatrix();

    MatrixMultiplicationBaseline();

    std::unordered_map<uint64_t, reactor::Runnable*> runnable_map = {
        {MultiplyBlockID, new MultiplyBlock()},
        {CountRepliesID, new CountReplies()},
        {PrintID, new Print()},
        {TestMainID, new TestMain()},
    };

    GetRepo().Run(TestMainID, runnable_map);
    return 0;
}
