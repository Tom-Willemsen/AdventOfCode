#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "bitset.h"

void test_size (void ** state) {
    
}

void test_bitset (void ** state) {
    bitset* bs = bitset_init(128);
    assert_int_equal(bs->size, 128);
    
    bitset_set(bs, 0);
    bitset_set(bs, 1);
    assert_int_equal(bitset_popcnt(bs), 2);
    assert_int_equal(bitset_get(bs, 0), 1);
    assert_int_equal(bitset_get(bs, 1), 1);
    
    bitset_set(bs, 127);
    assert_int_equal(bitset_popcnt(bs), 3);
    
    bitset_toggle(bs, 1);
    assert_int_equal(bitset_popcnt(bs), 2);
    assert_int_equal(bitset_get(bs, 1), 0);
    
    bitset_toggle(bs, 2);
    assert_int_equal(bitset_popcnt(bs), 3);
    assert_int_equal(bitset_get(bs, 2), 1);
    
    bitset_clear(bs, 2);
    assert_int_equal(bitset_popcnt(bs), 2);
    assert_int_equal(bitset_get(bs, 2), 0);
    
    bitset_free(bs);
}

void test_bitset_alloc_size (void ** state) {
    assert_int_equal(bitset_alloc_size(1), 1);
    assert_int_equal(bitset_alloc_size(32), 1);
    assert_int_equal(bitset_alloc_size(64), 1);
    assert_int_equal(bitset_alloc_size(65), 2);
    assert_int_equal(bitset_alloc_size(128), 2);
    assert_int_equal(bitset_alloc_size(129), 3);
}


int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_bitset),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
 
