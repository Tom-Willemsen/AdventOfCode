#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day11_impl.h"

uint8_t l0[10] = {5,4,8,3,1,4,3,2,2,3};
uint8_t l1[10] = {2,7,4,5,8,5,4,7,1,1};
uint8_t l2[10] = {5,2,6,4,5,5,6,1,7,3};
uint8_t l3[10] = {6,1,4,1,3,3,6,1,4,6};
uint8_t l4[10] = {6,3,5,7,3,8,5,4,7,8};
uint8_t l5[10] = {4,1,6,7,5,2,4,6,4,5};
uint8_t l6[10] = {2,1,7,6,8,4,1,7,2,1};
uint8_t l7[10] = {6,8,8,2,8,8,1,1,3,4};
uint8_t l8[10] = {4,8,4,6,8,4,8,5,5,4};
uint8_t l9[10] = {5,2,8,3,7,5,1,5,2,6};
uint8_t* testdata[10] = {l0,l1,l2,l3,l4,l5,l6,l7,l8,l9};

void test_day_11 (void ** state) {
    int64_t part1 = 0, part2 = 0;
    calculate(testdata, 10, 10, &part1, &part2);
    assert_int_equal(part1, 1656);
    assert_int_equal(part2, 195);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_11),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
