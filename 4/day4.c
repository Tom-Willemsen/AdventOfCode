#include "day4_impl.h"
#include "conversions.h"
#include "file_loading.h"


int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    char** data = load_file_as_str_arr(fptr, &data_size);
    
    fclose(fptr);
    
    int64_t n_numbers = 0;
    int64_t* numbers = str_to_int64_arr(data[0], ',', &n_numbers);
    
    int64_t n_boards = (data_size - 1) / (BOARD_SIZE + 1);
    int64_t*** boards = calloc(n_boards, sizeof(int64_t **));
    
    for (int64_t i=0; i<n_boards; ++i) {
        boards[i] = load_board(data, i);
    }
    
    for (int64_t i=0; i<data_size; ++i) {
        free(data[i]);
    }
    free(data);
    
    printf("Part 1: %"PRId64"\n", part1(boards, n_boards, numbers, n_numbers));
    printf("Part 2: %"PRId64"\n", part2(boards, n_boards, numbers, n_numbers));
    
    free(numbers);
    for (int64_t i=0; i<n_boards; ++i) {
        for (int64_t row=0; row<BOARD_SIZE; ++row) {
            free(boards[i][row]);
        }
        free(boards[i]);
    }
    free(boards);
    
    return EXIT_SUCCESS;
}
