#pragma once

#include <mtl/core/tensor.hpp>

namespace mtl::ops {

/// Matrix multiplication: C = alpha * A @ B + beta * C
///
/// Shapes:
///   A : [M, K]
///   B : [K, N]
///   C : [M, N]  (output, may be pre-allocated or null for new allocation)
///
/// TODO: implement tiled GEMM Metal kernel (shaders/matmul.metal).
/// TODO: add support for transposed inputs (A^T, B^T).
/// TODO: add batched GEMM for [batch, M, K] x [batch, K, N].
void matmul(const core::Tensor& A,
            const core::Tensor& B,
            core::Tensor&       C,
            float               alpha = 1.0f,
            float               beta  = 0.0f);

/// In-place version that allocates C if necessary.
[[nodiscard]] core::Tensor matmul(const core::Tensor& A, const core::Tensor& B);

} // namespace mtl::ops
