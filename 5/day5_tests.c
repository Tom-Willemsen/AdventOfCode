#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day5_impl.h"

char* testdata[10] = {
    "0,9 -> 5,9",
    "8,0 -> 0,8",
    "9,4 -> 3,4",
    "2,2 -> 2,1",
    "7,0 -> 7,4",
    "6,4 -> 2,0",
    "0,9 -> 2,9",
    "3,4 -> 1,4",
    "0,0 -> 8,8",
    "5,5 -> 8,2",
};

void test_day_5 (void ** state) {
    int64_t** points = parse_points(testdata, 10);
    int64_t max_x = 10, max_y = 10;
    
    int64_t** array = calloc(max_y, sizeof(int64_t*));
    for (int64_t i=0; i<max_y; ++i) {
        array[i] = calloc(max_x, sizeof(int64_t));
    }
    
    mark_straight(array, points, 10);
    int64_t part1 = count_gt_2(array, max_x, max_y);
    mark_diagonal(array, points, 10);
    int64_t part2 = count_gt_2(array, max_x, max_y);
    
    assert_int_equal(part1, 5);
    assert_int_equal(part2, 12);
    
    for (int64_t i=0; i<max_y; ++i) {
        free(array[i]);
    }
    free(array);
    for (int64_t i=0; i<10; ++i) {
        free(points[i]);
    }
    free(points);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_5),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
