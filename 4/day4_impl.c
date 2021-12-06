#include "day4_impl.h"

list_i64** load_boards(char** data, int64_t data_size, int64_t* n_boards) {
    int64_t start_line;
    list_i64* board_ll;
    
    *n_boards = (data_size - 1) / (BOARD_SIZE + 1);
    list_i64** boards = calloc(*n_boards, sizeof(list_i64 *));
    
    for (int64_t board=0; board<*n_boards; ++board) {
        start_line = 2 + (BOARD_SIZE + 1) * board;
        
        board_ll = list_i64_init(BOARD_SIZE * BOARD_SIZE);
        
        for (int64_t row = 0; row<BOARD_SIZE; ++row) {
            board_ll = list_i64_merge(board_ll, str_to_int64_list(data[start_line + row], ' '));
        }
        assert(board_ll->size == BOARD_SIZE * BOARD_SIZE);
        boards[board] = board_ll;
    }
    
    return boards;
}

int board_get(list_i64* board, int64_t row, int64_t col) {
    return list_i64_get(board, row * BOARD_SIZE + col);
}

void free_boards(list_i64** boards, int64_t n_boards) {
    for (int64_t i=0; i<n_boards; ++i) {
        list_i64_free(boards[i]);
    }
    free(boards);
}

int64_t sum_unmarked(list_i64* board, list_i64* numbers, int64_t n) {
    int64_t result = 0, index, value;
    for (uint64_t i=0; i<board->size; ++i) {
        value = list_i64_get(board, i);
        index = list_i64_indexof(numbers, value);
        if (index > n && index != -1) {
            result += value;
        }
    }
    return result;
}

int64_t board_wins_after_n_numbers(list_i64* board, list_i64* numbers, int64_t n) {
    int64_t winning = 0,index;
    
    // check rows
    for (int64_t row=0; row<BOARD_SIZE; ++row) {
        winning = 1;
        for (int64_t col=0; col<BOARD_SIZE; ++col) {
            index = list_i64_indexof(numbers, board_get(board, row, col));
            winning = winning && (index <= n) && (index != -1);
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
            index = list_i64_indexof(numbers, board_get(board, row, col));
            winning = winning && (index <= n) && (index != -1);
            if (!winning) break;
        }
        if (winning) {
            return 1;
        }
    }
    
    return 0;
}

int64_t part1(list_i64** boards, int64_t n_boards, list_i64* numbers) {
    for (int64_t i=0; i<numbers->size; ++i) {
        for (int64_t board=0; board<n_boards; ++board) {
            if (board_wins_after_n_numbers(boards[board], numbers, i)) {
                return sum_unmarked(boards[board], numbers, i) * list_i64_get(numbers, i);
            }
        }
    }
    return -1;
}

int64_t part2(list_i64** boards, int64_t n_boards, list_i64* numbers) {
    int64_t latest_win = 0, ret = -1;
    for (int64_t board=0; board<n_boards; ++board) {
        for (int64_t i=latest_win+1; i<numbers->size; ++i) {
            if (!board_wins_after_n_numbers(boards[board], numbers, i-1) && 
                board_wins_after_n_numbers(boards[board], numbers, i)) {
                
                latest_win = i;
                ret = sum_unmarked(boards[board], numbers, i) * list_i64_get(numbers, i);
                break;
            }
        }
    }
    return ret;
}
