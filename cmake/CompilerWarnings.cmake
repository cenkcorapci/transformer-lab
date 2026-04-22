# CompilerWarnings.cmake
# Sets aggressive but practical warning flags for C++ targets.

function(mtl_set_compiler_warnings target)
    set(_gcc_clang_warnings
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -Wimplicit-fallthrough
    )

    set(_clang_only_warnings
        -Wno-gnu-zero-variadic-macro-arguments
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
    )

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${target} PRIVATE
            ${_gcc_clang_warnings}
            ${_clang_only_warnings}
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE
            ${_gcc_clang_warnings}
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE /W4 /WX /permissive-)
    endif()
endfunction()
