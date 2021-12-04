#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"

const int64_t BOARD_SIZE = 5;

int64_t*** load_boards(char** data, int64_t data_size, int64_t* n_boards);
void free_boards(int64_t*** boards, int64_t n_boards);
int64_t sum_unmarked(int64_t** board_arr, int64_t* numbers, int64_t n_numbers);
int64_t board_wins_after_n_numbers(int64_t** board_arr, int64_t* numbers, int64_t n_numbers);
int64_t part1(int64_t*** boards, int64_t n_boards, int64_t* numbers, int64_t n_numbers);
int64_t part2(int64_t*** boards, int64_t n_boards, int64_t* bingo_numbers, int64_t n_bingo_numbers);
