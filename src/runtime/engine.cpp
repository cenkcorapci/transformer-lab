#include <mtl/runtime/engine.hpp>
#include <mtl/utils/error.hpp>
#include <mtl/utils/logging.hpp>

namespace mtl::runtime {

struct Engine::Impl {
    Options options;
    std::unique_ptr<gpu::MetalContext> ctx;
};

Engine::Engine(Options opts) : impl_(std::make_unique<Impl>()) {
    impl_->options = std::move(opts);
    impl_->ctx     = gpu::MetalContext::create();
    utils::get_logger("runtime").info("Engine initialised (stub).");
}

Engine::~Engine() = default;

Engine::Engine(Engine&&) noexcept = default;
Engine& Engine::operator=(Engine&&) noexcept = default;

bool Engine::is_ready() const noexcept {
    return impl_ && impl_->ctx != nullptr;
}

gpu::MetalContext& Engine::metal_context() noexcept {
    return *impl_->ctx;
}

const gpu::MetalContext& Engine::metal_context() const noexcept {
    return *impl_->ctx;
}

void Engine::synchronise() {
    // TODO: wait for all in-flight command buffers to complete
}

const Engine::Options& Engine::options() const noexcept {
    return impl_->options;
}

} // namespace mtl::runtime
