#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


char** load_file_as_str_arr(FILE* fptr, uint64_t *size) {
    uint64_t line = 0, lines = 0, linelength = 0, maxlinelength = 0;
    int c;
    char *buffer, **data = NULL;
    
    while ((c = fgetc(fptr)) != EOF)
    {
        if (c == '\n') {
            lines++;
            if ((linelength + 1) > maxlinelength) {
                maxlinelength = linelength + 1;  
            }
        } else {
            linelength++;
        }
    }
    *size = lines;
    if ((linelength + 1) > maxlinelength) {
        maxlinelength = linelength + 1;  
    }
    
    data = calloc(lines, sizeof(char*));
    buffer = calloc(maxlinelength + 1, sizeof(char));
    rewind(fptr);
    
    while(fscanf(fptr, "%s", buffer) != EOF) {
        data[line] = calloc(maxlinelength + 1, sizeof(char));
        strncpy(data[line], buffer, maxlinelength + 1);
        line++;
    }
    free(buffer);
    return data;
}


void free_str_arr(char** str_arr, uint64_t size) {
    for (uint64_t i=0; i<size; ++i) {
        free(str_arr[i]);
    }
    free(str_arr);
}
