#include <mtl/core/tensor.hpp>
#include <mtl/utils/error.hpp>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <numeric>
#include <stdexcept>

namespace mtl::core {

// ─── Pimpl ───────────────────────────────────────────────────────────────────

struct Tensor::Impl {
    std::vector<std::size_t> shape;
    std::vector<std::byte>   data;
    DataType                 dtype{DataType::Float32};

    [[nodiscard]] std::size_t numel() const noexcept {
        if (shape.empty()) {
            return 0;
        }
        return std::accumulate(shape.begin(), shape.end(), std::size_t{1},
                               std::multiplies<std::size_t>{});
    }

    [[nodiscard]] std::size_t nbytes() const noexcept {
        return numel() * dtype_size(dtype);
    }
};

// ─── Constructors ─────────────────────────────────────────────────────────────

Tensor::Tensor() : impl_(new Impl{}) {}

Tensor::Tensor(std::vector<std::size_t> shape, DataType dtype)
    : impl_(new Impl{std::move(shape), {}, dtype}) {
    impl_->data.resize(impl_->nbytes());
}

Tensor::~Tensor() {
    delete impl_;
}

Tensor::Tensor(Tensor&& other) noexcept : impl_(other.impl_) {
    other.impl_ = nullptr;
}

Tensor& Tensor::operator=(Tensor&& other) noexcept {
    if (this != &other) {
        delete impl_;
        impl_       = other.impl_;
        other.impl_ = nullptr;
    }
    return *this;
}

// ─── Accessors ────────────────────────────────────────────────────────────────

const std::vector<std::size_t>& Tensor::shape() const noexcept {
    return impl_->shape;
}

std::size_t Tensor::ndim() const noexcept {
    return impl_->shape.size();
}

std::size_t Tensor::numel() const noexcept {
    return impl_->numel();
}

std::size_t Tensor::nbytes() const noexcept {
    return impl_->nbytes();
}

DataType Tensor::dtype() const noexcept {
    return impl_->dtype;
}

std::span<std::byte> Tensor::data() {
    return {impl_->data.data(), impl_->data.size()};
}

std::span<const std::byte> Tensor::data() const {
    return {impl_->data.data(), impl_->data.size()};
}

template <typename T>
std::span<T> Tensor::data_as() {
    return {reinterpret_cast<T*>(impl_->data.data()), impl_->numel()};
}

template <typename T>
std::span<const T> Tensor::data_as() const {
    return {reinterpret_cast<const T*>(impl_->data.data()), impl_->numel()};
}

// Explicit instantiations for common types
template std::span<float>             Tensor::data_as<float>();
template std::span<const float>       Tensor::data_as<float>() const;
template std::span<std::int32_t>      Tensor::data_as<std::int32_t>();
template std::span<const std::int32_t> Tensor::data_as<std::int32_t>() const;

// ─── Fill helpers ─────────────────────────────────────────────────────────────

void Tensor::fill_zeros() {
    std::fill(impl_->data.begin(), impl_->data.end(), std::byte{0});
}

void Tensor::fill_ones() {
    // TODO: support non-float dtypes
    if (impl_->dtype == DataType::Float32) {
        auto span = data_as<float>();
        std::fill(span.begin(), span.end(), 1.0f);
    } else {
        throw utils::NotImplemented("Tensor::fill_ones for non-float32 dtype");
    }
}

void Tensor::fill_random([[maybe_unused]] float lo, [[maybe_unused]] float hi) {
    // TODO: implement seeded PRNG
    throw utils::NotImplemented("Tensor::fill_random");
}

bool Tensor::is_contiguous() const noexcept {
    // Trivially contiguous for now (no strided views yet)
    return true;
}

} // namespace mtl::core
