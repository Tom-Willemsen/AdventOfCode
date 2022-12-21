#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day21_impl.h"

char* testdata[15] = {
    "root: pppw + sjmn\n",
    "dbpl: 5\n",
    "cczh: sllz + lgvd\n",
    "zczc: 2\n",
    "ptdq: humn - dvpt\n",
    "dvpt: 3\n",
    "lfqf: 4\n",
    "humn: 5\n",
    "ljgn: 2\n",
    "sjmn: drzm * dbpl\n",
    "sllz: 4\n",
    "pppw: cczh / lfqf\n",
    "lgvd: ljgn * ptdq\n",
    "drzm: hmdt - zczc\n",
    "hmdt: 32\n",
};


void test_day_21_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 15, &part1, &part2);
    assert_int_equal(part1, 152);
    assert_int_equal(part2, 301);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_21_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
