add_library(day12_impl SHARED day12_impl.c)
add_executable(day12 day12.c)
target_link_libraries(day12 day12_impl common)
add_unit_test(day12_tests day12_tests.c day12_impl) 
