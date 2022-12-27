add_library(2022_day23_impl SHARED day23_impl.c)
add_executable(2022_day23 day23.c)
target_link_libraries(2022_day23 2022_day23_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day23_tests day23_tests.c 2022_day23_impl) 
