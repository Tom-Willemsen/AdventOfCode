add_library(2022_day16_impl SHARED day16_impl.c)
add_executable(2022_day16 day16.c)
target_link_libraries(2022_day16 2022_day16_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day16_tests day16_tests.c 2022_day16_impl) 
