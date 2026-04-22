# MetalHelpers.cmake
# Utilities for compiling .metal shaders to .metallib on Apple platforms.

# mtl_compile_shaders(<target>
#   SHADERS  <file1> [<file2> ...]
#   OUTPUT_DIR <dir>
# )
#
# For each .metal source file, this function:
#   1. Compiles it to a .air (Apple IR) file with `xcrun metal`
#   2. Links all .air files into a single default.metallib with `xcrun metallib`
# The resulting metallib path is added as a compile definition
# MTL_DEFAULT_METALLIB so the runtime can locate it at startup.

function(mtl_compile_shaders target)
    cmake_parse_arguments(PARSE_ARGV 1 ARG "" "OUTPUT_DIR" "SHADERS")

    if(NOT ARG_SHADERS)
        message(FATAL_ERROR "mtl_compile_shaders: no SHADERS provided")
    endif()

    if(NOT ARG_OUTPUT_DIR)
        set(ARG_OUTPUT_DIR "${CMAKE_BINARY_DIR}/shaders")
    endif()

    file(MAKE_DIRECTORY "${ARG_OUTPUT_DIR}")

    # Locate the Metal toolchain
    find_program(XCRUN xcrun REQUIRED)

    set(_air_files "")
    foreach(_src IN LISTS ARG_SHADERS)
        get_filename_component(_name "${_src}" NAME_WE)
        set(_air "${ARG_OUTPUT_DIR}/${_name}.air")

        add_custom_command(
            OUTPUT  "${_air}"
            COMMAND "${XCRUN}" -sdk macosx metal
                    -std=metal3.0
                    -O2
                    -c "${CMAKE_CURRENT_SOURCE_DIR}/${_src}"
                    -o "${_air}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${_src}"
            COMMENT "Compiling Metal shader: ${_src}"
            VERBATIM
        )
        list(APPEND _air_files "${_air}")
    endforeach()

    set(_metallib "${ARG_OUTPUT_DIR}/default.metallib")

    add_custom_command(
        OUTPUT  "${_metallib}"
        COMMAND "${XCRUN}" -sdk macosx metallib
                ${_air_files}
                -o "${_metallib}"
        DEPENDS ${_air_files}
        COMMENT "Linking Metal library: default.metallib"
        VERBATIM
    )

    add_custom_target(metal_shaders ALL DEPENDS "${_metallib}")
    add_dependencies(${target} metal_shaders)

    target_compile_definitions(${target}
        PRIVATE MTL_DEFAULT_METALLIB="${_metallib}"
    )
endfunction()
