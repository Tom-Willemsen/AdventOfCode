add_library(2022_day07_impl SHARED day07_impl.c)
add_executable(2022_day07 day07.c)
target_link_libraries(2022_day07 2022_day07_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day07_tests day07_tests.c 2022_day07_impl) 
