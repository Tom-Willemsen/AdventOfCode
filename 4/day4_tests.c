#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day4_impl.h"

char* data[20] = {
    "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1\n",
    "\n",
    "22 13 17 11  0\n",
    " 8  2 23  4 24\n",
    "21  9 14 16  7\n",
    " 6 10  3 18  5\n",
    " 1 12 20 15 19\n",
    "\n",
    " 3 15  0  2 22\n",
    " 9 18 13 17  5\n",
    "19  8  7 25 23\n",
    "20 11 10 24  4\n",
    "14 21 16 12  6\n",
    "\n",
    "14 21 17 24  4\n",
    "10 16 15  9 19\n",
    "18  8 23 26 20\n",
    "22 11 13  6  5\n",
    " 2  0 12  3  7\n",
    "\n",
};

char* simpledata[8] = {
    "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25\n",
    "\n",
    "1 2 3 4 5\n",
    "6 7 8 9 10\n",
    "11 12 13 14 15\n",
    "16 17 18 19 20\n",
    "21 22 23 24 25\n",
    "\n",
};

void test_part_1 (void ** state) {
    int64_t n_boards = 3;
    list_i64** boards = load_boards(data, 20, &n_boards);
    list_i64* numbers = str_to_int64_list(data[0], ',');
    
    assert_int_equal(part1(boards, n_boards, numbers), 4512);
    
    free_boards(boards, n_boards);
    list_i64_free(numbers);
}

void test_board_wins_afer_n_numbers (void ** state) {
    int64_t n_boards = 1;
    list_i64** boards = load_boards(simpledata, 8, &n_boards);
    list_i64* numbers = str_to_int64_list(simpledata[0], ',');
    
    assert_int_equal(board_wins_after_n_numbers(boards[0], numbers, 3), 0);
    assert_int_equal(board_wins_after_n_numbers(boards[0], numbers, 4), 1);
    
    free_boards(boards, n_boards);
    list_i64_free(numbers);
}

void test_sum_unmarked (void ** state) {
    int64_t n_boards = 1;
    list_i64** boards = load_boards(simpledata, 8, &n_boards);
    list_i64* numbers = str_to_int64_list(simpledata[0], ',');
    
    assert_int_equal(sum_unmarked(boards[0], numbers, 4), 310);
    
    free_boards(boards, n_boards);
    list_i64_free(numbers);
}

void test_part_2 (void ** state) {
    int64_t n_boards = 3;
    list_i64** boards = load_boards(data, 20, &n_boards);
    list_i64* numbers = str_to_int64_list(data[0], ',');
    
    assert_int_equal(part2(boards, n_boards, numbers), 1924);
    
    free_boards(boards, n_boards);
    list_i64_free(numbers);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_board_wins_afer_n_numbers),
        cmocka_unit_test (test_sum_unmarked),
        cmocka_unit_test (test_part_1),
        cmocka_unit_test (test_part_2),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
