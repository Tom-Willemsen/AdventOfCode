#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day08_impl.h"

uint8_t l0[5] = {3,0,3,7,3};
uint8_t l1[5] = {2,5,5,1,2};
uint8_t l2[5] = {6,5,3,3,2};
uint8_t l3[5] = {3,3,5,4,9};
uint8_t l4[5] = {3,5,3,9,0};
uint8_t* testdata[5] = {l0,l1,l2,l3,l4};

void test_day_8 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 5, 5, &part1, &part2);
    assert_int_equal(part1, 21);
    assert_int_equal(part2, 8);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_8),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
