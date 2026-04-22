#include <mtl/gpu/buffer.hpp>
#include <mtl/utils/error.hpp>

#include <cstdlib>

namespace mtl::gpu {

struct Buffer::Impl {
    void*       contents{nullptr};
    std::size_t size_bytes{0};
    StorageMode mode{StorageMode::Shared};
    void*       native{nullptr};
};

Buffer::Buffer() : impl_(std::make_unique<Impl>()) {}

Buffer::Buffer(std::size_t size_bytes, StorageMode mode) : impl_(std::make_unique<Impl>()) {
    impl_->size_bytes = size_bytes;
    impl_->mode       = mode;

#if defined(MTL_ENABLE_METAL)
    // TODO: allocate MTLBuffer via the global MetalContext
    // MTLBuffer* buf = [device newBufferWithLength:size_bytes
    //                                     options:MTLResourceStorageModeShared];
    // impl_->native   = (__bridge_retained void*)buf;
    // impl_->contents = [buf contents];
#endif

    // Fallback: plain heap allocation so non-Metal builds work.
    if (!impl_->contents && mode != StorageMode::Private) {
        impl_->contents = std::malloc(size_bytes); // NOLINT
        if (!impl_->contents) {
            impl_->size_bytes = 0; // mark invalid on allocation failure
        }
    }
}

Buffer::~Buffer() {
#if defined(MTL_ENABLE_METAL)
    // TODO: release MTLBuffer reference
#endif
    if (impl_ && impl_->mode != StorageMode::Private && impl_->contents) {
        std::free(impl_->contents); // NOLINT
        impl_->contents = nullptr;
    }
}

Buffer::Buffer(Buffer&&) noexcept = default;
Buffer& Buffer::operator=(Buffer&&) noexcept = default;

bool Buffer::is_valid() const noexcept {
    return impl_ && impl_->size_bytes > 0;
}

std::size_t Buffer::size_bytes() const noexcept {
    return impl_ ? impl_->size_bytes : 0;
}

StorageMode Buffer::storage_mode() const noexcept {
    return impl_ ? impl_->mode : StorageMode::Shared;
}

void* Buffer::contents() noexcept {
    return impl_ ? impl_->contents : nullptr;
}

const void* Buffer::contents() const noexcept {
    return impl_ ? impl_->contents : nullptr;
}

void* Buffer::native_handle() noexcept {
    return impl_ ? impl_->native : nullptr;
}

} // namespace mtl::gpu
