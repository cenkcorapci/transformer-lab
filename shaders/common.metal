// common.metal
// Shared utilities and type aliases used across all Metal kernels.

#include <metal_stdlib>
using namespace metal;

// ─── Numeric constants ────────────────────────────────────────────────────────

constant float kNegInf = -INFINITY;

// ─── Utility functions ────────────────────────────────────────────────────────

/// Safe division that avoids NaN when denominator is zero.
inline float safe_div(float num, float denom) {
    return (denom == 0.0f) ? 0.0f : num / denom;
}

/// Clamp a float to [lo, hi].
inline float fclamp(float x, float lo, float hi) {
    return min(max(x, lo), hi);
}
