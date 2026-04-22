#pragma once

#include <cstddef>
#include <memory>

namespace mtl::gpu {

class CommandQueue;

/// Represents a single recorded GPU command buffer.
///
/// TODO: wrap MTLCommandBuffer lifecycle (encode → commit → wait).
class CommandBuffer {
public:
    ~CommandBuffer();

    CommandBuffer(const CommandBuffer&)            = delete;
    CommandBuffer& operator=(const CommandBuffer&) = delete;
    CommandBuffer(CommandBuffer&&) noexcept;
    CommandBuffer& operator=(CommandBuffer&&) noexcept;

    /// Commit the buffer to the GPU and return immediately.
    void commit();

    /// Commit and block the calling thread until GPU work finishes.
    void commit_and_wait();

    [[nodiscard]] bool is_completed() const noexcept;

    [[nodiscard]] void* native_handle() noexcept;

private:
    friend class CommandQueue;
    explicit CommandBuffer(void* native);

    struct Impl;
    std::unique_ptr<Impl> impl_;
};

/// Owns a Metal command queue (MTLCommandQueue) and issues CommandBuffers.
///
/// TODO: implement MTLCommandQueue creation backed by MetalContext.
class CommandQueue {
public:
    ~CommandQueue();

    CommandQueue(const CommandQueue&)            = delete;
    CommandQueue& operator=(const CommandQueue&) = delete;
    CommandQueue(CommandQueue&&) noexcept;
    CommandQueue& operator=(CommandQueue&&) noexcept;

    /// Creates a new command buffer from this queue.
    [[nodiscard]] std::unique_ptr<CommandBuffer> make_command_buffer();

    [[nodiscard]] void* native_handle() noexcept;

private:
    friend class MetalContext;
    explicit CommandQueue(void* native_device);

    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace mtl::gpu
