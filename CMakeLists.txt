cmake_minimum_required(VERSION 3.21)
project(advent_of_code LANGUAGES C)

set(CMAKE_C_STANDARD 17)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Werror -Wpedantic)
endif()

include_directories("include")

add_executable(day1 1/day1.c)
add_executable(day2 2/day2.c)
add_executable(day3 3/day3.c)
