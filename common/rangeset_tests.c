#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "rangeset.h"

void test_set_independent_ranges (void ** state) {
    rangeset* rs = rangeset_init();
    
    assert_int_equal(rangeset_popcnt(rs), 0);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 0);
    rangeset_set(rs, 0, 4);
    assert_int_equal(rangeset_popcnt(rs), 5);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
    rangeset_set(rs, 10, 14);
    assert_int_equal(rangeset_popcnt(rs), 10);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 2);
    rangeset_set(rs, 20, 29);
    assert_int_equal(rangeset_popcnt(rs), 20);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 3);
}

void test_set_contained_range (void ** state) {
    rangeset* rs = rangeset_init();
    
    assert_int_equal(rangeset_popcnt(rs), 0);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 0);
    rangeset_set(rs, 10, 14);
    assert_int_equal(rangeset_popcnt(rs), 5);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
    rangeset_set(rs, 0, 24);
    assert_int_equal(rangeset_popcnt(rs), 25);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
}

void test_set_overlapping_range_end (void ** state) {
    rangeset* rs = rangeset_init();
    
    assert_int_equal(rangeset_popcnt(rs), 0);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 0);
    rangeset_set(rs, 10, 19);
    assert_int_equal(rangeset_popcnt(rs), 10);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
    rangeset_set(rs, 5, 14);
    assert_int_equal(rangeset_popcnt(rs), 15);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
}

void test_set_overlapping_range_start (void ** state) {
    rangeset* rs = rangeset_init();
    
    assert_int_equal(rangeset_popcnt(rs), 0);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 0);
    rangeset_set(rs, 5, 14);
    assert_int_equal(rangeset_popcnt(rs), 10);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
    rangeset_set(rs, 10, 19);
    assert_int_equal(rangeset_popcnt(rs), 15);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
}

void test_set_overlapping_range_both (void ** state) {
    rangeset* rs = rangeset_init();
    
    assert_int_equal(rangeset_popcnt(rs), 0);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 0);
    rangeset_set(rs, 5, 14);
    assert_int_equal(rangeset_popcnt(rs), 10);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
    rangeset_set(rs, 25, 34);
    assert_int_equal(rangeset_popcnt(rs), 20);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 2);
    rangeset_set(rs, 10, 30);
    assert_int_equal(rangeset_popcnt(rs), 30);
    assert_int_equal(list_tuple_i64_size(rs->on_ranges), 1);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_set_independent_ranges),
        cmocka_unit_test (test_set_contained_range),
        cmocka_unit_test (test_set_overlapping_range_end),
        cmocka_unit_test (test_set_overlapping_range_start),
        cmocka_unit_test (test_set_overlapping_range_both),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
 
 
