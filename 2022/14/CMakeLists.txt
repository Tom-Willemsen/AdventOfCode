add_library(2022_day14_impl SHARED day14_impl.c)
add_executable(2022_day14 day14.c)
target_link_libraries(2022_day14 2022_day14_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day14_tests day14_tests.c 2022_day14_impl) 
