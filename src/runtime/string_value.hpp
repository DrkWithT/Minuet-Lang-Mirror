#ifndef MINUET_RUNTIME_STRING_VALUE_HPP
#define MINUET_RUNTIME_STRING_VALUE_HPP

#include <string>

#include "runtime/fast_value.hpp"

namespace Minuet::Runtime {
    class StringValue : public HeapValueBase {
    public:
        StringValue();
        StringValue(std::string s) noexcept;

        auto get_memory_score() const& noexcept -> std::size_t override;
        auto get_tag() const& noexcept -> ObjectTag override;
        auto get_size() const& noexcept -> int override;
        auto is_frozen() const& noexcept -> bool override;

        // auto size() const& noexcept -> int override;
        auto push_value(FastValue arg) -> bool override;
        auto pop_value(SequenceOpPolicy mode) -> FastValue override;
        auto set_value(FastValue arg, std::size_t pos) -> bool override;
        auto get_value(std::size_t pos) -> std::optional<FastValue*> override;

        void freeze() noexcept override;
        auto items() noexcept -> std::vector<FastValue>& override;
        auto items() const noexcept -> const std::vector<FastValue>& override;
        auto clone() -> std::unique_ptr<HeapValueBase> override;

        auto as_fast_value() noexcept -> FastValue override;
        auto to_string() const& noexcept -> std::string override;

        [[nodiscard]] auto operator==(const HeapValueBase& rhs) const noexcept -> bool override;

    private:
        static constexpr auto cm_fast_val_memsize = 16UL;

        std::vector<FastValue> m_items;
        int m_length;
    };
}

#endif
