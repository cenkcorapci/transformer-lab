// softmax.metal
// Numerically stable softmax kernel (stub).

#include <metal_stdlib>
using namespace metal;

struct SoftmaxParams {
    uint rows;
    uint cols; ///< reduction axis length
};

// TODO: implement online softmax in a single pass using threadgroup reductions.
// Algorithm: for each row, compute (max, sum) in one pass, then normalise.

kernel void softmax_fp32(
    device const float*   input  [[buffer(0)]],
    device       float*   output [[buffer(1)]],
    constant SoftmaxParams& params [[buffer(2)]],
    uint row [[thread_position_in_grid]])
{
    // Stub — no computation yet.
    (void)input; (void)output; (void)params; (void)row;
}
