#pragma once

#include <mtl/core/tensor.hpp>

namespace mtl::ops {

/// Numerically stable softmax along a given axis.
///
/// Algorithm:
///   y_i = exp(x_i - max(x)) / sum_j exp(x_j - max(x))
///
/// TODO: implement online softmax with a single pass (shaders/softmax.metal).
/// TODO: add temperature scaling parameter.
void softmax(const core::Tensor& input, core::Tensor& output, int axis = -1);

/// In-place softmax (output == input is valid).
void softmax_inplace(core::Tensor& tensor, int axis = -1);

/// Numerically stable log-softmax.
void log_softmax(const core::Tensor& input, core::Tensor& output, int axis = -1);

} // namespace mtl::ops
