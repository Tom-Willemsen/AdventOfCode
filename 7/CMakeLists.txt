add_library(day7_impl SHARED day7_impl.c)
add_executable(day7 day7.c)
target_link_libraries(day7 day7_impl common)
add_unit_test(day7_tests day7_tests.c day7_impl) 
