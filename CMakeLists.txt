cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_STANDARD 11)


project(advent_of_code LANGUAGES C)

add_compile_options(-Wall -Wextra -Werror -pedantic)

add_executable(day1 1/day1.c)

