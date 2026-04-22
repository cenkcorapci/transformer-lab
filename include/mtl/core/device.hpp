#pragma once

#include <string_view>

namespace mtl::core {

/// Thin RAII wrapper around the Metal device (MTLDevice*).
///
/// On Apple platforms this wraps the system-default GPU device obtained via
/// MTLCreateSystemDefaultDevice().  On non-Metal builds it is a no-op stub.
///
/// TODO: support device enumeration for future multi-GPU Macs.
/// TODO: expose device capability flags (BF16 support, ray-tracing, etc.)
class Device {
public:
    /// Creates and owns the default system Metal device.
    Device();
    ~Device();

    // Non-copyable, movable
    Device(const Device&)            = delete;
    Device& operator=(const Device&) = delete;
    Device(Device&&) noexcept;
    Device& operator=(Device&&) noexcept;

    [[nodiscard]] bool        is_valid() const noexcept;
    [[nodiscard]] std::string_view name() const noexcept;

    /// Returns maximum number of threads per threadgroup for compute kernels.
    [[nodiscard]] std::size_t max_threads_per_threadgroup() const noexcept;

    /// Returns true when the device supports BF16 (Metal 3 / M3+).
    [[nodiscard]] bool supports_bfloat16() const noexcept;

    /// Returns the underlying MTLDevice* (opaque on non-Apple builds).
    [[nodiscard]] void* native_handle() noexcept;
    [[nodiscard]] const void* native_handle() const noexcept;

private:
    struct Impl;
    Impl* impl_{nullptr};
};

} // namespace mtl::core
