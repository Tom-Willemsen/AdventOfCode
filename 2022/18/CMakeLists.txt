add_library(2022_day18_impl SHARED day18_impl.c)
add_executable(2022_day18 day18.c)
target_link_libraries(2022_day18 2022_day18_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day18_tests day18_tests.c 2022_day18_impl) 
