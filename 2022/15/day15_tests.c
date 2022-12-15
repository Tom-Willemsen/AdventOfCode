#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day15_impl.h"

char* testdata[14] = {
    "Sensor at x=2, y=18: closest beacon is at x=-2, y=15\n",
    "Sensor at x=9, y=16: closest beacon is at x=10, y=16\n",
    "Sensor at x=13, y=2: closest beacon is at x=15, y=3\n",
    "Sensor at x=12, y=14: closest beacon is at x=10, y=16\n",
    "Sensor at x=10, y=20: closest beacon is at x=10, y=16\n",
    "Sensor at x=14, y=17: closest beacon is at x=10, y=16\n",
    "Sensor at x=8, y=7: closest beacon is at x=2, y=10\n",
    "Sensor at x=2, y=0: closest beacon is at x=2, y=10\n",
    "Sensor at x=0, y=11: closest beacon is at x=2, y=10\n",
    "Sensor at x=20, y=14: closest beacon is at x=25, y=17\n",
    "Sensor at x=17, y=20: closest beacon is at x=21, y=22\n",
    "Sensor at x=16, y=7: closest beacon is at x=15, y=3\n",
    "Sensor at x=14, y=3: closest beacon is at x=15, y=3\n",
    "Sensor at x=20, y=1: closest beacon is at x=15, y=3\n",
};


void test_day_14_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 14, &part1, &part2, 10, 20);
    assert_int_equal(part1, 26);
    assert_int_equal(part2, 56000011);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_14_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
