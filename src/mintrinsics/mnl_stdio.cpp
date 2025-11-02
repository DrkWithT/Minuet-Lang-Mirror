#include <iostream>
#include <print>
#include <utility>

#include "mintrinsics/mnl_stdio.hpp"
#include "runtime/string_value.hpp"

namespace Minuet::Intrinsics {
    auto native_print_value(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        const auto& argument_value = vm.handle_native_fn_access(argc, 0);

        std::println("{}", argument_value.to_string());

        return true;
    }

    auto native_prompt_int(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        int temp_i32 = 0;

        std::cin >> temp_i32;

        vm.handle_native_fn_return(Runtime::FastValue {temp_i32}, argc);

        return true;
    }

    auto native_prompt_float(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        double temp_f64 = 0;

        std::cin >> temp_f64;

        vm.handle_native_fn_return(Runtime::FastValue {temp_f64}, argc);

        return true;
    }

    auto native_readln(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        std::string temp_line;

        std::getline(std::cin, temp_line);

        if (auto& line_obj_p = vm.handle_native_fn_access_heap().try_create_value<Runtime::StringValue>(std::move(temp_line)); line_obj_p) {
            vm.handle_native_fn_return(Runtime::FastValue {
                line_obj_p.get(),
                Runtime::FVTag::string
            }, argc);

            return true;
        }

        return false;
    }
}