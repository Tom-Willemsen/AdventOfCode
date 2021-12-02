#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    int64_t p1depth = 0, p2depth = 0, horiz = 0, aim = 0, dist;
    char dir[10];
    
    if (argc < 2) return 1;
    
    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) return 2;
    
    while(fscanf(fptr, "%9s %" SCNd64, dir, &dist) != EOF) {
        if (strncmp(dir, "forward", 10) == 0) {
            horiz += dist;
            p2depth += aim * dist;
        } else if (strncmp(dir, "up", 10) == 0) {
            p1depth -= dist;
            aim -= dist;
        } else if (strncmp(dir, "down", 10) == 0) {
            p1depth += dist;
            aim += dist;
        }
    }
    
    fclose(fptr);
    
    printf("Part 1: %" PRId64 "\n", p1depth * horiz);
    printf("Part 2: %" PRId64 "\n", p2depth * horiz);
} 
