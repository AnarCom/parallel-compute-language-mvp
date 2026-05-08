#pragma once

#include <mutex>

#include "interface.hpp"

namespace reactor {

struct JoinCase {
    Channels inputs;
    Channels outputs;
    Pointer<Runnable> reaction;
};

class CycleCallback: public Callback {
    void OnMessage(uint64_t id, Object message) noexcept override;
};

class CycleRepository: public Repository {
public:
    static CycleRepository& GetRepository();
    void RegisterJoinCase(Channels inputs, Channels outputs, Pointer<Runnable> reaction) noexcept override;
    void CheckCases() noexcept;

private:
    std::vector<JoinCase> cases;
    size_t cycle_offset;

    std::mutex lock;

    CycleRepository();
    void CheckCase(size_t i) noexcept;
};

}  // namespace reactor
