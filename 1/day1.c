#include <inttypes.h>
#include <stdio.h>
#include "file_loading.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    list_i64* data = load_file_as_list_i64(fptr);
    fclose(fptr);
    int64_t v1 = INT64_MAX, v2 = INT64_MAX, v3 = INT64_MAX, v4;
    int64_t part1 = 0, part2 = 0;
    
    for(uint64_t i=0; i<data->size; ++i) {
        v4 = list_i64_get(data, i);
        if (v3 < v4) part1++;
        if (v1 < v4) part2++;
        v1 = v2;
        v2 = v3;
        v3 = v4;
    }
    
    list_i64_free(data);
    
    printf("Part 1: %" PRIu64 "\n", part1);
    printf("Part 2: %" PRIu64 "\n", part2);
    return EXIT_SUCCESS;
}
