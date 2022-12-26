#include "day25_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    char** data = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    
    char* part1 = calculate(data, data_size);
    
    free_str_arr(data, data_size);
    
    printf("Part 1: %s\n", part1);
    
    free(part1);
    
    return EXIT_SUCCESS;
}
