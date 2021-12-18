cmake_minimum_required(VERSION 3.21)
project(advent_of_code LANGUAGES C)

find_library(CMOCKA cmocka)
find_package(OpenMP)

set(CMAKE_C_STANDARD 17)

option(ASAN "Enable address sanitizer" OFF)

add_compile_options(
    -Wall 
    -Werror 
    -Wpedantic
    -Wno-unused-function
    -march=native
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
    -fsanitize-address-use-after-scope
  )
  add_link_options(
    -fsanitize=address
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
add_subdirectory(01/)
add_subdirectory(02/)
add_subdirectory(03/)
add_subdirectory(04/)
add_subdirectory(05/)
add_subdirectory(06/)
add_subdirectory(07/)
add_subdirectory(08/)
add_subdirectory(09/)
add_subdirectory(10/)
add_subdirectory(11/)
add_subdirectory(12/)
add_subdirectory(13/)
add_subdirectory(14/)
add_subdirectory(15/)
add_subdirectory(16/)
add_subdirectory(17/)
add_subdirectory(18/)
