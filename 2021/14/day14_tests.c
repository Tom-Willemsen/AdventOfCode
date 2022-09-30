#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day14_impl.h"

char* testdata[18] = {
    "NNCB\n",
    "\n",
    "CH -> B\n",
    "HH -> N\n",
    "CB -> H\n",
    "NH -> C\n",
    "HB -> C\n",
    "HC -> B\n",
    "HN -> C\n",
    "NN -> C\n",
    "BH -> H\n",
    "NC -> B\n",
    "NB -> B\n",
    "BN -> B\n",
    "BB -> N\n",
    "BC -> B\n",
    "CC -> N\n",
    "CN -> C\n",
};


void test_day_14 (void ** state) {
    int64_t part1 = 0, part2 = 0;
    calculate(testdata, 18, &part1, &part2);
    assert_int_equal(part1, 1588);
    assert_int_equal(part2, 2188189693529);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_14),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
