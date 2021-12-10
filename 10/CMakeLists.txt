add_library(day10_impl SHARED day10_impl.c)
add_executable(day10 day10.c)
target_link_libraries(day10 day10_impl common)
add_unit_test(day10_tests day10_tests.c day10_impl) 
