# Architecture

`metal-transformer-lab` is organised into five layers, each building on the one below.

```
┌──────────────────────────────────────────────────┐
│              Apps / Executables                   │
│   playground · infer · train · benchmarks        │
├──────────────────────────────────────────────────┤
│            Runtime Execution Engine               │
│      Engine · Graph · Profiler                   │
├──────────────────────────────────────────────────┤
│           Neural Network Blocks (nn/)            │
│   Linear · MultiHeadAttention · MLP              │
│   TransformerBlock · Model                       │
├──────────────────────────────────────────────────┤
│           Kernel Ops Layer (ops/)                │
│   matmul · softmax · layernorm · rope            │
│   activation                                     │
├──────────────────────────────────────────────────┤
│           GPU Abstraction (gpu/)                 │
│   MetalContext · CommandQueue · Pipeline         │
│   Buffer                                         │
├──────────────────────────────────────────────────┤
│            Core Tensor API (core/)               │
│   Tensor · Device · Allocator · DataType         │
└──────────────────────────────────────────────────┘
```

---

## Layer 1 — Core Tensor API (`include/mtl/core/`)

The foundation of everything.

| Component | Responsibility |
|-----------|---------------|
| `types.hpp` | `DataType` enum, `dtype_size()`, `dtype_name()` |
| `tensor.hpp` | Multi-dimensional tensor. RAII-owned data buffer, shape/stride, typed accessors. |
| `allocator.hpp` | Abstract `Allocator` interface. `HostAllocator` (heap). Future: `MetalAllocator` (MTLHeap). |
| `device.hpp` | Thin RAII wrapper around `MTLDevice`. Queries device name, capability flags. |

**Design principles:**
- Tensors are move-only (no accidental copies)
- Raw data bytes are always owned; Metal buffers are created lazily
- `data_as<T>()` provides typed `std::span` access

---

## Layer 2 — GPU Abstraction (`include/mtl/gpu/`)

Wraps the Metal API surface needed for compute dispatch.

| Component | Responsibility |
|-----------|---------------|
| `metal_context.hpp` | Owns the `MTLDevice`. Factory for `CommandQueue` and `Pipeline`. |
| `command_queue.hpp` | `MTLCommandQueue` wrapper. Issues `CommandBuffer`s. |
| `pipeline.hpp` | `MTLComputePipelineState` wrapper. Holds a compiled kernel function. |
| `buffer.hpp` | `MTLBuffer` wrapper. Storage mode (Shared / Private / Managed). |

**Apple Silicon advantage:** `StorageMode::Shared` buffers share a single physical backing store between CPU and GPU — zero-copy data exchange.

---

## Layer 3 — Kernel Ops (`include/mtl/ops/`)

Pure-function dispatch layer. Each op:
1. Validates input shapes
2. Allocates output if needed
3. Dispatches to the corresponding Metal kernel or CPU fallback

| Op | Kernel file | Algorithm |
|----|-------------|-----------|
| `matmul` | `shaders/matmul.metal` | Tiled GEMM |
| `softmax` | `shaders/softmax.metal` | Online numerically-stable softmax |
| `layernorm` | `shaders/layernorm.metal` | Fused LayerNorm / RMSNorm |
| `rope` | `shaders/rope.metal` | In-place Rotary PE |
| `activation` | (inline) | GELU, SiLU, ReLU |

---

## Layer 4 — Neural Network Blocks (`include/mtl/nn/`)

Stateful modules composed from Layer 3 ops and Layer 1 tensors.

| Module | Description |
|--------|-------------|
| `Linear` | Fully-connected layer. Weight tensor + optional bias. |
| `MultiHeadAttention` | Scaled dot-product MHA. Configurable causal mask, RoPE, dropout. |
| `MLP` | Feed-forward block. Supports standard (GELU/ReLU) and gated (SwiGLU) variants. |
| `TransformerBlock` | Pre-norm residual block: Norm→Attn + Norm→MLP. |
| `Model` | Abstract base class. All models expose `forward(input_ids)`. |

---

## Layer 5 — Runtime Execution Engine (`include/mtl/runtime/`)

Orchestrates GPU work.

| Component | Description |
|-----------|-------------|
| `Engine` | Owns `MetalContext`. Schedules async GPU dispatch. Manages memory pools. |
| `Graph` | DAG of compute nodes. Topological sort and kernel fusion (future). |
| `Profiler` | CPU wall-clock + Metal GPU timestamp recording. JSON trace export (future). |

---

## Memory Model

```
CPU RAM ←─────────────────── unified memory ──────────────────→ GPU RAM
         MTLStorageModeShared buffers (zero-copy on Apple Silicon)
         MTLStorageModePrivate buffers (GPU-only, blit copy required)
```

On M-series chips, CPU and GPU share the same DRAM. Metal buffers created as `Shared` need no explicit synchronisation beyond memory barriers encoded in the command buffer.

---

## Threading Model

- One `Engine` owns one `CommandQueue`.
- CPU threads submit work via `CommandBuffer` objects.
- GPU work is asynchronous; `synchronise()` or completion callbacks are used to fence.
- The `Profiler` is thread-safe for concurrent recording.
