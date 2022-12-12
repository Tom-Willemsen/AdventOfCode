add_library(2022_day12_impl SHARED day12_impl.c)
add_executable(2022_day12 day12.c)
target_link_libraries(2022_day12 2022_day12_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day12_tests day12_tests.c 2022_day12_impl) 
