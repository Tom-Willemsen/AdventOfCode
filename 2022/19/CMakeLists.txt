add_library(2022_day19_impl SHARED day19_impl.c)
add_executable(2022_day19 day19.c)
target_link_libraries(2022_day19 2022_day19_impl common OpenMP::OpenMP_C)
add_unit_test(2022_day19_tests day19_tests.c 2022_day19_impl) 
