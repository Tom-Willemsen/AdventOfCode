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
    
    bitset_set(bs, 127);
    assert_int_equal(bitset_popcnt(bs), 3);
    
    bitset_toggle(bs, 1);
    assert_int_equal(bitset_popcnt(bs), 2);
    
    bitset_toggle(bs, 2);
    assert_int_equal(bitset_popcnt(bs), 3);
    
    bitset_clear(bs, 2);
    assert_int_equal(bitset_popcnt(bs), 2);
    
    bitset_free(bs);
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
 
