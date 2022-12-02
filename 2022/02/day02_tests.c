#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day02_impl.h"

char* testdata[3] = {
    "A Y\n",
    "B X\n",
    "C Z\n"
};

void test_day_2 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 3, &part1, &part2);
    assert_int_equal(part1, 15);
    assert_int_equal(part2, 12);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_2),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
