// matmul.metal
// Tiled matrix multiplication kernel (stub — no compute logic yet).

#include <metal_stdlib>
using namespace metal;

/// Parameters block passed from the CPU.
struct MatmulParams {
    uint M;      ///< rows of A / C
    uint N;      ///< cols of B / C
    uint K;      ///< inner dimension
    float alpha; ///< scale for A @ B
    float beta;  ///< scale for C (accumulate)
};

// TODO: implement tiled GEMM with shared threadgroup memory.
// Reference tile sizes: 32×32 or 64×64 depending on M3 threadgroup limits.

kernel void matmul_fp32(
    device const float* A        [[buffer(0)]],
    device const float* B        [[buffer(1)]],
    device       float* C        [[buffer(2)]],
    constant MatmulParams& params [[buffer(3)]],
    uint2 thread_position_in_grid [[thread_position_in_grid]])
{
    // Stub — no computation yet.
    (void)A; (void)B; (void)C; (void)params; (void)thread_position_in_grid;
}
