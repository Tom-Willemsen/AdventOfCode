#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day15_impl.h"

uint8_t l0[10] = {1,1,6,3,7,5,1,7,4,2};
uint8_t l1[10] = {1,3,8,1,3,7,3,6,7,2};
uint8_t l2[10] = {2,1,3,6,5,1,1,3,2,8};
uint8_t l3[10] = {3,6,9,4,9,3,1,5,6,9};
uint8_t l4[10] = {7,4,6,3,4,1,7,1,1,1};
uint8_t l5[10] = {1,3,1,9,1,2,8,1,3,7};
uint8_t l6[10] = {1,3,5,9,9,1,2,4,2,1};
uint8_t l7[10] = {3,1,2,5,4,2,1,6,3,9};
uint8_t l8[10] = {1,2,9,3,1,3,8,5,2,1};
uint8_t l9[10] = {2,3,1,1,9,4,4,5,8,1};
uint8_t* testdata[10] = {l0,l1,l2,l3,l4,l5,l6,l7,l8,l9};


void test_day_15 (void ** state) {
    int64_t part1 = 0, part2 = 0;
    calculate(testdata, 10, 10, &part1, &part2);
    assert_int_equal(part1, 40);
    assert_int_equal(part2, 315);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_15),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
