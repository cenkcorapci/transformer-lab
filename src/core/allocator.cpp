#include <mtl/core/allocator.hpp>
#include <mtl/utils/error.hpp>

#include <new>

namespace mtl::core {

// ─── HostAllocator ────────────────────────────────────────────────────────────

void* HostAllocator::allocate(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    return ::operator new(size, std::nothrow);
}

void HostAllocator::deallocate(void* ptr) noexcept {
    ::operator delete(ptr);
}

// ─── default_allocator ────────────────────────────────────────────────────────

Allocator& default_allocator() noexcept {
    static HostAllocator instance;
    return instance;
}

} // namespace mtl::core
