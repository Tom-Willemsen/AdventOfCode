add_library(2022_day22_impl SHARED day22_impl.c)
add_executable(2022_day22 day22.c)
target_link_libraries(2022_day22 2022_day22_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day22_tests day22_tests.c 2022_day22_impl) 
