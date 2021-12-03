#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "file_loading.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    int64_t p1depth = 0, p2depth = 0, horiz = 0, dist;
    char dir[10];
    
    while(fscanf(fptr, "%9s %" SCNd64, dir, &dist) != EOF) {
        if (strncmp(dir, "forward", 10) == 0) {
            horiz += dist;
            p2depth += p1depth * dist;
        } else if (strncmp(dir, "up", 10) == 0) {
            p1depth -= dist;
        } else if (strncmp(dir, "down", 10) == 0) {
            p1depth += dist;
        }
    }
    
    fclose(fptr);
    
    printf("Part 1: %" PRId64 "\n", p1depth * horiz);
    printf("Part 2: %" PRId64 "\n", p2depth * horiz);
    return EXIT_SUCCESS;
} 
