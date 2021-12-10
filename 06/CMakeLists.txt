add_library(day06_impl SHARED day06_impl.c)
add_executable(day06 day06.c)
target_link_libraries(day06 day06_impl common)
add_unit_test(day06_tests day06_tests.c day06_impl) 
