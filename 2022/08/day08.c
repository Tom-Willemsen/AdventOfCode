#include "day08_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    int64_t part1 = 0;
    int64_t part2 = 0;
    uint64_t x_size, y_size;
    uint8_t** data = load_dense_file_as_uint8_arr(fptr, &y_size, &x_size);
    fclose(fptr);
    
    calculate(data, x_size, y_size, &part1, &part2);
    
    for (uint64_t y=0; y<y_size; ++y) {
        free(data[y]);
    }
    free(data);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2: %"PRId64"\n", part2);
    
    return EXIT_SUCCESS;
}
