add_library(day22_impl SHARED day22_impl.c)
add_executable(day22 day22.c)
target_link_libraries(day22 day22_impl common)
add_unit_test(day22_tests day22_tests.c day22_impl) 
