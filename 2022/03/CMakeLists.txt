add_library(2022_day03_impl SHARED day03_impl.c)
add_executable(2022_day03 day03.c)
target_link_libraries(2022_day03 2022_day03_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day03_tests day03_tests.c 2022_day03_impl) 
