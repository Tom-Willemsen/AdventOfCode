#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day17_impl.h"

void test_day_17_ex1 (void ** state) {
    int64_t part1, part2;
    calculate("target area: x=20..30, y=-10..-5", &part1, &part2);
    assert_int_equal(part1, 45);
    assert_int_equal(part2, 112);
}

void test_day_17_ex2 (void ** state) {
    int64_t part1, part2;
    calculate("target area: x=25..67, y=-260..-200", &part1, &part2);
    assert_int_equal(part1, 33670);
    assert_int_equal(part2, 4903);
}

void test_day_17_ex3 (void ** state) {
    int64_t part1, part2;
    calculate("target area: x=352..377, y=-49..-30", &part1, &part2);
    assert_int_equal(part1, 66);  // not 1176!
    assert_int_equal(part2, 820);
}

void test_day_17_ex4 (void ** state) {
    int64_t part1, part2;
    calculate("target area: x=819..820, y=-11..-5", &part1, &part2);
    assert_int_equal(part1, 36);  // not 66!
    assert_int_equal(part2, 27);
}

void test_day_17_minimal_1 (void ** state) {
    int64_t part1, part2;
    calculate("target area: x=3..3, y=-3..-3", &part1, &part2);
    assert_int_equal(part1, 3);
    assert_int_equal(part2, 4);
}

void test_day_17_minimal_2 (void ** state) {
    int64_t part1, part2;
    calculate("target area: x=2..2, y=-2..-2", &part1, &part2);
    assert_int_equal(part1, 0);
    assert_int_equal(part2, 1);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_17_ex1),
        cmocka_unit_test (test_day_17_ex2),
        cmocka_unit_test (test_day_17_ex3),
        cmocka_unit_test (test_day_17_ex4),
        cmocka_unit_test (test_day_17_minimal_1),
        cmocka_unit_test (test_day_17_minimal_2),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
