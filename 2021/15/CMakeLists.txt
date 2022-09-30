add_library(day15_impl SHARED day15_impl.c)
add_executable(day15 day15.c)
target_link_libraries(day15 day15_impl common)
add_unit_test(day15_tests day15_tests.c day15_impl) 
