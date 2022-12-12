#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day12_impl.h"

char* testdata[5] = {
    "Sabqponm\n",
    "abcryxxl\n",
    "accszExk\n",
    "acctuvwj\n",
    "abdefghi\n",
};


void test_day_12_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 5, &part1, &part2);
    assert_int_equal(part1, 31);
    assert_int_equal(part2, 29);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_12_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
