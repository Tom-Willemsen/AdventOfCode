#include "file_loading.h"

FILE* open_arg_as_file_or_exit(int argc, char** argv) {
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
    uint64_t l, lines = 1, linelength = 0, maxlinelength = 0;
    int c;
    char **data = NULL, *buffer;
    
    while ((c = fgetc(fptr)) != EOF)
    {
        linelength++;
        if (c == '\n') {
            lines++;
            if (linelength > maxlinelength) {
                maxlinelength = linelength;
            }
            linelength = 0;
        }
    }
    
    if (linelength > maxlinelength) {
        maxlinelength = linelength;  
    }
    
    data = calloc(lines, sizeof(char*));
    buffer = calloc(maxlinelength + 1, sizeof(char));
    rewind(fptr);
    
    for(l=0; l<lines; ++l){
        if (getline(&buffer, &maxlinelength, fptr) == -1) {
            break;
        }
        data[l] = calloc(maxlinelength, sizeof(char));
        strncpy(data[l], buffer, maxlinelength);
    }
    
    *size = l;
    free(buffer);
    return data;
}

void free_str_arr(char** const str_arr, const uint64_t size) {
    for (uint64_t i=0; i<size; ++i) {
        free(str_arr[i]);
    }
    free(str_arr);
}

ll_i64* load_file_as_ll_i64(FILE* fptr) {
    ll_i64* data = ll_i64_init();
    int64_t value;
    while(fscanf(fptr, "%" SCNu64, &value) != EOF) {
        ll_i64_push_back(data, value);
    }
    return data;
}
