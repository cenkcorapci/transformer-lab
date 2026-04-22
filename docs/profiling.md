# Profiling Guide

This document covers the profiling tools available for metal-transformer-lab on macOS / Apple Silicon.

---

## 1. Built-in Profiler (`mtl::runtime::Profiler`)

The project ships a lightweight CPU + GPU timing profiler.

### Enabling

```cpp
mtl::runtime::Engine::Options opts;
opts.enable_profiling = true;

mtl::runtime::Engine engine(opts);
auto& profiler = engine.profiler(); // TODO: expose in Engine
profiler.enable();
```

Or via the CLI:

```bash
./build/playground --profile
```

### Output

```
Kernel                                   CPU (ms)   GPU (ms)   Calls
------------------------------------------------------------------------
matmul_fp32 [4096x4096]                   0.142     12.450      100
softmax_fp32 [4096x1024]                  0.031      0.870      100
layernorm_fp32 [512x768]                  0.012      0.230      100
```

---

## 2. Xcode Instruments — Metal System Trace

The most comprehensive GPU profiling tool for Apple platforms.

### Command-line recording

```bash
./scripts/xcode_profile.sh playground
# or manually:
xcrun xctrace record \
    --template "Metal System Trace" \
    --output /tmp/my_trace.trace \
    --launch ./build/playground
```

### Opening the trace

```bash
open /tmp/my_trace.trace
```

### What to look for

| Track | Metric |
|-------|--------|
| GPU Timeline | Kernel execution time, gaps between kernels |
| GPU Hardware counters | ALU utilisation, memory bandwidth |
| Shader Timeline | Which kernel functions ran and when |
| Metal Resource State | Buffer allocation / deallocation events |

---

## 3. GPU Performance Counters (`MTLCounterSet`)

Use Metal's `MTLCounterSet` API to record fine-grained hardware metrics:

```cpp
// TODO: integrate into Profiler
// Relevant counter sets:
//   MTLCommonCounterSetStatistic
//   MTLCommonCounterSetTimestamp
// Relevant counters:
//   MTLCommonCounterGPUTime
//   MTLCommonCounterTotalCycles
//   MTLCommonCounterVertexCycles
//   MTLCommonCounterFragmentCycles
//   MTLCommonCounterComputeCycles
```

### Key metrics for transformer kernels

| Metric | Why it matters |
|--------|---------------|
| `GPU Occupancy` | Fraction of GPU threads active — low → memory-bound |
| `ALU Utilisation` | Fraction of time ALUs are busy — low → bandwidth or latency bound |
| `L1 Cache Hit Rate` | High = good for tiled kernels |
| `DRAM Bandwidth` | Measured vs peak — for flash attention should be close to roofline |

---

## 4. Metal Frame Debugger (Xcode)

Use for debugging incorrect kernel output (not performance):

1. Run `playground` or `infer` from Xcode (scheme needs Metal validation enabled)
2. Press the **Capture GPU Frame** button in the debugger toolbar
3. Inspect:
   - Bound buffers and their contents
   - Threadgroup/grid dispatch dimensions
   - Shader source alongside assembly

---

## 5. Roofline Analysis

For each kernel, compare achieved throughput to the roofline bound:

```
Arithmetic intensity (FLOP/byte) = total_FLOPs / bytes_transferred

For M3 Max:
  Peak FP32 compute : ~14 TFLOPS
  Peak memory BW    : ~400 GB/s
  Ridge point       : 14e12 / 400e9 ≈ 35 FLOP/byte
```

Kernels with arithmetic intensity < 35 FLOP/byte are memory-bound. FlashAttention's IO-aware tiling is specifically designed to push attention above the ridge point.

---

## 6. Apple Silicon Performance Guides

- [Metal Best Practices Guide](https://developer.apple.com/library/archive/documentation/Miscellaneous/Conceptual/MetalProgrammingGuide/Introduction/Introduction.html)
- [Optimising Metal Performance](https://developer.apple.com/documentation/metal/optimizing_performance_with_the_shader_debugger)
- [Metal Feature Set Tables](https://developer.apple.com/metal/Metal-Feature-Set-Tables.pdf)
