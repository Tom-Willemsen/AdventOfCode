#include <stdio.h>
#include <stdlib.h>

static FILE* open_arg_as_file_or_exit(int argc, char** argv) {
    if (argc == 0) {
        fprintf(stderr, "Usage: program <input filepath>\n");
        exit(EXIT_FAILURE);
    } else if (argc == 1) {
        fprintf(stderr, "Usage: %s <input filepath>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    FILE* fptr = fopen(argv[1], "r");
    
    if (fptr == NULL) {
        fprintf(stderr, "File at '%s' could not be opened\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    return fptr;
} 
