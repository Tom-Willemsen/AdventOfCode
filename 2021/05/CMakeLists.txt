add_library(day05_impl SHARED day05_impl.c)
add_executable(day05 day05.c)
target_link_libraries(day05 day05_impl common)
add_unit_test(day05_tests day05_tests.c day05_impl) 
