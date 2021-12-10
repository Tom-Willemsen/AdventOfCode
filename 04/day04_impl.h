#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "list.h"

const int64_t BOARD_SIZE = 5;

list_i64** load_boards(char** data, int64_t data_size, int64_t* n_boards);
void free_boards(list_i64** boards, int64_t n_boards);
int64_t sum_unmarked(list_i64* board, list_i64* numbers, int64_t n);
int64_t board_wins_after_n_numbers(list_i64* board, list_i64* numbers, int64_t n);
int64_t part1(list_i64** boards, int64_t n_boards, list_i64* numbers);
int64_t part2(list_i64** boards, int64_t n_boards, list_i64* numbers);
