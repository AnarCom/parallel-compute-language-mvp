#pragma once

#include <memory>
#include <optional>

namespace reactor {

template <typename T>
using Pointer = std::shared_ptr<T>;

template <typename T>
using Maybe = std::optional<T>;

}  // namespace reactor
