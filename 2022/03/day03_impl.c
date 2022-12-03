#include "day03_impl.h"

int64_t score(char c) {
    assert((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    if (c >= 'a' && c <= 'z') {
        return 1 + c - 'a';
    } else {
        return 27 + c - 'A';
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    
    assert(data_size % 3 == 0);
    
    for (uint64_t i = 0; i < data_size; ++i) {
        for (uint64_t j = 0; j < strlen(data[i]) / 2; ++j) {
            if (strchr(data[i] + strlen(data[i]) / 2, data[i][j]) != NULL) {
                *part1 += score(data[i][j]);
                break;
            } 
        }
        if (i % 3 == 0) {
            for (uint64_t j = 0; j < strlen(data[i]); ++j) {
                if (strchr(data[i+1], data[i][j]) != NULL && strchr(data[i+2], data[i][j]) != NULL) {
                    *part2 += score(data[i][j]);
                    break;
                }
            }
        }
    }
}
