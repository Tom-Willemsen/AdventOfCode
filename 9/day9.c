#include "day9_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t xsize, ysize;
    int64_t part1 = 0, part2 = 0;
    uint8_t** data = load_dense_file_as_uint8_arr(fptr, &ysize, &xsize);
    fclose(fptr);
    
    calculate(data, ysize, xsize, &part1, &part2);
    
    for (uint64_t i=0; i<ysize; ++i) {
        free(data[i]);
    }
    free(data);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2: %"PRId64"\n", part2);
    
    return EXIT_SUCCESS;
}
