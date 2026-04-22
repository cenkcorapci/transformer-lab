#pragma once

#include <cstddef>
#include <memory>

namespace mtl::gpu {

/// Storage mode mirrors MTLStorageMode options.
enum class StorageMode : std::uint8_t {
    /// CPU and GPU share the same physical memory (recommended for Apple Silicon).
    Shared,
    /// GPU-private; CPU cannot access directly (highest GPU bandwidth).
    Private,
    /// CPU-only managed (fallback for older Intel Macs).
    Managed,
};

/// RAII wrapper around a MTLBuffer.
///
/// On Apple Silicon with StorageMode::Shared the buffer backing store is
/// directly addressable from both CPU and GPU — no explicit copy is needed.
///
/// TODO: implement MTLBuffer allocation via MetalContext::device().
/// TODO: add blit-copy helpers for Private buffers.
class Buffer {
public:
    Buffer();
    Buffer(std::size_t size_bytes, StorageMode mode = StorageMode::Shared);
    ~Buffer();

    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) noexcept;
    Buffer& operator=(Buffer&&) noexcept;

    [[nodiscard]] bool        is_valid() const noexcept;
    [[nodiscard]] std::size_t size_bytes() const noexcept;
    [[nodiscard]] StorageMode storage_mode() const noexcept;

    /// Returns a CPU-side pointer (only valid for Shared / Managed buffers).
    [[nodiscard]] void*       contents() noexcept;
    [[nodiscard]] const void* contents() const noexcept;

    /// Returns the underlying MTLBuffer* (opaque).
    [[nodiscard]] void* native_handle() noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace mtl::gpu
