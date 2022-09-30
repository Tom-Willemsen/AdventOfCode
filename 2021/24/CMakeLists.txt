add_library(day24_impl SHARED day24_impl.c)
add_executable(day24 day24.c)
target_link_libraries(day24 day24_impl common OpenMP::OpenMP_C)
add_unit_test(day24_tests day24_tests.c day24_impl) 
