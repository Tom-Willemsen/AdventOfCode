add_library(day25_impl SHARED day25_impl.c)
add_executable(day25 day25.c)
target_link_libraries(day25 day25_impl common OpenMP::OpenMP_C)
add_unit_test(day25_tests day25_tests.c day25_impl) 
