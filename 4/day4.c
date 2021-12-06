#include "day4_impl.h"
#include "conversions.h"
#include "file_loading.h"
#include "list.h"


int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    char** data = load_file_as_str_arr(fptr, &data_size);
    
    fclose(fptr);
    
    list_i64* numbers = str_to_int64_list(data[0], ',');
    
    int64_t n_boards = 0;
    list_i64** boards = load_boards(data, data_size, &n_boards);
    
    free_str_arr(data, data_size);
    
    printf("Part 1: %"PRId64"\n", part1(boards, n_boards, numbers));
    printf("Part 2: %"PRId64"\n", part2(boards, n_boards, numbers));
    
    free_boards(boards, n_boards);
    list_i64_free(numbers);
    
    return EXIT_SUCCESS;
}
