#include <inttypes.h>
#include <stdio.h>
#include "file_loading.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    ll_i64* data = load_file_as_ll_i64(fptr);
    fclose(fptr);
    int64_t v1 = INT64_MAX, v2 = INT64_MAX, v3 = INT64_MAX, v4;
    int64_t part1 = 0, part2 = 0;
    
    ll_i64_node* it = data->start;
    while(ll_i64_next(&it, &v4)) {
        if (v3 < v4) part1++;
        if (v1 < v4) part2++;
        v1 = v2;
        v2 = v3;
        v3 = v4;
    }
    
    printf("Part 1: %" PRIu64 "\n", part1);
    printf("Part 2: %" PRIu64 "\n", part2);
    return EXIT_SUCCESS;
}
