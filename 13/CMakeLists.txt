add_library(day13_impl SHARED day13_impl.c)
add_executable(day13 day13.c)
target_link_libraries(day13 day13_impl common)
add_unit_test(day13_tests day13_tests.c day13_impl) 
