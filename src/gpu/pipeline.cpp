#include <mtl/gpu/pipeline.hpp>

#include <utility>

namespace mtl::gpu {

struct Pipeline::Impl {
    void*       native{nullptr};
    std::string function_name;
};

Pipeline::Pipeline(void* native_pipeline, std::string_view fn_name)
    : impl_(std::make_unique<Impl>()) {
    impl_->native        = native_pipeline;
    impl_->function_name = std::string(fn_name);
}

Pipeline::~Pipeline() = default;

Pipeline::Pipeline(Pipeline&&) noexcept = default;
Pipeline& Pipeline::operator=(Pipeline&&) noexcept = default;

bool Pipeline::is_valid() const noexcept {
    return impl_ && impl_->native != nullptr;
}

std::string_view Pipeline::function_name() const noexcept {
    return impl_ ? std::string_view(impl_->function_name) : "";
}

std::size_t Pipeline::max_total_threads_per_threadgroup() const noexcept {
    // TODO: query from MTLComputePipelineState
    return 1024;
}

std::size_t Pipeline::thread_execution_width() const noexcept {
    // TODO: query from MTLComputePipelineState
    return 32;
}

void* Pipeline::native_handle() noexcept {
    return impl_ ? impl_->native : nullptr;
}

} // namespace mtl::gpu
