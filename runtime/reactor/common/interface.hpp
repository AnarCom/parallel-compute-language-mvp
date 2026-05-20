#pragma once

#include <functional>
#include <unordered_map>

#include "helpers.hpp"
#include "type_system.hpp"
#include "lifecycle.hpp"

namespace reactor {

class ChannelBase;

using ChannelPtr = Pointer<ChannelBase>;

class ChannelBase : public ObjectValue {
public:
    ChannelBase(ChannelMode mode, Type payload_type);
    virtual ~ChannelBase() noexcept;

    virtual void Push(const Object& message) = 0;
    virtual uint64_t GetID() const noexcept = 0;

    [[nodiscard]] ChannelMode mode() const noexcept;
    [[nodiscard]] const Type& payload_type() const noexcept;
    [[nodiscard]] bool Accepts(const Object& message) const noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;
    std::string Serialize() const override;

    // Lifecycle methods
    void Close() noexcept;
    ChannelState GetState() const noexcept;
    bool CanAcceptMessages() const noexcept;
    bool CanConsumeMessages() const noexcept;
    bool IsActive() const noexcept;
    bool IsClosed() const noexcept;

protected:
    ChannelLifecycle& GetLifecycle() noexcept;
    const ChannelLifecycle& GetLifecycle() const noexcept;

private:
    ChannelMode mode_;
    Type payload_type_;
    ChannelLifecycle lifecycle_;
};

using Channels = std::vector<ChannelPtr>;

class Runnable {
public:
    virtual ~Runnable() noexcept;

    virtual void operator()(Objects inputs, Objects context) = 0;
    virtual uint64_t GetID() const noexcept = 0;
};

class Repository {
public:
    virtual ~Repository() noexcept;

    virtual void RegisterJoinCase(Channels inputs, Objects context, uint64_t runnable_id) = 0;
    virtual Pointer<ChannelBase> NewChannel(ChannelMode mode = ChannelMode::Async, Type payload_type = Type::Unit()) = 0;

    virtual void Run(uint64_t main_runnable_id, std::unordered_map<uint64_t, Runnable*> runnable_map) = 0;
};

}  // namespace reactor
