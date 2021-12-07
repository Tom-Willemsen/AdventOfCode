#include "day5_impl.h"

int main(int argc, char** argv) {
    int64_t part1, part2;
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    char** points_s = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    
    day5(points_s, data_size, &part1, &part2);
    free_str_arr(points_s, data_size);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2: %"PRId64"\n", part2);
    
    return EXIT_SUCCESS;
}
