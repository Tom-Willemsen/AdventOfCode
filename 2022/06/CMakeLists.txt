add_library(2022_day06_impl SHARED day06_impl.c)
add_executable(2022_day06 day06.c)
target_link_libraries(2022_day06 2022_day06_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day06_tests day06_tests.c 2022_day06_impl) 
