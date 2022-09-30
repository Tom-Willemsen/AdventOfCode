#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day23_impl.h"


void test_day_23 (void ** state) {
    
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_23),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
