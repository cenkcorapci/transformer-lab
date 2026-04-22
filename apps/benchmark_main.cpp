#include <mtl/runtime/engine.hpp>
#include <mtl/utils/logging.hpp>
#include <mtl/utils/timer.hpp>

#include <benchmark/benchmark.h>

// ─── Benchmark stubs ─────────────────────────────────────────────────────────
// Add benchmarks below and they will be discovered by Google Benchmark.

static void BM_EngineInit(benchmark::State& state) {
    for (auto _ : state) {
        mtl::runtime::Engine engine;
        benchmark::DoNotOptimize(engine);
    }
}
BENCHMARK(BM_EngineInit);

static void BM_TensorAlloc(benchmark::State& state) {
    const std::size_t numel = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        mtl::core::Tensor t({numel}, mtl::core::DataType::Float32);
        benchmark::DoNotOptimize(t);
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long>(numel));
}
BENCHMARK(BM_TensorAlloc)->Range(1 << 10, 1 << 24);

// ─── main ────────────────────────────────────────────────────────────────────
// benchmark::Initialize / benchmark::RunSpecifiedBenchmarks are provided by
// benchmark_main from the Google Benchmark library.
