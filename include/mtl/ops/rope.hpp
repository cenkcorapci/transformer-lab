#pragma once

#include <mtl/core/tensor.hpp>

#include <cstddef>

namespace mtl::ops {

/// Rotary Position Embedding (RoPE) as used in LLaMA / GPT-NeoX.
///
/// Applies complex-valued rotation to query and key tensors:
///   q'_i = q_i * cos(theta) - q_{i+1} * sin(theta)   (for even i)
///
/// TODO: implement RoPE Metal kernel (shaders/rope.metal).
/// TODO: support long-context scaling (YaRN, NTK-aware RoPE).
///
/// @param q    Query tensor  [batch, seq, n_heads, head_dim]
/// @param k    Key tensor    [batch, seq, n_heads, head_dim]
/// @param pos  Position ids  [batch, seq]
/// @param base Rotary base (default 10 000 for vanilla RoPE)
void rope(core::Tensor&       q,
          core::Tensor&       k,
          const core::Tensor& pos,
          float               base = 10000.0f);

} // namespace mtl::ops
