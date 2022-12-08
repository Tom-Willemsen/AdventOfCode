add_library(2022_day08_impl SHARED day08_impl.c)
add_executable(2022_day08 day08.c)
target_link_libraries(2022_day08 2022_day08_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day08_tests day08_tests.c 2022_day08_impl) 
