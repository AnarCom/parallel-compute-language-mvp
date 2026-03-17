#include "interface.hpp"

namespace reactor {

ChannelBase::ChannelBase(ChannelMode mode, Type payload_type)
    : mode_(mode), payload_type_(std::move(payload_type)) {}

ChannelBase::~ChannelBase() noexcept = default;

ChannelMode ChannelBase::mode() const noexcept {
    return mode_;
}

const Type& ChannelBase::payload_type() const noexcept {
    return payload_type_;
}

bool ChannelBase::Accepts(const Object& message) const noexcept {
    return payload_type_.Accepts(message);
}

ObjectKind ChannelBase::kind() const noexcept {
    return ObjectKind::Channel;
}

Type ChannelBase::GetType() const {
    return Type::Channel(mode_, payload_type_);
}

std::string ChannelBase::ToString() const {
    if (auto id = GetID(); id.has_value()) {
        return "<channel #" + std::to_string(*id) + ": " + GetType().ToString() + ">";
    }
    return "<channel: " + GetType().ToString() + ">";
}

Runnable::~Runnable() noexcept = default;

Repository::~Repository() noexcept = default;

}  // namespace reactor
