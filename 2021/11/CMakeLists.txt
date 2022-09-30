add_library(day11_impl SHARED day11_impl.c)
add_executable(day11 day11.c)
target_link_libraries(day11 day11_impl common)
add_unit_test(day11_tests day11_tests.c day11_impl) 
