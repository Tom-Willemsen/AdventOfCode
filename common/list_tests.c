#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "list.h"

void test_size (void ** state) {
    list_i64* list = list_i64_init(1);
    
    assert_int_equal(list->size, 0);
    list_i64_push_back(list, 5);
    assert_int_equal(list->size, 1);
    list_i64_push_front(list, 10);
    assert_int_equal(list->size, 2);
    list_i64_pop_front(list);
    assert_int_equal(list->size, 1);
    list_i64_pop_back(list);
    assert_int_equal(list->size, 0);
    
    list_i64_free(list);
}

void test_push_back_and_front (void ** state) {
    list_i64* list = list_i64_init(1);
    
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 2);
    assert_int_equal(list_i64_get(list, 0), 1);
    assert_int_equal(list_i64_get(list, 1), 2);
    list_i64_push_front(list, 3);
    list_i64_push_front(list, 4);
    assert_int_equal(list_i64_get(list, 0), 4);
    assert_int_equal(list_i64_get(list, 1), 3);
    assert_int_equal(list_i64_get(list, 2), 1);
    assert_int_equal(list_i64_get(list, 3), 2);
    
    list_i64_free(list);
}

void test_pop_back_and_front (void ** state) {
    list_i64* list = list_i64_init(1);
    
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 2);
    list_i64_push_back(list, 3);
    list_i64_push_back(list, 4);
    assert_int_equal(list_i64_pop_back(list), 4);
    assert_int_equal(list_i64_pop_front(list), 1);
    assert_int_equal(list_i64_pop_back(list), 3);
    assert_int_equal(list_i64_pop_front(list), 2);
    
    list_i64_free(list);
}

void test_peek_back_and_front (void ** state) {
    list_i64* list = list_i64_init(1);
    
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 2);
    list_i64_push_back(list, 3);
    list_i64_push_back(list, 4);
    assert_int_equal(list_i64_peek_back(list), 4);
    assert_int_equal(list_i64_peek_back(list), 4);
    assert_int_equal(list_i64_peek_front(list), 1);
    
    list_i64_free(list);
}

void test_contains (void ** state) {
    list_i64* list = list_i64_init(1);
    
    assert_int_equal(list_i64_contains(list, 1), 0);
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 2);
    assert_int_equal(list_i64_contains(list, 0), 0);
    assert_int_equal(list_i64_contains(list, 1), 1);
    assert_int_equal(list_i64_contains(list, 2), 1);
    assert_int_equal(list_i64_contains(list, 3), 0);
    
    list_i64_free(list);
}

void test_indexof (void ** state) {
    list_i64* list = list_i64_init(1);
    
    assert_int_equal(list_i64_indexof(list, 1), -1);
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 2);
    assert_int_equal(list_i64_indexof(list, 0), -1);
    assert_int_equal(list_i64_indexof(list, 1), 0);
    assert_int_equal(list_i64_indexof(list, 2), 1);
    assert_int_equal(list_i64_indexof(list, 3), -1);
    
    list_i64_free(list);
}

void test_remove (void ** state) {
    list_i64* list = list_i64_init(1);
    
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 2);
    list_i64_push_back(list, 3);
    list_i64_push_back(list, 4);
    assert_int_equal(list->size, 4);
    
    list_i64_remove(list, 2);
    
    assert_int_equal(list->size, 3);
    assert_int_equal(list_i64_indexof(list, 1), 0);
    assert_int_equal(list_i64_indexof(list, 2), 1);
    assert_int_equal(list_i64_indexof(list, 3), -1);
    assert_int_equal(list_i64_indexof(list, 4), 2);
    assert_int_equal(list_i64_get(list, 0), 1);
    assert_int_equal(list_i64_get(list, 1), 2);
    assert_int_equal(list_i64_get(list, 2), 4);
    
    
    list_i64_free(list);
}

void test_as_array (void ** state) {
    list_i64* list = list_i64_init(1);
    
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 22);
    list_i64_push_back(list, 333);
    list_i64_push_back(list, 44);
    list_i64_push_back(list, 5);

    uint64_t size;
    int64_t* arr = list_i64_as_array(list, &size);
    
    assert_int_equal(size, 5);
    assert_int_equal(arr[0], 1);
    assert_int_equal(arr[1], 22);
    assert_int_equal(arr[2], 333);
    assert_int_equal(arr[3], 44);
    assert_int_equal(arr[4], 5);
    
    free(arr);
    list_i64_free(list);
}

void test_min_max (void ** state) {
    list_i64* list = list_i64_init(1);
    
    list_i64_push_back(list, 1);
    list_i64_push_back(list, 2);
    list_i64_push_back(list, 3);
    list_i64_push_back(list, 4);
    
    assert_int_equal(list_i64_min(list), 1);
    assert_int_equal(list_i64_max(list), 4);
    
    assert_int_equal(list_i64_pop_front(list), 1);
    assert_int_equal(list_i64_pop_back(list), 4);
    
    assert_int_equal(list_i64_min(list), 2);
    assert_int_equal(list_i64_max(list), 3);
    
    assert_int_equal(list_i64_pop_front(list), 2);
    
    assert_int_equal(list_i64_min(list), 3);
    assert_int_equal(list_i64_max(list), 3);
    
    assert_int_equal(list_i64_pop_front(list), 3);
    
    assert_int_equal(list_i64_min(list), INT64_MAX);
    assert_int_equal(list_i64_max(list), INT64_MIN);
    
    list_i64_free(list);
}

void test_sort_inplace (void ** state) {
    list_i64* list = list_i64_init(1);
    
    list_i64_sort_inplace(list);
    
    list_i64_push_back(list, 4);
    list_i64_push_back(list, 2);
    list_i64_push_back(list, 3);
    
    list_i64_sort_inplace(list);
    
    assert_int_equal(list_i64_get(list, 0), 2);
    assert_int_equal(list_i64_get(list, 1), 3);
    assert_int_equal(list_i64_get(list, 2), 4);
    
    list_i64_push_back(list, 1);
    list_i64_push_front(list, 5);
    
    list_i64_sort_inplace(list);
    
    assert_int_equal(list_i64_get(list, 0), 1);
    assert_int_equal(list_i64_get(list, 1), 2);
    assert_int_equal(list_i64_get(list, 2), 3);
    assert_int_equal(list_i64_get(list, 3), 4);
    assert_int_equal(list_i64_get(list, 4), 5);
    
    list_i64_free(list);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_size),
        cmocka_unit_test (test_push_back_and_front),
        cmocka_unit_test (test_pop_back_and_front),
        cmocka_unit_test (test_peek_back_and_front),
        cmocka_unit_test (test_contains),
        cmocka_unit_test (test_indexof),
        cmocka_unit_test (test_remove),
        cmocka_unit_test (test_as_array),
        cmocka_unit_test (test_min_max),
        cmocka_unit_test (test_sort_inplace),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
 
