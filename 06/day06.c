#include "day06_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    int64_t part1, part2;
    char** points_s = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    list_i64* initialstate = str_to_int64_list(points_s[0], ',');
    free_str_arr(points_s, data_size);
    
    part1 = simulate(initialstate, 80);
    part2 = simulate(initialstate, 256);
    
    list_i64_free(initialstate);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2: %"PRId64"\n", part2);
    
    return EXIT_SUCCESS;
}
