add_library(2022_day17_impl SHARED day17_impl.c)
add_executable(2022_day17 day17.c)
target_link_libraries(2022_day17 2022_day17_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day17_tests day17_tests.c 2022_day17_impl) 
