#pragma once

#include <mtl/core/tensor.hpp>

namespace mtl::ops {

/// Root Mean Square Layer Normalization.
///
/// y = (x / rms(x)) * weight + bias
///
/// where rms(x) = sqrt( mean(x^2) + eps )
///
/// TODO: implement fused RMSNorm Metal kernel (shaders/layernorm.metal).
/// TODO: support standard LayerNorm with learned mean/variance.
void layernorm(const core::Tensor& input,
               const core::Tensor& weight,
               const core::Tensor& bias,
               core::Tensor&       output,
               float               eps = 1e-5f);

/// RMSNorm variant (no bias, no mean subtraction) as used in LLaMA.
void rmsnorm(const core::Tensor& input,
             const core::Tensor& weight,
             core::Tensor&       output,
             float               eps = 1e-6f);

} // namespace mtl::ops
