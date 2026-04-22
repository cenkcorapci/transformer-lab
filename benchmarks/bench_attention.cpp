#include <mtl/core/tensor.hpp>
#include <mtl/nn/attention.hpp>

#include <benchmark/benchmark.h>

// ─── Attention benchmarks ─────────────────────────────────────────────────────

static void BM_AttentionForwardAlloc(benchmark::State& state) {
    const std::size_t seq_len  = static_cast<std::size_t>(state.range(0));
    const std::size_t emb_dim  = 512;

    mtl::nn::MultiHeadAttention::Config cfg;
    cfg.embed_dim = emb_dim;
    cfg.num_heads = 8;
    cfg.head_dim  = emb_dim / 8;
    cfg.is_causal = true;

    mtl::nn::MultiHeadAttention attn(cfg);

    for (auto _ : state) {
        mtl::core::Tensor q({1, seq_len, emb_dim}, mtl::core::DataType::Float32);
        mtl::core::Tensor k({1, seq_len, emb_dim}, mtl::core::DataType::Float32);
        mtl::core::Tensor v({1, seq_len, emb_dim}, mtl::core::DataType::Float32);
        // TODO: call attn.forward once implemented
        benchmark::DoNotOptimize(q);
        benchmark::DoNotOptimize(k);
        benchmark::DoNotOptimize(v);
    }
}

BENCHMARK(BM_AttentionForwardAlloc)
    ->Arg(128)
    ->Arg(256)
    ->Arg(512)
    ->Arg(1024)
    ->Arg(2048)
    ->Unit(benchmark::kMillisecond);
