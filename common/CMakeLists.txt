add_library(common SHARED 
    conversions.c 
    file_loading.c 
    linked_list.c 
)
add_unit_test(linked_list_tests linked_list_tests.c common)
