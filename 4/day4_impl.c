#include "day4_impl.h"

int64_t*** load_boards(char** data, int64_t data_size, int64_t* n_boards) {
    int64_t start_line;
    int64_t row_length;
    int64_t** board_arr;
    
    *n_boards = (data_size - 1) / (BOARD_SIZE + 1);
    int64_t*** boards = calloc(*n_boards, sizeof(int64_t **));
    
    for (int64_t board=0; board<*n_boards; ++board) {
        board_arr = calloc(BOARD_SIZE, sizeof(int64_t*));
        start_line = 2 + (BOARD_SIZE + 1) * board;
        
        for (int64_t row = 0; row<BOARD_SIZE; ++row) {
            board_arr[row] = str_to_int64_arr(data[start_line + row], ' ', &row_length);
            if (row_length != BOARD_SIZE) {
                puts("bad row length");
            }
        }
        boards[board] = board_arr;
    }
    
    return boards;
}

void free_boards(int64_t*** boards, int64_t n_boards) {
    for (int64_t i=0; i<n_boards; ++i) {
        for (int64_t row=0; row<BOARD_SIZE; ++row) {
            free(boards[i][row]);
        }
        free(boards[i]);
    }
    free(boards);
}

int64_t sum_unmarked(int64_t** board_arr, int64_t* numbers, int64_t n_numbers) {
    int64_t result = 0, is_marked = 0;
    for (int64_t col=0; col<BOARD_SIZE; ++col) {
        for (int64_t row=0; row<BOARD_SIZE; ++row) {
            is_marked = 0;
            for (int64_t bn = 0; bn < n_numbers; ++bn) {
                if (board_arr[row][col] == numbers[bn]) {
                    is_marked = 1;
                    break;
                }
            }
            if (!is_marked) {
                result += board_arr[row][col];
            }
        }
    }
    return result;
}

int64_t board_wins_after_n_numbers(int64_t** board_arr, int64_t* numbers, int64_t n_numbers) {
    int64_t winning = 0, contains_bn = 0;
    
    // check rows
    for (int64_t row=0; row<BOARD_SIZE; ++row) {
        winning = 1;
        for (int64_t col=0; col<BOARD_SIZE; ++col) {
            contains_bn = 0;
            for (int64_t bn = 0; bn < n_numbers; ++bn) {
                if (board_arr[row][col] == numbers[bn]) {
                    contains_bn = 1;
                    break;
                }
            }
            winning = winning && contains_bn;
            if (!winning) break;
        }
        if (winning) {
            return 1;
        }
    }
    
    // check cols
    for (int64_t col=0; col<BOARD_SIZE; ++col) {
        winning = 1;
        for (int64_t row=0; row<BOARD_SIZE; ++row) {
            contains_bn = 0;
            for (int64_t bn = 0; bn < n_numbers; ++bn) {
                if (board_arr[row][col] == numbers[bn]) {
                    contains_bn = 1;
                    break;
                }
            }
            winning = winning && contains_bn;
            if (!winning) break;
        }
        if (winning) {
            return 1;
        }
    }
    
    return 0;
}

int64_t part1(int64_t*** boards, int64_t n_boards, int64_t* numbers, int64_t n_numbers) {
    for (int64_t i=0; i<n_numbers; ++i) {
        for (int64_t board=0; board<n_boards; ++board) {
            if (board_wins_after_n_numbers(boards[board], numbers, i)) {
                return sum_unmarked(boards[board], numbers, i) * numbers[i-1];
            }
        }
    }
    return -1;
}

int64_t part2(int64_t*** boards, int64_t n_boards, int64_t* bingo_numbers, int64_t n_bingo_numbers) {
    int64_t latest_win = 0, ret = -1;
    for (int64_t board=0; board<n_boards; ++board) {
        for (int64_t i=latest_win+1; i<n_bingo_numbers; ++i) {
            if (!board_wins_after_n_numbers(boards[board], bingo_numbers, i-1) && 
                board_wins_after_n_numbers(boards[board], bingo_numbers, i)) {
                
                latest_win = i;
                ret = sum_unmarked(boards[board], bingo_numbers, i) * bingo_numbers[i-1];
                break;
            }
        }
    }
    return ret;
}
