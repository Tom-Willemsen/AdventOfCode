add_library(2022_day02_impl SHARED day02_impl.c)
add_executable(2022_day02 day02.c)
target_link_libraries(2022_day02 2022_day02_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day02_tests day02_tests.c 2022_day02_impl) 
