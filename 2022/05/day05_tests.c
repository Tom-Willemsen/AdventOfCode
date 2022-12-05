#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day05_impl.h"

char* testdata[9] = {
    "    [D]    \n",
    "[N] [C]    \n",
    "[Z] [M] [P]\n",
    " 1   2   3 \n",
    "\n",
    "move 1 from 2 to 1\n",
    "move 3 from 1 to 3\n",
    "move 2 from 2 to 1\n",
    "move 1 from 1 to 2\n"
};

void test_day_5 (void ** state) {
    char* part1 = NULL;
    char* part2 = NULL;
    calculate(testdata, 9, &part1, &part2);
    assert_string_equal("CMZ", part1);
    assert_string_equal("MCD", part2);
    free(part1);
    free(part2);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_5),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
