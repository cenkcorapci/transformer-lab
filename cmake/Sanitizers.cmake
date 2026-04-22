# Sanitizers.cmake
# Enables AddressSanitizer and/or UndefinedBehaviorSanitizer on a target.

function(mtl_enable_sanitizers target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        message(STATUS "Enabling sanitizers for target: ${target}")
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -g
        )
        target_link_options(${target} PRIVATE
            -fsanitize=address,undefined
        )
    else()
        message(WARNING "Sanitizers not supported for compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endfunction()
