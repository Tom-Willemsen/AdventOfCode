add_library(day4_impl SHARED day4_impl.c)
add_executable(day4 day4.c)
target_link_libraries(day4 day4_impl)
add_unit_test(day4_tests day4_tests.c day4_impl) 
