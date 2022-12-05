add_library(2022_day05_impl SHARED day05_impl.c)
add_executable(2022_day05 day05.c)
target_link_libraries(2022_day05 2022_day05_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day05_tests day05_tests.c 2022_day05_impl) 
