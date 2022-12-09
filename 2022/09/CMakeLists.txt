add_library(2022_day09_impl SHARED day09_impl.c)
add_executable(2022_day09 day09.c)
target_link_libraries(2022_day09 2022_day09_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day09_tests day09_tests.c 2022_day09_impl) 
