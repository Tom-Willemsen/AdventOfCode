#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day17_impl.h"

void test_day_17 (void ** state) {
//     int64_t part1, part2;
//     calculate("8A004A801A8002F478", &part1, &part2);
//     assert_int_equal(part1, 16);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_17),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
