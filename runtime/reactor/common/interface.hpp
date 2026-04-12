#pragma once

#include <functional>

#include "type_system.hpp"

namespace reactor {

class ChannelBase : public ObjectValue {
public:
    ChannelBase(ChannelMode mode, Type payload_type);
    virtual ~ChannelBase() noexcept;

    virtual void Push(const Object& message) = 0;
    virtual Maybe<uint64_t> GetID() const noexcept = 0;

    [[nodiscard]] ChannelMode mode() const noexcept;
    [[nodiscard]] const Type& payload_type() const noexcept;
    [[nodiscard]] bool Accepts(const Object& message) const noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;
    std::string Serialize() const override;

private:
    ChannelMode mode_;
    Type payload_type_;
};

using Channels = std::vector<ChannelPtr>;

class Runnable {
public:
    virtual ~Runnable() noexcept;

    virtual void operator()(Objects inputs) = 0;
};

using RunnableOrLambda = std::function<void(Objects)>;

class Repository {
public:
    virtual ~Repository() noexcept;

    virtual void RegisterJoinCase(Channels inputs, Channels outputs, Pointer<RunnableOrLambda> reaction) = 0;
    virtual Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, Type payload_type = Type::Unit()) = 0;

    virtual void Run(Pointer<RunnableOrLambda> reaction) = 0;
};

}  // namespace reactor
