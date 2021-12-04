#include "day4_impl.h"
#include "file_loading.h"


int64_t* str_to_int64_arr(char* data, char delim, uint64_t* n) {
    int64_t* ret = calloc(strlen(data), sizeof(int64_t));
    char* buffer = calloc(strlen(data) + 1, sizeof(char));
    uint64_t buffer_idx = 0;
    char c;
    
    *n = 0;
    for (uint64_t idx = 0; idx < strlen(data); ++idx) {
        c = data[idx];
        if (c == '\n' || (c == delim && buffer_idx > 0)) {
            ret[*n] = strtol(buffer, NULL, 10);
            (*n)++;
            for (uint64_t i=0; i<5; ++i) {
                buffer[i] = '\0';
            }
            buffer_idx = 0;
        } else {
            buffer[buffer_idx] = c;
            buffer_idx++;
        }
    }
    
    free(buffer);
    return ret;
}


uint64_t bingo_board_n_wins_after_n_numbers(char** data, uint64_t board, int64_t* numbers, uint64_t n, int64_t* sum_unmarked) {
    
    uint64_t start_line = 2 + 6 * board;
    uint64_t row_length;
    uint64_t winning = 0, contains_bn = 0, is_marked = 0;
    *sum_unmarked = 0;
    
    int64_t* board_arr[5];
    for (uint64_t i = 0; i<5; ++i) {
        board_arr[i] = str_to_int64_arr(data[start_line + i], ' ', &row_length);
        if (row_length != 5) {
            printf("problematic row length=%"PRIu64" board=%"PRIu64" (start_line %"PRIu64")\n", row_length, board, start_line);
        }
    }
    
    // check rows
    for (uint64_t row=0; row<5; ++row) {
        winning = 1;
        for (uint64_t col=0; col<5; ++col) {
            contains_bn = 0;
            for (uint16_t bn = 0; bn < n; ++bn) {
                if (board_arr[row][col] == numbers[bn]) {
                    contains_bn = 1;
                    break;
                }
            }
            winning = winning && contains_bn;
        }
        if (winning) {
            break;
        }
    }
    
    if (!winning) {
        // check cols
        for (uint64_t col=0; col<5; ++col) {
            winning = 1;
            for (uint64_t row=0; row<5; ++row) {
                contains_bn = 0;
                for (uint16_t bn = 0; bn < n; ++bn) {
                    if (board_arr[row][col] == numbers[bn]) {
                        contains_bn = 1;
                        break;
                    }
                }
                winning = winning && contains_bn;
            }
            if (winning) {
                break;
            }
        }
    }
    
    if(winning) {
        for (uint64_t col=0; col<5; ++col) {
            for (uint64_t row=0; row<5; ++row) {
                is_marked = 0;
                for (uint16_t bn = 0; bn < n; ++bn) {
                    if (board_arr[row][col] == numbers[bn]) {
                        is_marked = 1;
                        break;
                    }
                }
                if (!is_marked) {
                    (*sum_unmarked) += board_arr[row][col];
                }
            }
        }
    }
    
    for (uint64_t i = 0; i<5; ++i) {
        free(board_arr[i]);
    }
    
    return winning;
}


int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    char** data = load_file_as_str_arr(fptr, &data_size);
    
    uint64_t n_bingo_numbers = 0;
    int64_t* bingo_numbers = str_to_int64_arr(data[0], ',', &n_bingo_numbers);
    int64_t sum_unmarked = 0, part1 = 0, part2 = 0, latest_win = 1, has_winner = 0;
    
    for (uint64_t i=0; i<n_bingo_numbers; ++i) {
        for (uint64_t board=0; board<100; ++board) {
            if (bingo_board_n_wins_after_n_numbers(data, board, bingo_numbers, i, &sum_unmarked)) {
                printf("Board %"PRIu64" has won (just drawn: %"PRId64")\n", board, bingo_numbers[i-1]);
                has_winner = 1;
                part1 = sum_unmarked * bingo_numbers[i-1];
                break;
            }
        }
        if(has_winner) {
            break;
        }
    }
    
    for (uint64_t board=0; board<100; ++board) {
        for (uint64_t i=latest_win; i<n_bingo_numbers; ++i) {
            if (!bingo_board_n_wins_after_n_numbers(data, board, bingo_numbers, i-1, &sum_unmarked) && 
                bingo_board_n_wins_after_n_numbers(data, board, bingo_numbers, i, &sum_unmarked)) {
                
                latest_win = i;
                part2 = sum_unmarked * bingo_numbers[i-1];
                break;
            }
        }
    }
    
    fclose(fptr);
    free(bingo_numbers);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2: %"PRIu64"\n", part2);
    
    return EXIT_SUCCESS;
}
