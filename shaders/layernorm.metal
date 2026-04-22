// layernorm.metal
// Fused LayerNorm / RMSNorm kernel (stub).

#include <metal_stdlib>
using namespace metal;

struct LayerNormParams {
    uint   rows;
    uint   cols;       ///< normalisation axis length
    float  eps;
    bool   rms_only;   ///< if true, skip mean subtraction (RMSNorm)
};

// TODO: implement two-pass LayerNorm:
//   pass 1: compute mean and variance per row (threadgroup reduce)
//   pass 2: normalise, scale, shift

kernel void layernorm_fp32(
    device const float*       input   [[buffer(0)]],
    device const float*       weight  [[buffer(1)]],
    device const float*       bias    [[buffer(2)]],
    device       float*       output  [[buffer(3)]],
    constant LayerNormParams& params  [[buffer(4)]],
    uint row [[thread_position_in_grid]])
{
    // Stub — no computation yet.
    (void)input; (void)weight; (void)bias; (void)output; (void)params; (void)row;
}
