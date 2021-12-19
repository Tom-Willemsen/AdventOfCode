add_library(day19_impl SHARED day19_impl.c)
add_executable(day19 day19.c)
target_link_libraries(day19 day19_impl common OpenMP::OpenMP_C)
add_unit_test(day19_tests day19_tests.c day19_impl) 
