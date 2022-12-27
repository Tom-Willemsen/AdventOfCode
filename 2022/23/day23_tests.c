#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day23_impl.h"

char* testdata[7] = {
    "....#..\n",
    "..###.#\n",
    "#...#.#\n",
    ".#...##\n",
    "#.###..\n",
    "##.#.##\n",
    ".#..#..\n",
};

void test_day_23_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 7, &part1, &part2);
    assert_int_equal(part1, 110);
    assert_int_equal(part2, 20);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_23_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
