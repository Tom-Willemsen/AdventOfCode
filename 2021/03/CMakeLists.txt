add_library(day03_impl SHARED day03_impl.c)
add_executable(day03 day03.c)
target_link_libraries(day03 day03_impl common)
add_unit_test(day03_tests day03_tests.c day03_impl) 
