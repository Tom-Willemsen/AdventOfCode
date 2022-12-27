add_library(2022_day24_impl SHARED day24_impl.c)
add_executable(2022_day24 day24.c)
target_link_libraries(2022_day24 2022_day24_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day24_tests day24_tests.c 2022_day24_impl) 
