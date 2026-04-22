# Roadmap

Development is organised into five phases. Each phase builds on the previous.

---

## Phase 1 — Tensor + Metal Kernels

**Goal:** Get the core GPU infrastructure working end-to-end.

- [ ] `Tensor` class: shape inference, stride computation, view/reshape
- [ ] `HostAllocator`: malloc/free with alignment
- [ ] `MetalAllocator`: MTLBuffer creation with Shared / Private modes
- [ ] `MetalContext`: initialise device, load `.metallib`
- [ ] `CommandQueue` + `CommandBuffer`: encode and commit compute work
- [ ] `matmul_fp32` Metal kernel: tiled GEMM 32×32 threadgroup tile
- [ ] `softmax_fp32` Metal kernel: online numerically-stable, 1-pass per row
- [ ] `layernorm_fp32` Metal kernel: fused mean/variance + scale/shift
- [ ] Unit tests passing for all ops
- [ ] Benchmark suite baseline numbers recorded

---

## Phase 2 — Transformer Forward Pass

**Goal:** Run a forward pass of the original Transformer architecture.

- [ ] `Linear` forward: dispatch to `matmul` + bias add
- [ ] `MultiHeadAttention` forward: Q/K/V projection → split heads → attn → merge
- [ ] Sinusoidal positional encoding
- [ ] `TransformerBlock` forward: pre-norm residual
- [ ] `MLP` forward: standard GELU variant
- [ ] End-to-end forward pass test: random weights, random input → output tensor
- [ ] Numerical correctness check against reference PyTorch implementation

---

## Phase 3 — FlashAttention-Style Tiled Attention

**Goal:** Implement IO-aware tiled attention kernels.

- [ ] FlashAttention forward pass (float32) in `shaders/flash_attention.metal`
  - Outer loop: Q tiles (block_q = 64)
  - Inner loop: K/V tiles (block_k = 64)
  - Online softmax normalisation (running max `m`, sum `l`)
  - Single output write per Q tile
- [ ] Causal masking inside flash_attention kernel
- [ ] FlashAttention backward pass (optional, harder)
- [ ] Benchmarks: compare naive O(N²) attention vs FlashAttention
- [ ] FP16 (`half`) variant of flash_attention kernel

---

## Phase 4 — LLaMA Inference

**Goal:** Autoregressive text generation with a LLaMA-style model.

- [ ] RMSNorm kernel (shaders/layernorm.metal, rms_only mode)
- [ ] Rotary Position Embedding (`shaders/rope.metal`)
- [ ] SwiGLU MLP variant
- [ ] KV cache: ring buffer, incremental decoding
- [ ] Weight loader: read safetensors format from disk
- [ ] Tokenizer: BPE via simple C++ implementation
- [ ] Greedy / top-k / temperature sampling
- [ ] End-to-end LLaMA-7B inference demo

---

## Phase 5 — Distributed / Parallel Concepts

**Goal:** Explore Megatron-style parallelism concepts on future hardware.

- [ ] Tensor parallelism design (column/row linear partitioning)
- [ ] Pipeline parallelism design (micro-batch scheduling)
- [ ] Multi-device abstraction (target: future Mac Pro with multiple M-series dies)
- [ ] Activation checkpointing for memory efficiency
- [ ] INT8 quantisation (QLoRA-style)
- [ ] INT4 quantisation (GPTQ-style)
- [ ] BF16 kernel variants (M3+)
- [ ] Unified memory optimisation: zero-copy KV cache

---

## Known Future Work (no target phase)

- Automatic differentiation / reverse-mode AD
- Compute graph fusion passes
- `MTLCounterSet` GPU performance counter integration
- JSON profiler trace (Chrome Trace Viewer format)
- Python binding (optional, for model weight conversion)
