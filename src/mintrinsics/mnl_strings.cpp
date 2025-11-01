#include "mintrinsics/mnl_strings.hpp"
#include "runtime/string_value.hpp"

namespace Minuet::Intrinsics {
    auto native_strlen(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        auto arg_0 = vm.handle_native_fn_access(argc, 0);
        
        if (auto arg_obj_ptr = arg_0.to_object_ptr(); arg_obj_ptr) {
            vm.handle_native_fn_return({arg_obj_ptr->get_size()}, argc);
            return true;
        }

        return false;
    }

    /// @brief Joins a string with another string, pushing the source's characters to the destination in sequence.
    auto native_strcat(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        auto source_arg_p = vm.handle_native_fn_access(argc, 1).to_object_ptr();
        auto target_arg_p = vm.handle_native_fn_access(argc, 0).to_object_ptr();

        if (!target_arg_p || !source_arg_p) {
            return false;
        }

        if (source_arg_p->get_tag() != Runtime::ObjectTag::string || target_arg_p->get_tag() != Runtime::ObjectTag::string) {
            return false;
        }

        for (const auto& source_items = source_arg_p->items(); const auto& item : source_items) {
            if (!target_arg_p->push_value(item)) {
                return false;
            }
        }

        return true;
    }

    /// @brief Slices a substring copy from a source string by `begin` ahead by `length`.
    auto native_substr(Runtime::VM::Engine& vm, int16_t argc) -> bool {
        auto source_arg_p = vm.handle_native_fn_access(argc, 0).to_object_ptr();
        const auto slice_begin = vm.handle_native_fn_access(argc, 1).to_scalar().value_or(0);
        const auto slice_len = vm.handle_native_fn_access(argc, 2).to_scalar().value_or(0);

        if (!source_arg_p || slice_len == 0) {
            return false;
        }

        if (source_arg_p->get_tag() != Runtime::ObjectTag::string) {
            return false;
        }

        const auto slice_end = slice_begin + slice_len;

        if (const auto source_len = source_arg_p->get_size(); slice_end >= source_len) {
            return false;
        }

        if (auto& result_obj_p = vm.handle_native_fn_access_heap().try_create_value<Runtime::StringValue>(
            source_arg_p->to_string().substr(slice_begin, slice_len)
        ); result_obj_p) {
            vm.handle_native_fn_return(
                Runtime::FastValue {
                    result_obj_p.get(),
                    Runtime::FVTag::string,
                },
                argc
            );

            return true;
        }

        return false;
    }
}
