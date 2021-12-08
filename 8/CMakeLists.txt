add_library(day8_impl SHARED day8_impl.c)
add_executable(day8 day8.c)
target_link_libraries(day8 day8_impl common)
add_unit_test(day8_tests day8_tests.c day8_impl) 
