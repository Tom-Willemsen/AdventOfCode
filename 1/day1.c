#include <inttypes.h>
#include <stdio.h>

int main(int argc, char** argv) {
    uint64_t v1 = UINT64_MAX, v2 = UINT64_MAX, v3 = UINT64_MAX, v4;
    uint64_t part1 = 0, part2 = 0;
    
    if (argc < 2) return 1;
    
    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) return 2;
    
    while(fscanf(fptr, "%" SCNu64, &v4) != EOF) {
        if (v3 < v4) part1++;
        if (v1 < v4) part2++;
        v1 = v2;
        v2 = v3;
        v3 = v4;
    }
    
    fclose(fptr);
    
    printf("Part 1: %" PRIu64 "\n", part1);
    printf("Part 2: %" PRIu64 "\n", part2);
    return 0;
}
