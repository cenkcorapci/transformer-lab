#pragma once

#include <mtl/core/tensor.hpp>

namespace mtl::ops {

/// Applies the GELU (Gaussian Error Linear Unit) activation element-wise.
///
/// Approximation: GELU(x) ≈ 0.5 * x * (1 + tanh(√(2/π) * (x + 0.044715*x³)))
///
/// TODO: implement fused GELU Metal kernel.
void gelu(const core::Tensor& input, core::Tensor& output);
void gelu_inplace(core::Tensor& tensor);

/// SiLU / Swish: f(x) = x * sigmoid(x)
void silu(const core::Tensor& input, core::Tensor& output);
void silu_inplace(core::Tensor& tensor);

/// ReLU: f(x) = max(0, x)
void relu(const core::Tensor& input, core::Tensor& output);
void relu_inplace(core::Tensor& tensor);

} // namespace mtl::ops
