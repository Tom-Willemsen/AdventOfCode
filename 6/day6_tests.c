#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day6_impl.h"

char* testdata= "3,4,3,1,2\n";

void test_day_6 (void ** state) {
    list_i64* initialstate = str_to_int64_list(testdata, ',');
    
    assert_int_equal(simulate(initialstate, 18), 26);
    assert_int_equal(simulate(initialstate, 80), 5934);
    assert_int_equal(simulate(initialstate, 256), 26984457539);
    
    list_i64_free(initialstate);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_6),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
