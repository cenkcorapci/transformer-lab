#pragma once

#include <mtl/core/device.hpp>

#include <memory>

namespace mtl::gpu {

class CommandQueue;
class Pipeline;

/// Owns the Metal device and acts as the entry point for all GPU operations.
///
/// Typical usage:
/// @code
///   auto ctx = mtl::gpu::MetalContext::create();
///   auto queue = ctx->make_command_queue();
/// @endcode
///
/// TODO: implement MTLDevice initialisation on Apple platforms.
/// TODO: add device capability query helpers.
class MetalContext {
public:
    ~MetalContext();

    MetalContext(const MetalContext&)            = delete;
    MetalContext& operator=(const MetalContext&) = delete;
    MetalContext(MetalContext&&) noexcept;
    MetalContext& operator=(MetalContext&&) noexcept;

    /// Creates a MetalContext backed by the system default GPU.
    [[nodiscard]] static std::unique_ptr<MetalContext> create();

    [[nodiscard]] bool is_valid() const noexcept;

    [[nodiscard]] mtl::core::Device&       device() noexcept;
    [[nodiscard]] const mtl::core::Device& device() const noexcept;

    /// Creates a new CommandQueue on this device.
    [[nodiscard]] std::unique_ptr<CommandQueue> make_command_queue();

    /// Creates a compute pipeline from a named kernel function in the default
    /// .metallib library compiled from shaders/.
    /// TODO: implement pipeline cache to avoid redundant compilation.
    [[nodiscard]] std::unique_ptr<Pipeline> make_pipeline(const char* function_name);

private:
    MetalContext();

    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace mtl::gpu
