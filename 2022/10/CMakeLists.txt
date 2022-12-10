add_library(2022_day10_impl SHARED day10_impl.c)
add_executable(2022_day10 day10.c)
target_link_libraries(2022_day10 2022_day10_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day10_tests day10_tests.c 2022_day10_impl) 
