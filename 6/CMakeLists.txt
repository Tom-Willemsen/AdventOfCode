add_library(day6_impl SHARED day6_impl.c)
add_executable(day6 day6.c)
target_link_libraries(day6 day6_impl common)
add_unit_test(day6_tests day6_tests.c day6_impl) 
