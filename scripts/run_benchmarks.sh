#!/usr/bin/env bash
# run_benchmarks.sh — Run all benchmarks and save results to a JSON report.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build"
RUNNER="${BUILD_DIR}/benchmarks_runner"
REPORT_DIR="${REPO_ROOT}/benchmark_results"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
REPORT="${REPORT_DIR}/bench_${TIMESTAMP}.json"

if [[ ! -f "${RUNNER}" ]]; then
    echo "Error: benchmarks_runner not found. Build with MTL_ENABLE_BENCHMARKS=ON."
    exit 1
fi

mkdir -p "${REPORT_DIR}"

echo "Running benchmarks ..."
"${RUNNER}" \
    --benchmark_format=json \
    --benchmark_out="${REPORT}" \
    --benchmark_repetitions=3 \
    --benchmark_report_aggregates_only=true

echo "Results saved to: ${REPORT}"

# Also print a console summary
"${RUNNER}" \
    --benchmark_format=console \
    --benchmark_repetitions=1
