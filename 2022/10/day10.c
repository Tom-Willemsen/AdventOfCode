#include "day10_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    int64_t part1 = 0;
    char part2[WIDTH*HEIGHT] = {0};
    uint64_t data_size;
    char** data = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    
    calculate(data, data_size, &part1, part2);
    
    free_str_arr(data, data_size);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2:\n");
    for (int64_t r=0; r<HEIGHT; ++r) {
        for (int64_t c=0; c<WIDTH; ++c) {
            printf("%c", part2[r*WIDTH + c]);
        }
        printf("\n");
    }
    
    return EXIT_SUCCESS;
}
