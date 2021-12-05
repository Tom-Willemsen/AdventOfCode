add_library(day5_impl SHARED day5_impl.c)
add_executable(day5 day5.c)
target_link_libraries(day5 day5_impl common)
add_unit_test(day5_tests day5_tests.c day5_impl) 
