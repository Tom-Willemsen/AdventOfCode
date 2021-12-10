cmake_minimum_required(VERSION 3.21)
project(advent_of_code LANGUAGES C)

find_library(NAMES cmocka REQUIRED)

set(CMAKE_C_STANDARD 17)

add_compile_options(
    -Wall 
    -Werror 
    -Wpedantic
    -Wno-unused-function
    -march=native
)

include(CheckIPOSupported)
check_ipo_supported()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories("common")

function(add_unit_test name source link)
    add_executable(${name} ${source})
    target_include_directories(${name} PUBLIC 3)
    target_link_libraries(${name} cmocka common ${link})
    add_custom_command(
        TARGET ${name} 
        POST_BUILD 
        COMMAND ${name}
        COMMENT "Tests for ${link} from ${source}"
    )
    add_custom_target(${name}.RUN_TESTS ${name} ALL)
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
