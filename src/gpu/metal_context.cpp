#include <mtl/gpu/metal_context.hpp>
#include <mtl/gpu/command_queue.hpp>
#include <mtl/gpu/pipeline.hpp>
#include <mtl/utils/error.hpp>
#include <mtl/utils/logging.hpp>

#include <memory>

namespace mtl::gpu {

struct MetalContext::Impl {
    mtl::core::Device device;
};

MetalContext::MetalContext() : impl_(std::make_unique<Impl>()) {}

MetalContext::~MetalContext() = default;

MetalContext::MetalContext(MetalContext&&) noexcept = default;
MetalContext& MetalContext::operator=(MetalContext&&) noexcept = default;

std::unique_ptr<MetalContext> MetalContext::create() {
    // TODO: check Metal availability before constructing.
    auto ctx = std::unique_ptr<MetalContext>(new MetalContext());
    auto& log = mtl::utils::get_logger("gpu");
    log.info("MetalContext created (stub). Device: {}", ctx->device().name());
    return ctx;
}

bool MetalContext::is_valid() const noexcept {
    return impl_ && impl_->device.is_valid();
}

mtl::core::Device& MetalContext::device() noexcept {
    return impl_->device;
}

const mtl::core::Device& MetalContext::device() const noexcept {
    return impl_->device;
}

std::unique_ptr<CommandQueue> MetalContext::make_command_queue() {
    // TODO: create MTLCommandQueue from impl_->device.native_handle()
    return std::unique_ptr<CommandQueue>(new CommandQueue(impl_->device.native_handle()));
}

std::unique_ptr<Pipeline> MetalContext::make_pipeline([[maybe_unused]] const char* function_name) {
    // TODO: look up function in loaded MTLLibrary and compile pipeline
    throw mtl::utils::NotImplemented("MetalContext::make_pipeline");
}

} // namespace mtl::gpu
