#include "day3_impl.h"
#include "file_loading.h"

int main(int argc, char** argv) {
    uint64_t data_size;
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    char** data = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    
    printf("Part 1: %" PRIu64 "\n", part1(data, data_size));
    printf("Part 2: %ld\n", part2(data, data_size, 0) * part2(data, data_size, 1));
    
    free_str_arr(data, data_size);
    return EXIT_SUCCESS;
}
