#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day14_impl.h"

char* testdata[2] = {
    "498,4 -> 498,6 -> 496,6\n",
    "503,4 -> 502,4 -> 502,9 -> 494,9\n",
};


void test_day_14_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 2, &part1, &part2);
    assert_int_equal(part1, 24);
    assert_int_equal(part2, 93);
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
