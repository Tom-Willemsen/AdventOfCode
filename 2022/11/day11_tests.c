#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day11_impl.h"

char* testdata[27] = {
    "Monkey 0:\n",
    "  Starting items: 79, 98\n",
    "  Operation: new = old * 19\n",
    "  Test: divisible by 23\n",
    "    If true: throw to monkey 2\n",
    "    If false: throw to monkey 3\n",
    "\n",
    "Monkey 1:\n",
    "  Starting items: 54, 65, 75, 74\n",
    "  Operation: new = old + 6\n",
    "  Test: divisible by 19\n",
    "    If true: throw to monkey 2\n",
    "    If false: throw to monkey 0\n",
    "\n",
    "Monkey 2:\n",
    "  Starting items: 79, 60, 97\n",
    "  Operation: new = old * old\n",
    "  Test: divisible by 13\n",
    "    If true: throw to monkey 1\n",
    "    If false: throw to monkey 3\n",
    "\n",
    "Monkey 3:\n",
    "  Starting items: 74\n",
    "  Operation: new = old + 3\n",
    "  Test: divisible by 17\n",
    "    If true: throw to monkey 0\n",
    "    If false: throw to monkey 1\n",
};

void test_day_11 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 27, &part1, &part2);
    // assert_int_equal(part1, 10605);
    assert_int_equal(part2, 2713310158);
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
