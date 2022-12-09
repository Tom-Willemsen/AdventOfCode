add_library(common SHARED 
    conversions.c 
    deque.c 
    file_loading.c
)
add_unit_test(deque_tests deque_tests.c common)
add_unit_test(list_tests list_tests.c common)
add_unit_test(bitset_tests bitset_tests.c common)
