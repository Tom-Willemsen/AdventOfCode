#include "day05_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    char* part1 = NULL;
    char* part2 = NULL;
    uint64_t data_size;
    char** data = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    
    calculate(data, data_size, &part1, &part2);
    
    free_str_arr(data, data_size);
    
    printf("Part 1: %s\n", part1);
    printf("Part 2: %s\n", part2);
    
    free(part1);
    free(part2);
    
    return EXIT_SUCCESS;
}
