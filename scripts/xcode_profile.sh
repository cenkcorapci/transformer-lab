#!/usr/bin/env bash
# xcode_profile.sh — Launch a binary under Xcode Instruments Metal System Trace.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build"
TARGET="${1:-playground}"
BINARY="${BUILD_DIR}/${TARGET}"
TRACE_OUT="/tmp/mtl_${TARGET}.trace"

if [[ ! -f "${BINARY}" ]]; then
    echo "Error: ${BINARY} not found. Build the project first."
    exit 1
fi

echo "Recording Metal System Trace for: ${BINARY}"
xcrun xctrace record \
    --template "Metal System Trace" \
    --output "${TRACE_OUT}" \
    --launch "${BINARY}" -- "${@:2}"

echo "Trace saved to: ${TRACE_OUT}"
echo "Open with: open ${TRACE_OUT}"
