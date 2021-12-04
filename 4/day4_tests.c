#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day4_impl.h"

void test_part_1 (void ** state) {
    assert_true(1);
}

void test_part_2 (void ** state) {
    assert_true(1);
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
