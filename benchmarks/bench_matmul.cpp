#include <mtl/core/tensor.hpp>
#include <mtl/ops/matmul.hpp>

#include <benchmark/benchmark.h>

// ─── Matrix allocation benchmarks ────────────────────────────────────────────

static void BM_MatmulAlloc(benchmark::State& state) {
    const std::size_t N = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        mtl::core::Tensor A({N, N}, mtl::core::DataType::Float32);
        mtl::core::Tensor B({N, N}, mtl::core::DataType::Float32);
        // TODO: call matmul once implemented
        benchmark::DoNotOptimize(A);
        benchmark::DoNotOptimize(B);
    }
    // Report FLOPs: 2 * N^3 for a square GEMM
    state.counters["GFLOPS_theoretical"] =
        benchmark::Counter(2.0 * static_cast<double>(N * N * N) * 1e-9,
                           benchmark::Counter::kIsIterationInvariant);
}

BENCHMARK(BM_MatmulAlloc)
    ->Arg(64)
    ->Arg(256)
    ->Arg(512)
    ->Arg(1024)
    ->Arg(2048)
    ->Unit(benchmark::kMicrosecond);
