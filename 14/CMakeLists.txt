add_library(day14_impl SHARED day14_impl.c)
add_executable(day14 day14.c)
target_link_libraries(day14 day14_impl common)
add_unit_test(day14_tests day14_tests.c day14_impl) 
