#ifndef MINUET_INTRINSICS_STRINGS_HPP
#define MINUET_INTRINSICS_STRINGS_HPP

#include "runtime/vm.hpp"

namespace Minuet::Intrinsics {
    /// @brief Gets the count of a list's items.
    [[nodiscard]] auto native_strlen(Runtime::VM::Engine& vm, int16_t argc) -> bool;

    /// @brief Joins a string with another string, pushing the source's characters to the destination in sequence.
    [[nodiscard]] auto native_strcat(Runtime::VM::Engine& vm, int16_t argc) -> bool;

    /// @brief Slices a substring copy from a source string by `begin` ahead by `length`.
    [[nodiscard]] auto native_substr(Runtime::VM::Engine& vm, int16_t argc) -> bool;
}

#endif
