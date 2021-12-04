#include "day4_impl.h"

ll_i64** load_boards(char** data, int64_t data_size, int64_t* n_boards) {
    int64_t start_line;
    ll_i64* board_ll;
    
    *n_boards = (data_size - 1) / (BOARD_SIZE + 1);
    ll_i64** boards = calloc(*n_boards, sizeof(ll_i64 *));
    
    for (int64_t board=0; board<*n_boards; ++board) {
        start_line = 2 + (BOARD_SIZE + 1) * board;
        
        board_ll = ll_i64_init();
        
        for (int64_t row = 0; row<BOARD_SIZE; ++row) {
            board_ll = ll_i64_merge(board_ll, str_to_int64_ll(data[start_line + row], ' '));
        }
        assert(board_ll->size == BOARD_SIZE * BOARD_SIZE);
        boards[board] = board_ll;
    }
    
    return boards;
}

int board_get(ll_i64* board, int64_t row, int64_t col) {
    return ll_i64_get(board, row * BOARD_SIZE + col);
}

void free_boards(ll_i64** boards, int64_t n_boards) {
    for (int64_t i=0; i<n_boards; ++i) {
        ll_i64_free(boards[i]);
    }
    free(boards);
}

int64_t sum_unmarked(ll_i64* board, ll_i64* numbers, int64_t n) {
    int64_t result = 0, index, value;
    ll_i64_node* it = ll_i64_it(board);
    while (ll_i64_next(&it, &value)) {
        index = ll_i64_indexof(numbers, value);
        if (index > n && index != -1) {
            result += value;
        }
    }
    return result;
}

int64_t board_wins_after_n_numbers(ll_i64* board, ll_i64* numbers, int64_t n) {
    int64_t winning = 0,index;
    
    // check rows
    for (int64_t row=0; row<BOARD_SIZE; ++row) {
        winning = 1;
        for (int64_t col=0; col<BOARD_SIZE; ++col) {
            index = ll_i64_indexof(numbers, board_get(board, row, col));
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
            index = ll_i64_indexof(numbers, board_get(board, row, col));
            winning = winning && (index <= n) && (index != -1);
            if (!winning) break;
        }
        if (winning) {
            return 1;
        }
    }
    
    return 0;
}

int64_t part1(ll_i64** boards, int64_t n_boards, ll_i64* numbers) {
    for (int64_t i=0; i<numbers->size; ++i) {
        for (int64_t board=0; board<n_boards; ++board) {
            if (board_wins_after_n_numbers(boards[board], numbers, i)) {
                return sum_unmarked(boards[board], numbers, i) * ll_i64_get(numbers, i);
            }
        }
    }
    return -1;
}

int64_t part2(ll_i64** boards, int64_t n_boards, ll_i64* numbers) {
    int64_t latest_win = 0, ret = -1;
    for (int64_t board=0; board<n_boards; ++board) {
        for (int64_t i=latest_win+1; i<numbers->size; ++i) {
            if (!board_wins_after_n_numbers(boards[board], numbers, i-1) && 
                board_wins_after_n_numbers(boards[board], numbers, i)) {
                
                latest_win = i;
                ret = sum_unmarked(boards[board], numbers, i) * ll_i64_get(numbers, i);
                break;
            }
        }
    }
    return ret;
}
