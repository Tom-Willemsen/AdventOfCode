cmake_minimum_required(VERSION 3.21)
project(advent_of_code LANGUAGES C)

find_library(CMOCKA cmocka)
find_package(OpenMP)

set(CMAKE_C_STANDARD 23)

option(ASAN "Enable address sanitizer" OFF)

add_compile_options(
    -Wall
    -Wextra
    -Werror 
    -Wpedantic
    -Wno-unused-function
    -Wno-unused-parameter
    -Wno-sign-compare
    $<$<C_COMPILER_ID:GNU>:-Waggressive-loop-optimizations>
    -march=native
    -mtune=native
    -ffast-math
    -fopenmp
)

add_link_options(
    -fopenmp
)

if(ASAN)
  add_compile_options(
    -fstack-protector-all
    -fsanitize=address
    -fno-omit-frame-pointer
    $<$<C_COMPILER_ID:Clang>:-fsanitize-address-use-after-return=always>
    $<$<C_COMPILER_ID:Clang>:-fsanitize=undefined>
    -fsanitize-address-use-after-scope
  )
  add_link_options(
    -fsanitize=address
    $<$<C_COMPILER_ID:Clang>:-fsanitize=undefined>
  )
endif(ASAN)


include(CheckIPOSupported)
check_ipo_supported()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories("common")

function(add_unit_test name source link)
    if (CMOCKA)
        add_executable(${name} ${source})
        target_link_libraries(${name} cmocka common ${link})
        add_custom_command(
            TARGET ${name} 
            POST_BUILD 
            COMMAND ${name}
            COMMENT "Tests for ${link} from ${source}"
        )
        add_custom_target(${name}.RUN_TESTS ${name} ALL)
    else()
        message(AUTHOR_WARNING "Skipping creating ${name} from ${source} as cmocka is not available")
    endif()
endfunction(add_unit_test)

add_subdirectory(common/)
add_subdirectory(2021)
add_subdirectory(2022)
