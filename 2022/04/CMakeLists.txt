add_library(2022_day04_impl SHARED day04_impl.c)
add_executable(2022_day04 day04.c)
target_link_libraries(2022_day04 2022_day04_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day04_tests day04_tests.c 2022_day04_impl) 
