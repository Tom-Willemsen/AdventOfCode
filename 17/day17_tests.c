#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day17_impl.h"

void test_day_17 (void ** state) {
    int64_t part1, part2;
    calculate("target area: x=20..30, y=-10..-5", &part1, &part2);
    assert_int_equal(part1, 45);
    assert_int_equal(part2, 112);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_17),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
