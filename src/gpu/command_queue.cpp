#include <mtl/gpu/command_queue.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::gpu {

// ─── CommandBuffer ────────────────────────────────────────────────────────────

struct CommandBuffer::Impl {
    void* native{nullptr};
    bool  completed{false};
};

CommandBuffer::CommandBuffer(void* native) : impl_(std::make_unique<Impl>()) {
    impl_->native = native;
}

CommandBuffer::~CommandBuffer() = default;

CommandBuffer::CommandBuffer(CommandBuffer&&) noexcept = default;
CommandBuffer& CommandBuffer::operator=(CommandBuffer&&) noexcept = default;

void CommandBuffer::commit() {
    // TODO: call [mtlCommandBuffer commit]
    throw mtl::utils::NotImplemented("CommandBuffer::commit");
}

void CommandBuffer::commit_and_wait() {
    // TODO: call [mtlCommandBuffer commit] then [mtlCommandBuffer waitUntilCompleted]
    throw mtl::utils::NotImplemented("CommandBuffer::commit_and_wait");
}

bool CommandBuffer::is_completed() const noexcept {
    return impl_ && impl_->completed;
}

void* CommandBuffer::native_handle() noexcept {
    return impl_ ? impl_->native : nullptr;
}

// ─── CommandQueue ─────────────────────────────────────────────────────────────

struct CommandQueue::Impl {
    void* native{nullptr};
};

CommandQueue::CommandQueue(void* native_device) : impl_(std::make_unique<Impl>()) {
    // TODO: create MTLCommandQueue from native_device
    impl_->native = native_device;
}

CommandQueue::~CommandQueue() = default;

CommandQueue::CommandQueue(CommandQueue&&) noexcept = default;
CommandQueue& CommandQueue::operator=(CommandQueue&&) noexcept = default;

std::unique_ptr<CommandBuffer> CommandQueue::make_command_buffer() {
    // TODO: call [mtlCommandQueue commandBuffer]
    return std::unique_ptr<CommandBuffer>(new CommandBuffer(nullptr));
}

void* CommandQueue::native_handle() noexcept {
    return impl_ ? impl_->native : nullptr;
}

} // namespace mtl::gpu
