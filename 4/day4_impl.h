#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "linked_list.h"

const int64_t BOARD_SIZE = 5;

ll_i64** load_boards(char** data, int64_t data_size, int64_t* n_boards);
void free_boards(ll_i64** boards, int64_t n_boards);
int64_t sum_unmarked(ll_i64* board, ll_i64* numbers, int64_t n);
int64_t board_wins_after_n_numbers(ll_i64* board, ll_i64* numbers, int64_t n);
int64_t part1(ll_i64** boards, int64_t n_boards, ll_i64* numbers);
int64_t part2(ll_i64** boards, int64_t n_boards, ll_i64* numbers);
