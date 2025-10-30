#include <memory>
#include <queue>

#include "runtime/heap_storage.hpp"

namespace Minuet::Runtime {
    auto HeapStorage::allocate_id() -> std::size_t {
        std::size_t next_id = 0;

        if (!m_hole_list.empty()) {
            next_id = m_hole_list.front();
            m_hole_list.pop();
        } else {
            next_id = m_next_id;
            ++m_next_id;
        }

        return next_id;
    }

    HeapStorage::HeapStorage()
    : m_hole_list {}, m_objects {}, m_dud {}, m_overhead {0UL}, m_next_id {0UL} {
        m_objects.reserve(cm_normal_obj_capacity);
        m_objects.resize(cm_normal_obj_capacity);
    }

    HeapStorage::HeapStorage(std::vector<std::unique_ptr<HeapValueBase>> preloads)
    : m_hole_list {}, m_objects {}, m_dud {}, m_overhead {0UL}, m_next_id {0UL} {
        m_objects.reserve(cm_normal_obj_capacity);
        m_objects.resize(cm_normal_obj_capacity);

        std::size_t preload_n = 0;

        for (auto& preloading_obj : preloads) {
            m_objects[preload_n] = std::move(preloading_obj);
            ++preload_n;
        }

        m_overhead = preload_n * cm_normal_obj_overhead;
        m_next_id = preload_n; 
    }

    auto HeapStorage::is_ripe() const& noexcept -> bool {
        return m_overhead >= cm_normal_gc_threshold;
    }

    [[nodiscard]] auto HeapStorage::try_destroy_value(std::size_t id) noexcept -> bool {
        if (auto& object_cell = m_objects[id]; object_cell) {
            object_cell = {};
            m_overhead -= cm_normal_obj_overhead;
            m_hole_list.emplace(id);

            return true;
        }

        return false;
    }

    auto HeapStorage::get_objects() noexcept -> std::vector<std::unique_ptr<HeapValueBase>>& {
        return m_objects;
    }
}
