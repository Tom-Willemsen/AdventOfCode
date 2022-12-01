add_library(2022_day01_impl SHARED day01_impl.c)
add_executable(2022_day01 day01.c)
target_link_libraries(2022_day01 2022_day01_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day01_tests day01_tests.c 2022_day01_impl) 
