#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day03_impl.h"

char* testdata[6] = {
    "vJrwpWtwJgWrhcsFMMfFFhFp\n",
    "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n",
    "PmmdzqPrVvPwwTWBwg\n",
    "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n",
    "ttgJtRGJQctTZtZT\n",
    "CrZsJsPPZsGzwwsLwLmpwMDw\n"
};

void test_day_2 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 6, &part1, &part2);
    assert_int_equal(part1, 157);
    assert_int_equal(part2, 70);
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
