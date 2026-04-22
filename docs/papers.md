# Papers

Reference list for implementations planned in this repository.

---

## Implemented

*(none yet — scaffold only)*

---

## Planned

### Phase 1–2

| # | Paper | Year | Key Contribution |
|---|-------|------|-----------------|
| 1 | [Attention Is All You Need](https://arxiv.org/abs/1706.03762) | 2017 | Original Transformer: encoder-decoder with multi-head self-attention |
| 2 | [BERT: Pre-training of Deep Bidirectional Transformers](https://arxiv.org/abs/1810.04805) | 2018 | Masked language model pre-training; bidirectional encoder |

### Phase 3 — FlashAttention

| # | Paper | Year | Key Contribution |
|---|-------|------|-----------------|
| 3 | [FlashAttention: Fast and Memory-Efficient Exact Attention with IO-Awareness](https://arxiv.org/abs/2205.14135) | 2022 | Tiled attention that avoids materialising the N×N matrix; IO-optimal |
| 4 | [FlashAttention-2](https://arxiv.org/abs/2307.08691) | 2023 | Improved parallelism and work partitioning; 2× faster than FA-1 |

### Phase 4 — LLaMA

| # | Paper | Year | Key Contribution |
|---|-------|------|-----------------|
| 5 | [LLaMA: Open and Efficient Foundation Language Models](https://arxiv.org/abs/2302.13971) | 2023 | RMSNorm, SwiGLU, RoPE; efficient GPT-style decoder |
| 6 | [RoFormer: Enhanced Transformer with Rotary Position Embedding](https://arxiv.org/abs/2104.09864) | 2021 | Rotary positional encoding (RoPE) |
| 7 | [GLU Variants Improve Transformer](https://arxiv.org/abs/2002.05202) | 2020 | SwiGLU and other gated linear unit variants |

### Phase 5 — Systems / Parallelism

| # | Paper | Year | Key Contribution |
|---|-------|------|-----------------|
| 8 | [Megatron-LM: Training Multi-Billion Parameter Language Models Using Model Parallelism](https://arxiv.org/abs/1909.08053) | 2019 | Tensor parallelism for transformer layers |
| 9 | [GPipe: Efficient Training of Giant Neural Networks using Pipeline Parallelism](https://arxiv.org/abs/1811.06965) | 2018 | Pipeline parallelism with micro-batching |
| 10 | [ZeRO: Memory Optimizations Toward Training Trillion Parameter Models](https://arxiv.org/abs/1910.02054) | 2019 | Sharded optimizer state / gradients |

---

## Background Reading

- [The Illustrated Transformer](https://jalammar.github.io/illustrated-transformer/) — Jay Alammar
- [Transformer Circuits Thread](https://transformer-circuits.pub/) — Anthropic
- [ELI5: FlashAttention](https://gordicaleksa.medium.com/eli5-flash-attention-5c44017022ad) — Aleksa Gordić
- [Metal Shading Language Specification](https://developer.apple.com/metal/Metal-Shading-Language-Specification.pdf) — Apple
- [Apple Silicon CPU Optimization Guide](https://developer.apple.com/documentation/apple-silicon/cpu-optimization-guide) — Apple
