#include "interface.hpp"
#include "lifecycle.hpp"

namespace reactor {

ChannelBase::ChannelBase(ChannelMode mode, Type payload_type)
    : mode_(mode), payload_type_(std::move(payload_type)), lifecycle_() {}

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

// ChannelBase lifecycle methods
void ChannelBase::Close() noexcept {
    lifecycle_.Close();
}

ChannelState ChannelBase::GetState() const noexcept {
    return lifecycle_.GetState();
}

bool ChannelBase::CanAcceptMessages() const noexcept {
    return lifecycle_.CanAcceptMessages();
}

bool ChannelBase::CanConsumeMessages() const noexcept {
    return lifecycle_.CanConsumeMessages();
}

bool ChannelBase::IsActive() const noexcept {
    return lifecycle_.IsActive();
}

bool ChannelBase::IsClosed() const noexcept {
    return lifecycle_.IsClosed();
}

ChannelLifecycle& ChannelBase::GetLifecycle() noexcept {
    return lifecycle_;
}

const ChannelLifecycle& ChannelBase::GetLifecycle() const noexcept {
    return lifecycle_;
}

}  // namespace reactor
