// flash_attention.metal
// IO-aware tiled attention kernel — FlashAttention style (stub).
//
// Reference: Dao et al. "FlashAttention: Fast and Memory-Efficient Exact
// Attention with IO-Awareness" (2022).

#include <metal_stdlib>
using namespace metal;

struct FlashAttnParams {
    uint   batch;
    uint   n_heads;
    uint   seq_q;
    uint   seq_k;
    uint   head_dim;
    float  scale;      ///< 1 / sqrt(head_dim)
    bool   is_causal;
};

// TODO: implement tiled FlashAttention forward pass.
// Tiling strategy:
//   - Outer loop: tiles of Q rows (block_q rows per threadgroup)
//   - Inner loop: tiles of K/V columns (block_k cols per threadgroup)
//   - Maintain running max (m) and sum (l) for online softmax normalisation
//   - Accumulate output in registers; write once at the end

kernel void flash_attention_fp32(
    device const float*        Q      [[buffer(0)]],
    device const float*        K      [[buffer(1)]],
    device const float*        V      [[buffer(2)]],
    device       float*        O      [[buffer(3)]],
    constant FlashAttnParams&  params [[buffer(4)]],
    uint3 tid [[thread_position_in_grid]])
{
    // Stub — no computation yet.
    (void)Q; (void)K; (void)V; (void)O; (void)params; (void)tid;
}
