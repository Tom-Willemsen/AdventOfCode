#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day09_impl.h"

char* testdata_p1[8] = {
    "R 4\n",
    "U 4\n",
    "L 3\n",
    "D 1\n",
    "R 4\n",
    "D 1\n",
    "L 5\n",
    "R 2\n"
};

char* testdata_p2[8] = {
    "R 5\n",
    "U 8\n",
    "L 8\n",
    "D 3\n",
    "R 17\n",
    "D 10\n",
    "L 25\n",
    "U 20\n"
};

void test_day_9_p1 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata_p1, 8, &part1, &part2);
    assert_int_equal(part1, 13);
    assert_int_equal(part2, 1);
}

void test_day_9_p2 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata_p2, 8, &part1, &part2);
    assert_int_equal(part1, 88);
    assert_int_equal(part2, 36);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_9_p1),
        cmocka_unit_test (test_day_9_p2),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
