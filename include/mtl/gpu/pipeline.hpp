#pragma once

#include <cstddef>
#include <memory>
#include <string_view>

namespace mtl::gpu {

/// Wraps a MTLComputePipelineState compiled from a Metal kernel function.
///
/// TODO: implement pipeline creation from MTLLibrary.
/// TODO: add threadgroup size recommendation based on pipeline threadExecutionWidth.
class Pipeline {
public:
    ~Pipeline();

    Pipeline(const Pipeline&)            = delete;
    Pipeline& operator=(const Pipeline&) = delete;
    Pipeline(Pipeline&&) noexcept;
    Pipeline& operator=(Pipeline&&) noexcept;

    [[nodiscard]] bool              is_valid() const noexcept;
    [[nodiscard]] std::string_view  function_name() const noexcept;

    /// Recommended threadgroup size for square 2-D dispatch.
    [[nodiscard]] std::size_t max_total_threads_per_threadgroup() const noexcept;
    [[nodiscard]] std::size_t thread_execution_width() const noexcept;

    [[nodiscard]] void* native_handle() noexcept;

private:
    friend class MetalContext;
    Pipeline(void* native_pipeline, std::string_view fn_name);

    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace mtl::gpu
