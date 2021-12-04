#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "linked_list.h"

void test_size (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    assert_int_equal(ll->size, 0);
    ll_i64_push_back(ll, 5);
    assert_int_equal(ll->size, 1);
    ll_i64_push_front(ll, 10);
    assert_int_equal(ll->size, 2);
    ll_i64_pop_front(ll);
    assert_int_equal(ll->size, 1);
    ll_i64_pop_back(ll);
    assert_int_equal(ll->size, 0);
    
    ll_i64_free(ll);
}

void test_push_back_and_front (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    ll_i64_push_back(ll, 1);
    ll_i64_push_back(ll, 2);
    assert_int_equal(ll_i64_get(ll, 0), 1);
    assert_int_equal(ll_i64_get(ll, 1), 2);
    ll_i64_push_front(ll, 3);
    ll_i64_push_front(ll, 4);
    assert_int_equal(ll_i64_get(ll, 0), 4);
    assert_int_equal(ll_i64_get(ll, 1), 3);
    assert_int_equal(ll_i64_get(ll, 2), 1);
    assert_int_equal(ll_i64_get(ll, 3), 2);
    
    ll_i64_free(ll);
}

void test_pop_back_and_front (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    ll_i64_push_back(ll, 1);
    ll_i64_push_back(ll, 2);
    ll_i64_push_back(ll, 3);
    ll_i64_push_back(ll, 4);
    assert_int_equal(ll_i64_pop_back(ll), 4);
    assert_int_equal(ll_i64_pop_front(ll), 1);
    assert_int_equal(ll_i64_pop_back(ll), 3);
    assert_int_equal(ll_i64_pop_front(ll), 2);
    
    ll_i64_free(ll);
}

void test_peek_back_and_front (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    ll_i64_push_back(ll, 1);
    ll_i64_push_back(ll, 2);
    ll_i64_push_back(ll, 3);
    ll_i64_push_back(ll, 4);
    assert_int_equal(ll_i64_peek_back(ll), 4);
    assert_int_equal(ll_i64_peek_back(ll), 4);
    assert_int_equal(ll_i64_peek_front(ll), 1);
    
    ll_i64_free(ll);
}

void test_contains (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    assert_int_equal(ll_i64_contains(ll, 1), 0);
    ll_i64_push_back(ll, 1);
    ll_i64_push_back(ll, 2);
    assert_int_equal(ll_i64_contains(ll, 0), 0);
    assert_int_equal(ll_i64_contains(ll, 1), 1);
    assert_int_equal(ll_i64_contains(ll, 2), 1);
    assert_int_equal(ll_i64_contains(ll, 3), 0);
    
    ll_i64_free(ll);
}

void test_indexof (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    assert_int_equal(ll_i64_indexof(ll, 1), -1);
    ll_i64_push_back(ll, 1);
    ll_i64_push_back(ll, 2);
    assert_int_equal(ll_i64_indexof(ll, 0), -1);
    assert_int_equal(ll_i64_indexof(ll, 1), 0);
    assert_int_equal(ll_i64_indexof(ll, 2), 1);
    assert_int_equal(ll_i64_indexof(ll, 3), -1);
    
    ll_i64_free(ll);
}

void test_remove (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    ll_i64_push_back(ll, 1);
    ll_i64_push_back(ll, 2);
    ll_i64_push_back(ll, 3);
    ll_i64_push_back(ll, 4);
    assert_int_equal(ll->size, 4);
    
    ll_i64_remove(ll, 2);
    
    assert_int_equal(ll->size, 3);
    assert_int_equal(ll_i64_indexof(ll, 1), 0);
    assert_int_equal(ll_i64_indexof(ll, 2), 1);
    assert_int_equal(ll_i64_indexof(ll, 3), -1);
    assert_int_equal(ll_i64_indexof(ll, 4), 2);
    assert_int_equal(ll_i64_get(ll, 0), 1);
    assert_int_equal(ll_i64_get(ll, 1), 2);
    assert_int_equal(ll_i64_get(ll, 2), 4);
    
    
    ll_i64_free(ll);
}

void test_as_array (void ** state) {
    ll_i64* ll = ll_i64_init();
    
    ll_i64_push_back(ll, 1);
    ll_i64_push_back(ll, 22);
    ll_i64_push_back(ll, 333);
    ll_i64_push_back(ll, 44);
    ll_i64_push_back(ll, 5);

    uint64_t size;
    int64_t* arr = ll_i64_as_array(ll, &size);
    
    assert_int_equal(size, 5);
    assert_int_equal(arr[0], 1);
    assert_int_equal(arr[1], 22);
    assert_int_equal(arr[2], 333);
    assert_int_equal(arr[3], 44);
    assert_int_equal(arr[4], 5);
    
    free(arr);
    ll_i64_free(ll);
}

void test_iterator (void ** state) {
    int64_t value, pos = 0;
    ll_i64* ll = ll_i64_init();
    
    ll_i64_push_back(ll, 0);
    ll_i64_push_back(ll, 20);
    ll_i64_push_back(ll, 40);

    ll_i64_node* it = ll->start;
    while (ll_i64_next(&it, &value)) {
        assert_int_equal(value, pos * 20);
        pos++;
    }
    assert_int_equal(pos, 3);
    
    ll_i64_pop_front(ll);
    ll_i64_pop_front(ll);
    ll_i64_pop_front(ll);
    assert_int_equal(ll->size, 0);
    
    it = ll->start;
    while (ll_i64_next(&it, &value)) {
        assert_true(0);
    }
    
    ll_i64_free(ll);
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
        cmocka_unit_test (test_iterator),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
 
