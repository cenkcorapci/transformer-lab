#include <mtl/core/tensor.hpp>
#include <mtl/ops/softmax.hpp>

#include <benchmark/benchmark.h>

// ─── Tensor allocation benchmarks ────────────────────────────────────────────

static void BM_SoftmaxAlloc(benchmark::State& state) {
    const std::size_t n = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        mtl::core::Tensor input ({n}, mtl::core::DataType::Float32);
        mtl::core::Tensor output({n}, mtl::core::DataType::Float32);
        // TODO: call softmax once implemented
        benchmark::DoNotOptimize(input);
        benchmark::DoNotOptimize(output);
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long>(n));
    state.SetBytesProcessed(state.iterations() *
                            static_cast<long>(n) * static_cast<long>(sizeof(float)));
}

BENCHMARK(BM_SoftmaxAlloc)
    ->Range(1 << 10, 1 << 22)
    ->Unit(benchmark::kMicrosecond);
