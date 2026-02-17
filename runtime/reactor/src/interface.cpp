#include "interface.hpp"

namespace reactor {

Object::~Object() noexcept {}

Callback::~Callback() noexcept {}

ChannelBase::~ChannelBase() noexcept {}

void ChannelBase::SetID(uint64_t id) noexcept {
    this->id = id;
}

Maybe<uint64_t> ChannelBase::GetID() const noexcept {
    return this->id;
}

void ChannelBase::SetCallback(Pointer<Callback> callback) noexcept {
    this->callback = callback;
}

Pointer<Callback> ChannelBase::GetCallback() const noexcept {
    return this->callback;
}

void ChannelBase::Push(Object message) {
    auto maybe_id = this->GetID();
    auto maybe_callback = this->GetCallback();
    if (maybe_id.has_value() && bool(maybe_callback)) {
        maybe_callback->OnMessage(maybe_id.value(), message);
    }
}

Runnable::~Runnable() noexcept {}

Repository::~Repository() noexcept {}

}  // namespace reactor
