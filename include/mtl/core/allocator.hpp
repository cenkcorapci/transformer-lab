#pragma once

#include <mtl/core/types.hpp>
#include <mtl/utils/error.hpp>

#include <cstddef>
#include <memory>
#include <string_view>

namespace mtl::core {

class Tensor;

/// Allocation strategy tag used when requesting memory.
enum class MemoryKind : std::uint8_t {
    /// Ordinary heap allocation — CPU only.
    Host,
    /// Metal buffer with MTLStorageModeShared — accessible by CPU and GPU.
    MetalShared,
    /// Metal buffer with MTLStorageModePrivate — GPU-only, highest bandwidth.
    MetalPrivate,
};

/// Abstract allocator interface.
///
/// Concrete implementations are provided for:
///   - HostAllocator (malloc/free)
///   - MetalAllocator (MTLBuffer)
///
/// TODO: implement MetalAllocator backed by a MTLHeap for arena-style allocation.
class Allocator {
public:
    virtual ~Allocator() = default;

    /// Allocate `size` bytes.  Returns nullptr on failure.
    [[nodiscard]] virtual void* allocate(std::size_t size) = 0;

    /// Deallocate a previously allocated block.
    virtual void deallocate(void* ptr) noexcept = 0;

    [[nodiscard]] virtual MemoryKind kind() const noexcept = 0;
    [[nodiscard]] virtual std::string_view name() const noexcept = 0;
};

/// Simple CPU heap allocator using operator new.
class HostAllocator : public Allocator {
public:
    [[nodiscard]] void* allocate(std::size_t size) override;
    void deallocate(void* ptr) noexcept override;
    [[nodiscard]] MemoryKind kind() const noexcept override { return MemoryKind::Host; }
    [[nodiscard]] std::string_view name() const noexcept override { return "HostAllocator"; }
};

/// Returns the process-wide default allocator (HostAllocator unless overridden).
[[nodiscard]] Allocator& default_allocator() noexcept;

} // namespace mtl::core
