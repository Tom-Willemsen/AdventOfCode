#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day04_impl.h"

char* testdata[6] = {
    "2-4,6-8\n",
    "2-3,4-5\n",
    "5-7,7-9\n",
    "2-8,3-7\n",
    "6-6,4-6\n",
    "2-6,4-8\n"
};

void test_day_4 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 6, &part1, &part2);
    assert_int_equal(part1, 2);
    assert_int_equal(part2, 4);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_4),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
