#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day01_impl.h"

char* testdata[14] = {
    "1000\n",
    "2000\n",
    "3000\n",
    "\n",
    "4000\n",
    "\n",
    "5000\n",
    "6000\n",
    "\n",
    "7000\n",
    "8000\n",
    "9000\n",
    "\n",
    "10000\n"
};

void test_day_1 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 14, &part1, &part2);
    assert_int_equal(part1, 24000);
    assert_int_equal(part2, 45000);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_1),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
