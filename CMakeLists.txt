cmake_minimum_required(VERSION 3.26)

project(
    metal_transformer_lab
    VERSION 0.1.0
    DESCRIPTION "C++20 + Apple Metal transformer systems playground"
    LANGUAGES CXX
)

# ─── C++ standard ────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ─── CMake modules ───────────────────────────────────────────────────────────
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ─── User-facing options ─────────────────────────────────────────────────────
option(MTL_ENABLE_TESTS       "Build unit tests (GoogleTest)"          ON)
option(MTL_ENABLE_BENCHMARKS  "Build microbenchmarks (Google Benchmark)" ON)
option(MTL_ENABLE_SANITIZERS  "Enable AddressSanitizer / UBSan"        OFF)
option(MTL_ENABLE_METAL       "Enable Apple Metal GPU backend"          ON)

# ─── Platform guard ──────────────────────────────────────────────────────────
if(MTL_ENABLE_METAL)
    if(NOT APPLE)
        message(WARNING
            "MTL_ENABLE_METAL=ON but target platform is not Apple. "
            "Metal support will be disabled.")
        set(MTL_ENABLE_METAL OFF)
    endif()
endif()

message(STATUS "=== metal-transformer-lab ===")
message(STATUS "  Version           : ${PROJECT_VERSION}")
message(STATUS "  Build type        : ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard      : ${CMAKE_CXX_STANDARD}")
message(STATUS "  Enable Metal      : ${MTL_ENABLE_METAL}")
message(STATUS "  Enable Tests      : ${MTL_ENABLE_TESTS}")
message(STATUS "  Enable Benchmarks : ${MTL_ENABLE_BENCHMARKS}")
message(STATUS "  Enable Sanitizers : ${MTL_ENABLE_SANITIZERS}")

# ─── Build helpers ───────────────────────────────────────────────────────────
include(CompilerWarnings)
include(Sanitizers)
include(Dependencies)

if(MTL_ENABLE_METAL)
    include(MetalHelpers)
endif()

# ─── Export compile commands (for clangd / clang-tidy) ───────────────────────
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ─── Core static library ─────────────────────────────────────────────────────
file(GLOB_RECURSE MTL_CORE_SOURCES
    "src/core/*.cpp"
    "src/gpu/*.cpp"
    "src/ops/*.cpp"
    "src/nn/*.cpp"
    "src/runtime/*.cpp"
    "src/utils/*.cpp"
)

add_library(mtl_core STATIC ${MTL_CORE_SOURCES})

target_include_directories(mtl_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(mtl_core
    PUBLIC
        fmt::fmt
        spdlog::spdlog
)

mtl_set_compiler_warnings(mtl_core)

if(MTL_ENABLE_SANITIZERS)
    mtl_enable_sanitizers(mtl_core)
endif()

# ─── Apple frameworks ────────────────────────────────────────────────────────
if(MTL_ENABLE_METAL)
    find_library(METAL_FRAMEWORK     Metal      REQUIRED)
    find_library(FOUNDATION_FRAMEWORK Foundation REQUIRED)
    find_library(QUARTZCORE_FRAMEWORK QuartzCore REQUIRED)
    find_library(METALKIT_FRAMEWORK   MetalKit)  # optional

    target_link_libraries(mtl_core
        PUBLIC
            ${METAL_FRAMEWORK}
            ${FOUNDATION_FRAMEWORK}
            ${QUARTZCORE_FRAMEWORK}
    )

    if(METALKIT_FRAMEWORK)
        target_link_libraries(mtl_core PUBLIC ${METALKIT_FRAMEWORK})
        target_compile_definitions(mtl_core PUBLIC MTL_HAS_METALKIT=1)
    endif()

    target_compile_definitions(mtl_core PUBLIC MTL_ENABLE_METAL=1)

    # Compile .metal shaders → .metallib
    mtl_compile_shaders(mtl_core
        SHADERS
            shaders/common.metal
            shaders/matmul.metal
            shaders/softmax.metal
            shaders/layernorm.metal
            shaders/rope.metal
            shaders/flash_attention.metal
        OUTPUT_DIR "${CMAKE_BINARY_DIR}/shaders"
    )
endif()

# ─── Executables ─────────────────────────────────────────────────────────────
add_executable(playground      apps/playground_main.cpp)
add_executable(infer           apps/infer_main.cpp)
add_executable(train           apps/train_main.cpp)

foreach(_exe playground infer train)
    target_link_libraries(${_exe} PRIVATE mtl_core CLI11::CLI11)
    mtl_set_compiler_warnings(${_exe})
endforeach()

# ─── Tests ───────────────────────────────────────────────────────────────────
if(MTL_ENABLE_TESTS)
    enable_testing()

    file(GLOB_RECURSE MTL_TEST_SOURCES "tests/*.cpp")

    add_executable(unit_tests ${MTL_TEST_SOURCES})
    target_link_libraries(unit_tests
        PRIVATE
            mtl_core
            GTest::gtest_main
    )
    mtl_set_compiler_warnings(unit_tests)

    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()

# ─── Benchmarks ──────────────────────────────────────────────────────────────
if(MTL_ENABLE_BENCHMARKS)
    file(GLOB_RECURSE MTL_BENCH_SOURCES "benchmarks/*.cpp")

    add_executable(benchmarks_runner
        ${MTL_BENCH_SOURCES}
        apps/benchmark_main.cpp
    )
    target_link_libraries(benchmarks_runner
        PRIVATE
            mtl_core
            benchmark::benchmark_main
    )
    mtl_set_compiler_warnings(benchmarks_runner)
endif()
