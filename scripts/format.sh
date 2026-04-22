#!/usr/bin/env bash
# format.sh — Run clang-format over all C++ source and header files.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

find "${REPO_ROOT}" \
    \( -path "${REPO_ROOT}/build" -o -path "${REPO_ROOT}/_deps" \) -prune \
    -o \( -name "*.cpp" -o -name "*.hpp" -o -name "*.h" \) -print \
    | xargs clang-format -i --style=file

echo "clang-format complete."
