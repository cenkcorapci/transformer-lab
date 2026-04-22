#pragma once

#include <mtl/core/tensor.hpp>

#include <cstddef>

namespace mtl::nn {

/// Fully-connected linear layer: y = x @ W^T + b
///
/// Weight shape: [out_features, in_features]
/// Bias shape:   [out_features]  (optional)
///
/// TODO: integrate matmul op and weight management.
class Linear {
public:
    Linear(std::size_t in_features, std::size_t out_features, bool use_bias = true);
    ~Linear();

    Linear(const Linear&)            = delete;
    Linear& operator=(const Linear&) = delete;
    Linear(Linear&&) noexcept;
    Linear& operator=(Linear&&) noexcept;

    /// Forward pass: returns [*, out_features] tensor.
    /// TODO: dispatch to mtl::ops::matmul.
    [[nodiscard]] core::Tensor forward(const core::Tensor& input) const;

    [[nodiscard]] core::Tensor&       weight() noexcept;
    [[nodiscard]] const core::Tensor& weight() const noexcept;
    [[nodiscard]] core::Tensor*       bias() noexcept;
    [[nodiscard]] const core::Tensor* bias() const noexcept;

    [[nodiscard]] std::size_t in_features()  const noexcept;
    [[nodiscard]] std::size_t out_features() const noexcept;

private:
    struct Impl;
    Impl* impl_{nullptr};
};

} // namespace mtl::nn
