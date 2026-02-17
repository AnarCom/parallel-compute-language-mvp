#pragma once

#include <memory>
#include <queue>
#include <optional>
#include <vector>

namespace reactor {

template <typename T>
using Pointer = std::shared_ptr<T>;

template <typename T>
using Maybe = std::optional<T>;

class ChannelBase;

class Object {
public:
    virtual ~Object() noexcept;
    int integer = 0;
    Pointer<ChannelBase> channel = {};
};

using Objects = std::vector<Object>;

class Callback {
public:
    ~Callback() noexcept;

    virtual void OnMessage(uint64_t id, Object message) noexcept = 0;
};

class ChannelBase: public Object {
public:
    virtual ~ChannelBase() noexcept;

    void SetID(uint64_t id) noexcept;
    Maybe<uint64_t> GetID() const noexcept;

    void SetCallback(Pointer<Callback> callback) noexcept;
    Pointer<Callback> GetCallback() const noexcept;

    virtual void Push(Object message);

private:
    Maybe<uint64_t> id;
    Pointer<Callback> callback;
};

using Channels = std::vector<Pointer<ChannelBase>>;

class Runnable {
public:
    virtual ~Runnable() noexcept;

    virtual void Run(Objects inputs, Channels outputs) = 0;
};

class Repository {
public:
    virtual ~Repository() noexcept;

    virtual void RegisterJoinCase(Channels inputs, Channels outputs, Pointer<Runnable> reaction) noexcept = 0;
};

}  // namespace reactor
