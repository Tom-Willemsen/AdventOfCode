add_library(day08_impl SHARED day08_impl.c)
add_executable(day08 day08.c)
target_link_libraries(day08 day08_impl common)
add_unit_test(day08_tests day08_tests.c day08_impl) 
