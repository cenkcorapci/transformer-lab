// rope.metal
// Rotary Position Embedding kernel (stub).

#include <metal_stdlib>
using namespace metal;

struct RopeParams {
    uint   seq_len;
    uint   n_heads;
    uint   head_dim;
    float  base;   ///< rotary base, default 10000
};

// TODO: implement in-place RoPE.
// For position p and dimension pair (2i, 2i+1):
//   theta   = p / base^(2i / head_dim)
//   q'[2i]   = q[2i] * cos(theta) - q[2i+1] * sin(theta)
//   q'[2i+1] = q[2i] * sin(theta) + q[2i+1] * cos(theta)

kernel void rope_fp32(
    device       float*    q       [[buffer(0)]],
    device       float*    k       [[buffer(1)]],
    device const uint*     pos_ids [[buffer(2)]],
    constant RopeParams&   params  [[buffer(3)]],
    uint3 id [[thread_position_in_grid]])
{
    // Stub — no computation yet.
    (void)q; (void)k; (void)pos_ids; (void)params; (void)id;
}
