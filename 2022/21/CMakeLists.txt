add_library(2022_day21_impl SHARED day21_impl.c)
add_executable(2022_day21 day21.c)
target_link_libraries(2022_day21 2022_day21_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day21_tests day21_tests.c 2022_day21_impl) 
