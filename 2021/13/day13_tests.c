#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day13_impl.h"

char* testdata_ex1[21] = {
    "6,10",
    "0,14",
    "9,10",
    "0,3",
    "10,4",
    "4,11",
    "6,0",
    "6,12",
    "4,1",
    "0,13",
    "10,12",
    "3,4",
    "3,0",
    "8,4",
    "1,10",
    "2,14",
    "8,10",
    "9,0",
    "",
    "fold along y=7",
    "fold along x=5",
};

void test_day_13 (void ** state) {
    int64_t part1 = 0;
    char* part2 = NULL;
    calculate(testdata_ex1, 21, &part1, &part2);
    assert_int_equal(part1, 17);
    assert_string_equal(part2, "[notset]");
    free(part2);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_13),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
