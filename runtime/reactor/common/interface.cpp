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
    return "<channel #" + std::to_string(GetID()) + ": " + GetType().ToString() + ">";
}

std::string ChannelBase::Serialize() const {
    return "channel:" + std::to_string(GetID()) + ":" + GetType().Serialize();
}

// ChannelObject implementation
ChannelObject::ChannelObject(Pointer<ChannelBase> channel) noexcept : channel_(std::move(channel)) {}

ObjectKind ChannelObject::kind() const noexcept {
    return ObjectKind::Channel;
}

Type ChannelObject::GetType() const {
    return channel_->GetType();
}

std::string ChannelObject::ToString() const {
    return channel_->ToString();
}

std::string ChannelObject::Serialize() const {
    return channel_->Serialize();
}

const Pointer<ChannelBase>& ChannelObject::channel() const noexcept {
    return channel_;
}

Runnable::~Runnable() noexcept = default;

Repository::~Repository() noexcept = default;

}  // namespace reactor
