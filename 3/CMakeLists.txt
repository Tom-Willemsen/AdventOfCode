add_library(day3_impl SHARED day3_impl.c)
add_executable(day3 day3.c)
target_link_libraries(day3 day3_impl common)
add_unit_test(day3_tests day3_tests.c day3_impl) 
