add_library(2022_day11_impl SHARED day11_impl.c)
add_executable(2022_day11 day11.c)
target_link_libraries(2022_day11 2022_day11_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day11_tests day11_tests.c 2022_day11_impl) 
