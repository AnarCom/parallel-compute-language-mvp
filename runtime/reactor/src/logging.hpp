#pragma once

#include <string_view>

#ifndef NDEBUG
#include <cstdlib>
#include <iostream>
#endif

namespace reactor::debug {

inline void runtime_assert(bool condition, const std::string_view& message) noexcept {
    #ifndef NDEBUG
    if (!condition) {
        std::cerr << message << std::endl;
        std::abort();
    }
    #endif
}

inline void print(const std::string_view& message) noexcept {
    #ifndef NDEBUG
    std::cerr << message << std::endl;
    #endif
}

}  // namespace reactor::debug