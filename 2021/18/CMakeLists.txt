add_library(day18_impl SHARED day18_impl.c)
add_executable(day18 day18.c)
target_link_libraries(day18 day18_impl common OpenMP::OpenMP_C)
add_unit_test(day18_tests day18_tests.c day18_impl) 
