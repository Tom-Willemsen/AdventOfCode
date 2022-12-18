#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day18_impl.h"

char* testdata[13] = {
    "2,2,2\n",
    "1,2,2\n",
    "3,2,2\n",
    "2,1,2\n",
    "2,3,2\n",
    "2,2,1\n",
    "2,2,3\n",
    "2,2,4\n",
    "2,2,6\n",
    "1,2,5\n",
    "3,2,5\n",
    "2,1,5\n",
    "2,3,5\n",
};


void test_day_18_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 13, &part1, &part2);
    assert_int_equal(part1, 64);
    assert_int_equal(part2, 58);

}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_18_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
