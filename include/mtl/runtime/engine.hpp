#pragma once

#include <mtl/core/tensor.hpp>
#include <mtl/gpu/metal_context.hpp>

#include <memory>
#include <string_view>

namespace mtl::runtime {

/// The inference/training execution engine.
///
/// Responsibilities:
///   1. Own the MetalContext and GPU resources.
///   2. Schedule operation dispatch to the GPU.
///   3. Manage memory pools and tensor lifetimes.
///   4. Integrate with the profiler.
///
/// TODO: implement async dispatch pipeline.
/// TODO: add batch scheduling and priority queues.
class Engine {
public:
    struct Options {
        bool   enable_profiling{false};
        bool   use_fp16{false};
        bool   use_bf16{false};  ///< requires M3+
        std::size_t max_batch_size{1};
    };

    explicit Engine(Options opts = {});
    ~Engine();

    Engine(const Engine&)            = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) noexcept;
    Engine& operator=(Engine&&) noexcept;

    [[nodiscard]] bool is_ready() const noexcept;

    [[nodiscard]] gpu::MetalContext&       metal_context() noexcept;
    [[nodiscard]] const gpu::MetalContext& metal_context() const noexcept;

    /// Synchronise all in-flight GPU work.
    void synchronise();

    [[nodiscard]] const Options& options() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace mtl::runtime
