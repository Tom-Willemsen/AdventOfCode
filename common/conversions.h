#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t* str_to_int64_arr(const char* const data, const char delim, int64_t* n) {
    int64_t slen = strlen(data);
    int64_t* ret = calloc(slen, sizeof(int64_t));
    char* buffer = calloc(slen + 1, sizeof(char));
    int64_t buffer_idx = 0;
    char c;
    
    *n = 0;
    for (int64_t idx = 0; idx < slen; ++idx) {
        c = data[idx];
        if (c == '\n' || (c == delim && buffer_idx > 0)) {
            ret[*n] = strtol(buffer, NULL, 10);
            (*n)++;
            for (int64_t i=0; i<slen + 1; ++i) {
                buffer[i] = '\0';
            }
            memset(buffer, '\0', slen + 1);
            buffer_idx = 0;
        } else if (c >= '0' && c <= '9') {
            buffer[buffer_idx] = c;
            buffer_idx++;
        }
    }
    
    free(buffer);
    return ret;
}
