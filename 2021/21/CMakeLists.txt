add_library(day21_impl SHARED day21_impl.c)
add_executable(day21 day21.c)
target_link_libraries(day21 day21_impl common)
add_unit_test(day21_tests day21_tests.c day21_impl) 
