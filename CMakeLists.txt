cmake_minimum_required(VERSION 3.21)
project(advent_of_code LANGUAGES C)

find_library(NAMES cmocka REQUIRED)

set(CMAKE_C_STANDARD 17)

add_compile_options(
    -Wall 
    -Werror 
    -Wpedantic
    -Wno-unused-function
)

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
add_subdirectory(1/)
add_subdirectory(2/)
add_subdirectory(3/)
add_subdirectory(4/)
add_subdirectory(5/)
add_subdirectory(6/)
