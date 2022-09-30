#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day12_impl.h"

char* testdata_ex1[7] = {
    "start-A",
    "start-b",
    "A-c",
    "A-b",
    "b-d",
    "A-end",
    "b-end",
};

char* testdata_ex2[10] = {
    "dc-end",
    "HN-start",
    "start-kj",
    "dc-start",
    "dc-HN",
    "LN-dc",
    "HN-end",
    "kj-sa",
    "kj-HN",
    "kj-dc",
};

char* testdata_ex3[18] = {
    "fs-end",
    "he-DX",
    "fs-he",
    "start-DX",
    "pj-DX",
    "end-zg",
    "zg-sl",
    "zg-pj",
    "pj-he",
    "RW-he",
    "fs-DX",
    "pj-RW",
    "zg-RW",
    "start-pj",
    "he-WI",
    "zg-he",
    "pj-fs",
    "start-RW",
};

void test_day_12_ex1 (void ** state) {
    int64_t part1 = 0, part2 = 0;
    calculate(testdata_ex1, 7, &part1, &part2);
    assert_int_equal(part1, 10);
    assert_int_equal(part2, 36);
}

void test_day_12_ex2 (void ** state) {
    int64_t part1 = 0, part2 = 0;
    calculate(testdata_ex2, 10, &part1, &part2);
    assert_int_equal(part1, 19);
    assert_int_equal(part2, 103);
}

void test_day_12_ex3 (void ** state) {
    int64_t part1 = 0, part2 = 0;
    calculate(testdata_ex3, 18, &part1, &part2);
    assert_int_equal(part1, 226);
    assert_int_equal(part2, 3509);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_12_ex1),
        cmocka_unit_test (test_day_12_ex2),
        cmocka_unit_test (test_day_12_ex3),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
