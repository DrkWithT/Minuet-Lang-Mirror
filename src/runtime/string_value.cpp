#include <utility>
#include <sstream>

#include "runtime/string_value.hpp"

namespace Minuet::Runtime {
    StringValue::StringValue()
    : m_items {}, m_length {0} {}

    StringValue::StringValue(std::string s) noexcept
    : m_items {}, m_length {0} {
        for (const auto c : s) {
            m_items.emplace_back(c);
            ++m_length;
        }
    }

    auto StringValue::get_memory_score() const& noexcept -> std::size_t {
        return cm_fast_val_memsize * m_items.size();
    }

    auto StringValue::get_tag() const& noexcept -> ObjectTag {
        return ObjectTag::string;
    }

    auto StringValue::get_size() const& noexcept -> int {
        return m_length;
    }

    auto StringValue::is_frozen() const& noexcept -> bool {
        return false;
    }

    // auto StringValue::size() const& noexcept -> int;

    auto StringValue::push_value([[maybe_unused]] FastValue arg) -> bool {
        // NOTE: char literals can be converted to their underlying integer BUT it must be masked against 127 for a valid ASCII representation.
        const char arg_ascii_repr = static_cast<char>(arg.to_scalar().value_or(0) & 0x7f);

        m_items.emplace_back(arg_ascii_repr);
        ++m_length;

        return true;
    }

    auto StringValue::pop_value(SequenceOpPolicy mode) -> FastValue {
        if (m_items.empty()) {
            return {};
        }

        auto target_value = (mode == SequenceOpPolicy::back)
            ? m_items.back()
            : m_items.front();

        if (mode == SequenceOpPolicy::back) {
            m_items.pop_back();
        } else {
            m_items.erase(m_items.begin());
        }

        --m_length;

        return target_value;
    }

    auto StringValue::set_value(FastValue arg, std::size_t pos) -> bool {
        if (pos >= m_items.size()) {
            return false;
        }

        m_items[pos] = std::move(arg);

        return true;
    }

    auto StringValue::get_value(std::size_t pos) -> std::optional<FastValue*> {
        if (pos >= m_items.size()) {
            return {};
        }

        return &m_items[pos];
    }

    void StringValue::freeze() noexcept {}

    auto StringValue::items() noexcept -> std::vector<FastValue>& {
        return m_items;
    }

    auto StringValue::clone() -> std::unique_ptr<HeapValueBase> {
        return std::make_unique<StringValue>(to_string());
    }

    auto StringValue::as_fast_value() noexcept -> FastValue {
        return {this, FVTag::string};
    }

    auto StringValue::to_string() const& noexcept -> std::string {
        std::ostringstream sout;

        for (const auto& c_item : m_items) {
            sout << static_cast<char>(c_item.to_scalar().value_or(0) & 0x7f);
        }

        return sout.str();
    }
}