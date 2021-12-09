add_library(day9_impl SHARED day9_impl.c)
add_executable(day9 day9.c)
target_link_libraries(day9 day9_impl common)
add_unit_test(day9_tests day9_tests.c day9_impl) 
