#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day24_impl.h"

char* testdata[6] = {
    "#.######\n",
    "#>>.<^<#\n",
    "#.<..<<#\n",
    "#>v.><>#\n",
    "#<^v^^>#\n",
    "######.#\n",
};

void test_day_24_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 6, &part1, &part2);
    assert_int_equal(part1, 18);
    assert_int_equal(part2, 54);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_24_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
