#include "day13_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    int64_t part1 = 0, part2_y_size = 0, part2_x_size = 0;
    char** part2;
    uint64_t data_size;
    char** data = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    
    calculate(data, data_size, &part1, &part2, &part2_y_size, &part2_x_size);
    
    free_str_arr(data, data_size);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2:\n");
    for (int64_t y=0; y<part2_y_size; ++y) {
        for (int64_t x=0; x<part2_x_size; ++x) {
            printf("%c", part2[y][x]);
        }
        puts("");
    }
    
    free_str_arr(part2, part2_y_size);
    
    return EXIT_SUCCESS;
}
