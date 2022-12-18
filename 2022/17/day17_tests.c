#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day17_impl.h"

char* testdata[1] = {
    ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>\n",
};


void test_day_17_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 1, &part1, &part2);
    assert_int_equal(part1, 3068);
    assert_int_equal(part2, 1514285714288);

}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_17_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
