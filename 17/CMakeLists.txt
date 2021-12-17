add_library(day17_impl SHARED day17_impl.c)
add_executable(day17 day17.c)
target_link_libraries(day17 day17_impl common)
add_unit_test(day17_tests day17_tests.c day17_impl) 
