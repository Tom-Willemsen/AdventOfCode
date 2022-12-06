#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day06_impl.h"

void test_day_6_ex1 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    
    char* test = "mjqjpqmgbljsphdztnvjfqwrcgsmlb";
    calculate(test, &part1, &part2);
    assert_int_equal(part1, 7);
    assert_int_equal(part2, 19);
}

void test_day_6_ex2 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    
    char* test = "bvwbjplbgvbhsrlpgdmjqwftvncz";
    calculate(test, &part1, &part2);
    assert_int_equal(part1, 5);
    assert_int_equal(part2, 23);
}

void test_day_6_ex3 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    
    char* test = "nppdvjthqldpwncqszvftbrmjlhg";
    calculate(test, &part1, &part2);
    assert_int_equal(part1, 6);
    assert_int_equal(part2, 23);
}

void test_day_6_ex4 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    
    char* test = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg";
    calculate(test, &part1, &part2);
    assert_int_equal(part1, 10);
    assert_int_equal(part2, 29);
}

void test_day_6_ex5 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    
    char* test = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
    calculate(test, &part1, &part2);
    assert_int_equal(part1, 11);
    assert_int_equal(part2, 26);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_6_ex1),
        cmocka_unit_test (test_day_6_ex2),
        cmocka_unit_test (test_day_6_ex3),
        cmocka_unit_test (test_day_6_ex4),
        cmocka_unit_test (test_day_6_ex5),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
