add_library(2022_day20_impl SHARED day20_impl.c)
add_executable(2022_day20 day20.c)
target_link_libraries(2022_day20 2022_day20_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day20_tests day20_tests.c 2022_day20_impl) 
