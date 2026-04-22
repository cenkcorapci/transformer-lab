#pragma once

#include <mtl/core/types.hpp>

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace mtl::core {

/// Strongly-typed multi-dimensional tensor.
///
/// Lifetime is managed by the owning Allocator; raw data lives either in
/// CPU-visible memory or a Metal buffer, depending on the storage mode.
///
/// TODO: implement storage backend selection (CPU / Metal shared / Metal private)
/// TODO: implement shape/stride utilities
/// TODO: implement view() / reshape() / slice()
class Tensor {
public:
    Tensor();
    explicit Tensor(std::vector<std::size_t> shape, DataType dtype = DataType::Float32);
    ~Tensor();

    // Non-copyable, movable
    Tensor(const Tensor&)            = delete;
    Tensor& operator=(const Tensor&) = delete;
    Tensor(Tensor&&) noexcept;
    Tensor& operator=(Tensor&&) noexcept;

    // ── Accessors ────────────────────────────────────────────────────────────

    [[nodiscard]] const std::vector<std::size_t>& shape() const noexcept;
    [[nodiscard]] std::size_t                     ndim() const noexcept;
    [[nodiscard]] std::size_t                     numel() const noexcept;
    [[nodiscard]] std::size_t                     nbytes() const noexcept;
    [[nodiscard]] DataType                        dtype() const noexcept;

    /// Returns a raw byte span over the data buffer (CPU-accessible only).
    [[nodiscard]] std::span<std::byte>       data();
    [[nodiscard]] std::span<const std::byte> data() const;

    /// Typed convenience accessor — UB if T does not match dtype.
    template <typename T>
    [[nodiscard]] std::span<T> data_as();

    template <typename T>
    [[nodiscard]] std::span<const T> data_as() const;

    // ── Utilities ────────────────────────────────────────────────────────────

    void fill_zeros();
    void fill_ones();

    /// Fill with values drawn from a uniform distribution U(lo, hi).
    /// TODO: implement PRNG seeding
    void fill_random(float lo = -1.0f, float hi = 1.0f);

    [[nodiscard]] bool is_contiguous() const noexcept;

private:
    struct Impl;
    Impl* impl_{nullptr};
};

} // namespace mtl::core
