#include <iostream>
#include <print>
#include <string>
#include <vector>

#include "mintrinsics/mnl_stdio.hpp"
#include "mintrinsics/mnl_lists.hpp"
#include "mintrinsics/mnl_strings.hpp"
#include "mintrinsics/mnl_utils.hpp"
#include "driver/driver.hpp"
#include "driver/plugins/disassembler.hpp"
#include "driver/plugins/ir_dumper.hpp"

constexpr auto minuet_version_major = 0;
constexpr auto minuet_version_minor = 8;
constexpr auto minuet_version_patch = 0;
constexpr auto minuet_run_argv_offset = 3;

using namespace Minuet;


class DriverBuilder {
private:
    bool m_ir_printer_on;
    bool m_bc_printer_on;

public:
    DriverBuilder() noexcept
    : m_ir_printer_on {false}, m_bc_printer_on {false} {}

    [[nodiscard]] auto config_ir_dumper(bool enabled_flag) noexcept -> DriverBuilder* {
        m_ir_printer_on = enabled_flag;

        return this;
    }

    [[nodiscard]] auto config_bc_dumper(bool enabled_flag) noexcept -> DriverBuilder* {
        m_bc_printer_on = enabled_flag;

        return this;
    }

    [[nodiscard]] auto build() noexcept -> Driver::Driver {
        Driver::Driver interpreter_driver;

        Driver::Plugins::IRDumper ir_printer;
        ir_printer.set_disable_flag(!m_ir_printer_on);        
        Driver::Plugins::Disassembler bc_printer;
        bc_printer.set_disable_flag(!m_bc_printer_on);

        interpreter_driver.add_ir_dumper(ir_printer);
        interpreter_driver.add_disassembler(bc_printer);

        return interpreter_driver;
    }
};

/**
 * @brief Stringifies the native main function's `argv` strings from argument 3 and after, stopping at the terminating `nullptr`. The resulting `std::vector<std::string>` will then be injected into the interpreter via builder.
 * 
 * @param argv Pointer to `argv[3]` for `int main()`.
 * @return std::vector<std::string> 
 */
[[nodiscard]] auto consume_running_args(char* argv[], int full_argc) -> std::vector<std::string> {
    std::vector<std::string> program_args;

    for (auto arg_pos = minuet_run_argv_offset; arg_pos < full_argc; ++arg_pos) {
        program_args.emplace_back(argv[arg_pos]);
    }

    return program_args;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::println(std::cerr, "Invalid argument count, try 'minuetm info' for help.");

        return 1;
    }

    std::string arg_1 {argv[1]};
    std::string arg_2 { (argc >= 3) ? argv[2] : ""};

    DriverBuilder driver_builder;
    Driver::Driver app;

    if (arg_1 == "info") {
        std::println("minuetm v{}.{}.{}\n\nUsage: ./minuetm [info | compile-only <main-file> | run <main-file>]\n\tinfo []: shows usage info and version.", minuet_version_major, minuet_version_minor, minuet_version_patch);

        return 0;
    } else if (arg_1 == "compile-only" && !arg_2.empty()) {
        app = driver_builder.config_ir_dumper(true)->config_bc_dumper(true)->build();
    } else if (arg_1 == "run" && !arg_2.empty()) {
        app = driver_builder.config_ir_dumper(false)->config_bc_dumper(false)->build();
    } else {
        std::println("minuetm v{}.{}.{}\n\nUsage: ./minuetm [info | compile-only <main-file> | run <main-file>]\n\tinfo []: shows usage info and version.", minuet_version_major, minuet_version_minor, minuet_version_patch);

        return 1;
    }

    // stdlib standard I/O
    app.register_native_proc({"print", Intrinsics::native_print_value});
    app.register_native_proc({"prompt_int", Intrinsics::native_prompt_int});
    app.register_native_proc({"prompt_float", Intrinsics::native_prompt_float});
    app.register_native_proc({"readln", Intrinsics::native_readln});

    // stdlib lists
    app.register_native_proc({"len_of", Intrinsics::native_len_of});
    app.register_native_proc({"list_push_back", Intrinsics::native_list_push_back});
    app.register_native_proc({"list_pop_back", Intrinsics::native_list_pop_back});
    app.register_native_proc({"list_pop_front", Intrinsics::native_list_pop_front});
    app.register_native_proc({"list_concat", Intrinsics::native_list_concat});

    // stdlib strings
    app.register_native_proc({"strlen", Intrinsics::native_strlen});
    app.register_native_proc({"strcat", Intrinsics::native_strcat});
    app.register_native_proc({"substr", Intrinsics::native_substr});

    // stdlib utils
    app.register_native_proc({"stoi", Intrinsics::native_stoi});
    app.register_native_proc({"stof", Intrinsics::native_stof});
    app.register_native_proc({"get_argv", Intrinsics::native_get_argv});

    return app(arg_2, consume_running_args(argv, argc)) ? 0 : 1 ;
}
