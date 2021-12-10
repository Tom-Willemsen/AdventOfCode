add_library(day07_impl SHARED day07_impl.c)
add_executable(day07 day07.c)
target_link_libraries(day07 day07_impl common)
add_unit_test(day07_tests day07_tests.c day07_impl) 
