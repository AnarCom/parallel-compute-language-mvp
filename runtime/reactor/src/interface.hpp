#pragma once

#include <atomic>
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

class ChannelBase: public Object {
public:
    virtual ~ChannelBase() noexcept;

    virtual void Push(Object message) = 0;
    virtual Maybe<uint64_t> GetID() const noexcept = 0;
};

using Channels = std::vector<Pointer<ChannelBase>>;

class Runnable {
public:
    virtual ~Runnable() noexcept;

    virtual void operator()(Objects inputs) = 0;
};

using RunnableOrLambda = std::function<void (Objects)>;

class Repository {
public:
    virtual ~Repository() noexcept;

    /* currently outputs is an empty vector. Will be provided later for runtime optimization purposes */
    virtual void RegisterJoinCase(Channels inputs, Channels outputs, Pointer<RunnableOrLambda> reaction) = 0;
    virtual Pointer<ChannelBase> NewChannel() = 0;

    virtual void Run(Pointer<RunnableOrLambda> reaction) = 0;
};

}  // namespace reactor
