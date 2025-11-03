#include <iostream>
#include <print>
#include <string>
#include <stdexcept>

#include "mintrinsics/mnl_utils.hpp"

namespace Minuet::Intrinsics {
    auto native_stoi(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        auto& source_ref = vm.handle_native_fn_access(argc, 0);

        if (auto source_as_obj_p = source_ref.to_object_ptr(); source_as_obj_p) {
            std::string source_text = source_as_obj_p->to_string();

            try {
                vm.handle_native_fn_return(Runtime::FastValue {
                    std::stoi(source_text)
                }, argc);
            } catch (const std::invalid_argument& parse_error) {
                std::println(std::cerr, "NativeError: {}", parse_error.what());

                return false;
            } catch (const std::out_of_range& repr_error) {
                std::println(std::cerr, "NativeError: {}", repr_error.what());

                return false;
            }

            return true;
        }

        return false;
    }

    auto native_stof(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        auto& source_ref = vm.handle_native_fn_access(argc, 0);

        if (auto source_as_obj_p = source_ref.to_object_ptr(); source_as_obj_p) {
            std::string source_text = source_as_obj_p->to_string();

            try {
                vm.handle_native_fn_return(Runtime::FastValue {
                    std::stof(source_text)
                }, argc);
            } catch (const std::invalid_argument& parse_error) {
                std::println(std::cerr, "NativeError: {}", parse_error.what());

                return false;
            } catch (const std::out_of_range& repr_error) {
                std::println(std::cerr, "NativeError: {}", repr_error.what());

                return false;
            }

            return true;
        }

        return false;
    }

    /// TODO: Fix a possible bug of the arguments sequence being garbage collected early if its reference prematurely becomes unreachable. One possible solution could be to rewrite the heap to contain the argv separately from the usual object pool. Then `fun main: [argv]` would have the arguments reference implicitly passed.
    auto native_get_argv(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        auto argv_list_ptr = vm.handle_native_fn_access_argv();

        vm.handle_native_fn_return(Runtime::FastValue {
            argv_list_ptr,
            Runtime::FVTag::sequence,
        }, argc);

        return true;
    }
}