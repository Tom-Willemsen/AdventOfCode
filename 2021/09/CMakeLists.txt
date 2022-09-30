add_library(day09_impl SHARED day09_impl.c)
add_executable(day09 day09.c)
target_link_libraries(day09 day09_impl common)
add_unit_test(day09_tests day09_tests.c day09_impl) 
