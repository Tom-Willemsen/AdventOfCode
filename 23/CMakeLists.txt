add_library(day23_impl SHARED day23_impl.c)
add_executable(day23 day23.c)
target_link_libraries(day23 day23_impl common)
add_unit_test(day23_tests day23_tests.c day23_impl) 
