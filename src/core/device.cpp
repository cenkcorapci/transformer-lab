#include <mtl/core/device.hpp>
#include <mtl/utils/error.hpp>
#include <mtl/utils/logging.hpp>

namespace mtl::core {

struct Device::Impl {
    std::string name{"[stub device]"};
    bool        valid{false};
};

Device::Device() : impl_(new Impl{}) {
    // TODO: call MTLCreateSystemDefaultDevice() on Apple platforms.
    // For now, mark the device as a stub so non-Metal builds compile.
#if defined(MTL_ENABLE_METAL)
    // impl_->native = MTLCreateSystemDefaultDevice();
    // impl_->valid  = (impl_->native != nullptr);
    // impl_->name   = [impl_->native.name UTF8String];
    impl_->valid = false; // will be set when Metal is wired up
    impl_->name  = "Metal GPU (stub)";
#else
    impl_->valid = false;
    impl_->name  = "No Metal (non-Apple build)";
#endif
    auto& log = utils::get_logger("core");
    log.debug("Device created: {}", impl_->name);
}

Device::~Device() {
    delete impl_;
}

Device::Device(Device&& other) noexcept : impl_(other.impl_) {
    other.impl_ = nullptr;
}

Device& Device::operator=(Device&& other) noexcept {
    if (this != &other) {
        delete impl_;
        impl_       = other.impl_;
        other.impl_ = nullptr;
    }
    return *this;
}

bool Device::is_valid() const noexcept {
    return impl_ && impl_->valid;
}

std::string_view Device::name() const noexcept {
    return impl_ ? std::string_view(impl_->name) : "<null>";
}

std::size_t Device::max_threads_per_threadgroup() const noexcept {
    // TODO: query from MTLDevice
    return 1024;
}

bool Device::supports_bfloat16() const noexcept {
    // TODO: query from MTLDevice GPU family (Apple7+ / M3+)
    return false;
}

void* Device::native_handle() noexcept {
    // TODO: return MTLDevice* cast to void*
    return nullptr;
}

const void* Device::native_handle() const noexcept {
    return nullptr;
}

} // namespace mtl::core
