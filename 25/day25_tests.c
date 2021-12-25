#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day25_impl.h"

char* testdata[9] = {
    "v...>>.vv>\n",
    ".vv>>.vv..\n",
    ">>.>v>...v\n",
    ">>v>>.>.v.\n",
    "v>v.vv.v..\n",
    ">.>>..v...\n",
    ".vv..>.>v.\n",
    "v.v..>>v.v\n",
    "....v..v.>\n", 
};

void test_day_25 (void ** state) {
    int64_t part1 = 0;
    calculate(testdata, 9, &part1);
    assert_int_equal(part1, 58);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_25),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
