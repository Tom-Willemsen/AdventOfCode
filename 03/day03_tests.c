#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day03_impl.h"

char* data[12] = {
    "00100\n",
    "11110\n",
    "10110\n",
    "10111\n",
    "10101\n",
    "01111\n",
    "00111\n",
    "11100\n",
    "10000\n",
    "11001\n",
    "00010\n",
    "01010\n",
};

void test_part_1 (void ** state) {
    assert_int_equal(part1(data, 12), 198);
}

void test_part_2 (void ** state) {
    assert_int_equal(part2(data, 12, 0) * part2(data, 12, 1), 230);
}


int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_part_1),
        cmocka_unit_test (test_part_2),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
