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

char* realdata[56] = {
    "Monkey 0:\n",
    "  Starting items: 89, 74\n",
    "  Operation: new = old * 5\n",
    "  Test: divisible by 17\n",
    "    If true: throw to monkey 4\n",
    "    If false: throw to monkey 7\n",
    "\n",
    "Monkey 1:\n",
    "  Starting items: 75, 69, 87, 57, 84, 90, 66, 50\n",
    "  Operation: new = old + 3\n",
    "  Test: divisible by 7\n",
    "    If true: throw to monkey 3\n",
    "    If false: throw to monkey 2\n",
    "\n",
    "Monkey 2:\n",
    "  Starting items: 55\n",
    "  Operation: new = old + 7\n",
    "  Test: divisible by 13\n",
    "    If true: throw to monkey 0\n",
    "    If false: throw to monkey 7\n",
    "\n",
    "Monkey 3:\n",
    "  Starting items: 69, 82, 69, 56, 68\n",
    "  Operation: new = old + 5\n",
    "  Test: divisible by 2\n",
    "    If true: throw to monkey 0\n",
    "    If false: throw to monkey 2\n",
    "\n",
    "Monkey 4:\n",
    "  Starting items: 72, 97, 50\n",
    "  Operation: new = old + 2\n",
    "  Test: divisible by 19\n",
    "    If true: throw to monkey 6\n",
    "    If false: throw to monkey 5\n",
    "\n",
    "Monkey 5:\n",
    "  Starting items: 90, 84, 56, 92, 91, 91\n",
    "  Operation: new = old * 19\n",
    "  Test: divisible by 3\n",
    "    If true: throw to monkey 6\n",
    "    If false: throw to monkey 1\n",
    "\n",
    "Monkey 6:\n",
    "  Starting items: 63, 93, 55, 53\n",
    "  Operation: new = old * old\n",
    "  Test: divisible by 5\n",
    "    If true: throw to monkey 3\n",
    "    If false: throw to monkey 1\n",
    "\n",
    "Monkey 7:\n",
    "  Starting items: 50, 61, 52, 58, 86, 68, 97\n",
    "  Operation: new = old + 4\n",
    "  Test: divisible by 11\n",
    "    If true: throw to monkey 5\n",
    "    If false: throw to monkey 4\n",
    "\n"
};

void test_day_11_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 27, &part1, &part2);
    assert_int_equal(part1, 10605);
    assert_int_equal(part2, 2713310158);
}

void test_day_11_real (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(realdata, 56, &part1, &part2);
    assert_int_equal(part1, 120056);
    assert_int_equal(part2, 21816744824);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_11_ex),
        cmocka_unit_test (test_day_11_real),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
