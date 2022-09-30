#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day09_impl.h"

uint8_t l1[10] = {2,1,9,9,9,4,3,2,1,0};
uint8_t l2[10] = {3,9,8,7,8,9,4,9,2,1};
uint8_t l3[10] = {9,8,5,6,7,8,9,8,9,2};
uint8_t l4[10] = {8,7,6,7,8,9,6,7,8,9};
uint8_t l5[10] = {9,8,9,9,9,6,5,6,7,8};
uint8_t* testdata[5] = {l1, l2, l3, l4, l5};

void test_day_9 (void ** state) {
    int64_t part1, part2;
    calculate(testdata, 5, 10, &part1, &part2);
    assert_int_equal(part1, 15);
    assert_int_equal(part2, 1134);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_9),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
