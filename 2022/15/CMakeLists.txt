add_library(2022_day15_impl SHARED day15_impl.c)
add_executable(2022_day15 day15.c)
target_link_libraries(2022_day15 2022_day15_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day15_tests day15_tests.c 2022_day15_impl) 
