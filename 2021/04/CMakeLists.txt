add_library(day04_impl SHARED day04_impl.c)
add_executable(day04 day04.c)
target_link_libraries(day04 day04_impl common)
add_unit_test(day04_tests day04_tests.c day04_impl) 
