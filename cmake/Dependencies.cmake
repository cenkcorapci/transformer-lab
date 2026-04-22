# Dependencies.cmake
# Fetches and configures third-party libraries via FetchContent.

include(FetchContent)

# ─── fmt ─────────────────────────────────────────────────────────────────────
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        10.2.1
    GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(fmt)

# ─── spdlog ──────────────────────────────────────────────────────────────────
# Use the bundled fmt to avoid duplicate symbols
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.13.0
    GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(spdlog)

# ─── CLI11 ───────────────────────────────────────────────────────────────────
FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG        v2.4.1
    GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(CLI11)

# ─── GoogleTest ──────────────────────────────────────────────────────────────
if(MTL_ENABLE_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
        GIT_SHALLOW    ON
    )
    # Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# ─── Google Benchmark ────────────────────────────────────────────────────────
if(MTL_ENABLE_BENCHMARKS)
    set(BENCHMARK_ENABLE_TESTING   OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.8.3
        GIT_SHALLOW    ON
    )
    FetchContent_MakeAvailable(benchmark)
endif()
