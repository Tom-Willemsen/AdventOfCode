add_library(2022_day13_impl SHARED day13_impl.c)
add_executable(2022_day13 day13.c)
target_link_libraries(2022_day13 2022_day13_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day13_tests day13_tests.c 2022_day13_impl) 
