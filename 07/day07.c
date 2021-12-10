#include "day07_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    char** positions_s = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    list_i64* positions = str_to_int64_list(positions_s[0], ',');
    free_str_arr(positions_s, data_size);
    
    printf("Part 1: %"PRId64"\n", part1(positions));
    printf("Part 2: %"PRId64"\n", part2(positions));
    
    list_i64_free(positions);
    
    return EXIT_SUCCESS;
}
