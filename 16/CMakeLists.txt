add_library(day16_impl SHARED day16_impl.c)
add_executable(day16 day16.c)
target_link_libraries(day16 day16_impl common)
add_unit_test(day16_tests day16_tests.c day16_impl) 
