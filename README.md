# metal-transformer-lab

> A modern C++20 + Apple Metal transformer systems playground for implementing seminal transformer papers from scratch — built for Apple Silicon.

[![CI macOS](https://github.com/cenkcorapci/transformer-lab/actions/workflows/ci-macos.yml/badge.svg)](https://github.com/cenkcorapci/transformer-lab/actions/workflows/ci-macos.yml)
[![Format Check](https://github.com/cenkcorapci/transformer-lab/actions/workflows/format.yml/badge.svg)](https://github.com/cenkcorapci/transformer-lab/actions/workflows/format.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

## Vision

`metal-transformer-lab` is a personal systems-engineering playground focused on:

- **GPU programming with Apple Metal** (Metal Shading Language)
- **Modern C++20** patterns, RAII, concepts, and ranges
- **Transformer systems engineering** from first principles

The goal is to grow this repository from simple GPU kernel experiments into a serious inference and training engine for transformer models — natively on Apple Silicon M-series chips.

No Python required in the core runtime. Python scripts are allowed in `scripts/` for tooling only.

---

## Why Metal for Transformers on Apple Silicon?

Apple Silicon (M1/M2/M3/M4) features a **unified memory architecture** where CPU and GPU share the same physical RAM. This eliminates expensive PCIe copy overhead that plagues discrete GPU setups:

- **Zero-copy buffers**: Metal buffers created with `MTLStorageModeShared` are directly accessible from both CPU and GPU threads
- **High memory bandwidth**: M3 Max delivers up to 400 GB/s of unified memory bandwidth
- **Neural Engine + GPU**: Hybrid offloading is possible
- **Metal Performance Shaders (MPS)**: Apple-optimised BLAS/LAPACK-level primitives available as fallback
- **Xcode Instruments**: World-class GPU profiling tooling built-in

This makes Apple Silicon an excellent research platform for exploring transformer systems at the kernel level.

---

## Papers Roadmap

| # | Paper | Status |
|---|-------|--------|
| 1 | [Attention Is All You Need](https://arxiv.org/abs/1706.03762) (Vaswani et al., 2017) | 🔲 Planned |
| 2 | [BERT](https://arxiv.org/abs/1810.04805) (Devlin et al., 2018) | 🔲 Planned |
| 3 | [FlashAttention](https://arxiv.org/abs/2205.14135) — tiled attention kernels | 🔲 Planned |
| 4 | [LLaMA](https://arxiv.org/abs/2302.13971) (Touvron et al., 2023) | 🔲 Planned |
| 5 | [Megatron-LM](https://arxiv.org/abs/1909.08053) — tensor/pipeline parallelism | 🔲 Planned |

See [`docs/roadmap.md`](docs/roadmap.md) for detailed milestone breakdowns.

---

## Repository Structure

```
metal-transformer-lab/
├── CMakeLists.txt          # Top-level build
├── cmake/                  # CMake modules
├── docs/                   # Architecture, roadmap, profiling docs
├── include/mtl/            # Public C++ headers
│   ├── core/               # Tensor, device, allocator, types
│   ├── gpu/                # Metal context, command queue, pipeline, buffers
│   ├── ops/                # Kernel-level ops (matmul, softmax, layernorm, …)
│   ├── nn/                 # Neural network blocks
│   ├── runtime/            # Execution engine, compute graph, profiler
│   └── utils/              # Logging, timer, error handling
├── src/                    # Implementation files
├── shaders/                # Metal Shading Language (.metal) kernels
├── apps/                   # Executable entry points
├── tests/                  # GoogleTest unit tests
├── benchmarks/             # Google Benchmark microbenchmarks
└── scripts/                # Build/lint/profile helper scripts
```

---

## Build Instructions

### Prerequisites

- macOS 13+ (Ventura) on Apple Silicon or Intel Mac with Metal support
- Xcode 15+ (for Metal toolchain)
- CMake 3.26+
- Ninja (recommended): `brew install ninja`

### Configure & Build

```bash
cmake -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DMTL_ENABLE_TESTS=ON \
    -DMTL_ENABLE_BENCHMARKS=ON

cmake --build build --parallel
```

### Run Tests

```bash
cd build && ctest --output-on-failure
```

### Run Benchmarks

```bash
./build/benchmarks_runner --benchmark_format=console
```

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `MTL_ENABLE_TESTS` | `ON` | Build GoogleTest unit tests |
| `MTL_ENABLE_BENCHMARKS` | `ON` | Build Google Benchmark microbenchmarks |
| `MTL_ENABLE_SANITIZERS` | `OFF` | Enable AddressSanitizer / UBSan |
| `MTL_ENABLE_METAL` | `ON` | Enable Metal GPU backend |

---

## Benchmarking Goals

| Kernel | Target (M3 Max) | Notes |
|--------|----------------|-------|
| GEMM 4096×4096 fp32 | > 8 TFLOPS | Baseline Metal shader |
| Softmax 1M elements | < 1 ms | Numerically stable |
| FlashAttention seqlen=2048 | < 5 ms | Tiled, IO-aware |
| LayerNorm 768-dim, 512 batch | < 0.5 ms | Fused kernel |

---

## Profiling Tools

### Xcode Instruments
```bash
xcrun xctrace record --template "Metal System Trace" \
    --launch ./build/playground -- --seq-len 512
```

### Metal Frame Debugger
Launch via Xcode → Product → Profile → Metal System Trace

### GPU Counters
Use `MTLCounterSet` API for fine-grained occupancy and bandwidth metrics. See [`docs/profiling.md`](docs/profiling.md) for setup.

---

## Future Plans

- [ ] FP16 (`half`) compute kernels
- [ ] BF16 support (M3+)
- [ ] KV cache with ring buffer
- [ ] Unified memory zero-copy inference
- [ ] INT8 / INT4 quantisation
- [ ] Speculative decoding
- [ ] Multi-GPU (future Mac Pro with multiple dies)
- [ ] Metal Performance Shaders (MPS) fallback path

---

## Contributing

This is a personal learning project. PRs fixing bugs or improving the build system are welcome. Please run `scripts/format.sh` before submitting.

---

## License

MIT — see [LICENSE](LICENSE).
