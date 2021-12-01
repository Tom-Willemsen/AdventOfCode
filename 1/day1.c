#include <stdio.h>
#include <limits.h>

int main(int argc, char** argv) {
    int v1 = INT_MAX;
    int v2 = INT_MAX;
    int v3 = INT_MAX;
    int v4;
    int part1 = 0;
    int part2 = 0;
    
    if (argc < 2) {
        puts("need filepath");
        return 1;
    }
    
    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        puts("invalid filename");
        return 1;
    }
    
    while(fscanf(fptr, "%d\n", &v4) != EOF) {
        if (v3 < v4) {
            part1++;
        }
        if (v1 < v4) {
            part2++;
        }
        v1 = v2;
        v2 = v3;
        v3 = v4;
    }
    
    fclose(fptr);
    
    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);
    return 0;
}
