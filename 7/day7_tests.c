#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day7_impl.h"

char* testdata= "16,1,2,0,4,2,7,1,2,14\n";

void test_part_1 (void ** state) {
    list_i64* positions = str_to_int64_list(testdata, ',');
    assert_int_equal(part1(positions), 37);
    list_i64_free(positions);
}

void test_part_2 (void ** state) {
    list_i64* positions = str_to_int64_list(testdata, ',');
    assert_int_equal(part2(positions), 168);
    list_i64_free(positions);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_part_1),
        cmocka_unit_test (test_part_2),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
