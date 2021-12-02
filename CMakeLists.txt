cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_STANDARD 17)

project(advent_of_code LANGUAGES C)

add_compile_options(-Wall -Werror -Wpedantic)

add_executable(day1 1/day1.c)
add_executable(day2 2/day2.c)
