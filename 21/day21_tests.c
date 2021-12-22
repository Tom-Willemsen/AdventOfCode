#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day21_impl.h"

char* testdata[2] = {
    "Player 1 starting position: 4\n",
    "Player 2 starting position: 8\n",
};

void test_day_21 (void ** state) {
    int64_t part1 = 0, part2 = 0;
    calculate(testdata, 2, &part1, &part2);
    assert_int_equal(part1, 739785);
    assert_int_equal(part2, 444356092776315);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_21),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
