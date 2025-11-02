#ifndef MINUET_INTRINSICS_UTILS_HPP
#define MINUET_INTRINSICS_UTILS_HPP

#include "runtime/vm.hpp"

namespace Minuet::Intrinsics {
    [[nodiscard]] auto native_stoi(Runtime::VM::Engine& vm, int16_t argc) -> bool;

    [[nodiscard]] auto native_stof(Runtime::VM::Engine& vm, int16_t argc) -> bool;
}

#endif
