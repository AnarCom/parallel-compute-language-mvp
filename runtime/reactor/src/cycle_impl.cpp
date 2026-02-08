#include "cycle_impl.hpp"

namespace reactor {

// Does nothing
void CycleCallback::OnMessage(uint64_t id, Object message) noexcept {}

CycleRepository& CycleRepository::GetRepository() {
    static CycleRepository instance;
    return instance;
}

// ID and Callback is unused
void CycleRepository::RegisterJoinCase(Channels inputs, Channels outputs, Pointer<Runnable> reaction) noexcept {
    this->cases.push_back({.inputs = inputs, .outputs = outputs, .reaction = reaction});
}

void CycleRepository::CheckCases() noexcept {
    auto guard = std::lock_guard(this->lock);
    auto total_cases = this->cases.size();
    for (size_t i = 0; i < total_cases; ++i) {
        this->CheckCase((i + this->cycle_offset) % total_cases);
    }
}

void CycleRepository::CheckCase(size_t i) noexcept {
    auto& current_case = cases.at(i);
    auto is_ready = std::all_of(
        current_case.inputs.begin(),
        current_case.inputs.end(),
        [](Pointer<ChannelBase> channel) { return !channel->IsEmpty(); }
    );
    if (is_ready) {
        Objects objects;
        for (auto& channel : current_case.inputs) {
            objects.push_back(channel->Pop());
        }
        current_case.reaction->Run(objects, current_case.outputs);
    }
}

CycleRepository::CycleRepository(): cases(), cycle_offset(0) {}
    

}  // namespace reactor
