#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day20_impl.h"

char* testdata[7] = {
    "1\n",
    "2\n",
    "-3\n",
    "3\n",
    "-2\n",
    "0\n",
    "4\n",
};


void test_day_20_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 7, &part1, &part2);
    assert_int_equal(part1, 3);
    assert_int_equal(part2, 1623178306);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_20_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
