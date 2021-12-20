add_library(day20_impl SHARED day20_impl.c)
add_executable(day20 day20.c)
target_link_libraries(day20 day20_impl common)
add_unit_test(day20_tests day20_tests.c day20_impl) 
