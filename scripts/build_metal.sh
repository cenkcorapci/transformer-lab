#!/usr/bin/env bash
# build_metal.sh — Configure and build the project for macOS/Apple Silicon.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build"
BUILD_TYPE="${BUILD_TYPE:-Release}"

echo "=== metal-transformer-lab build ==="
echo "  Repo root  : ${REPO_ROOT}"
echo "  Build dir  : ${BUILD_DIR}"
echo "  Build type : ${BUILD_TYPE}"

cmake -B "${BUILD_DIR}" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DMTL_ENABLE_TESTS=ON \
    -DMTL_ENABLE_BENCHMARKS=ON \
    -DMTL_ENABLE_METAL=ON \
    "${REPO_ROOT}"

cmake --build "${BUILD_DIR}" --parallel

echo ""
echo "Build complete. Binaries:"
echo "  ${BUILD_DIR}/playground"
echo "  ${BUILD_DIR}/infer"
echo "  ${BUILD_DIR}/train"
echo "  ${BUILD_DIR}/unit_tests"
echo "  ${BUILD_DIR}/benchmarks_runner"
