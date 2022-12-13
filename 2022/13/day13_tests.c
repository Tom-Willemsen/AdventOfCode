#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day13_impl.h"

char* testdata[23] = {
    "[1,1,3,1,1]\n",
    "[1,1,5,1,1]\n",
    "\n",
    "[[1],[2,3,4]]\n",
    "[[1],4]\n",
    "\n",
    "[9]\n",
    "[[8,7,6]]\n",
    "\n",
    "[[4,4],4,4]\n",
    "[[4,4],4,4,4]\n",
    "\n",
    "[7,7,7,7]\n",
    "[7,7,7]\n",
    "\n",
    "[]\n",
    "[3]\n",
    "\n",
    "[[[]]]\n",
    "[[]]\n",
    "\n",
    "[1,[2,[3,[4,[5,6,7]]]],8,9]\n",
    "[1,[2,[3,[4,[5,6,0]]]],8,9]\n",
};


void test_day_13_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 23, &part1, &part2);
    assert_int_equal(part1, 13);
    assert_int_equal(part2, 140);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_13_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
