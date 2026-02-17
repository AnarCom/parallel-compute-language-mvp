#pragma once

#include <string>

#ifndef NDEBUG
#include <cstdlib>
#include <iostream>
#endif

namespace reactor::debug {

inline void runtime_assert(bool condition, const std::string& message) noexcept {
    #ifndef NDEBUG
    if (!condition) {
        std::cerr << message << std::endl;
        std::abort();
    }
    #endif
}

}  // namespace reactor::debug