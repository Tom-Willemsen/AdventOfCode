#include "day03_impl.h"

uint64_t part1(char** data, uint64_t data_size) {
    int64_t ones;
    uint64_t gamma = 0, epsilon = 0;
    for(uint64_t pos=0; pos<strlen(data[0]) - 1; ++pos) {
        ones = 0;
        for(uint64_t row=0; row<data_size; ++row) {
            if (data[row][pos] == '1') {
                ones++;
            } else {
                ones--;
            }
        }
        gamma <<= 1;
        epsilon <<= 1;
        if (ones > 0) {
            gamma++;
        } else {
            epsilon++;
        }
    }
    return gamma * epsilon;
}

uint64_t count_char_matching_selector(char** data, uint64_t data_size, char* selector, uint64_t pos, char c) {
    uint64_t counter = 0;
    for (uint64_t row = 0; row<data_size; ++row) {
        if (strncmp(data[row], selector, pos) == 0 && data[row][pos] == c) {
            counter++;
        }
    }
    return counter;
}

char* first_matching_selector(char** data, uint64_t data_size, char* selector, uint64_t pos) {
    for (uint64_t row = 0; row<data_size; ++row) {
        if (strncmp(data[row], selector, pos) == 0) {
            return data[row];
        }
    }
    return NULL;
}

uint64_t part2(char** data, uint64_t data_size, uint64_t is_co2) {
    uint64_t ones, zeros, result, pos;
    char* selector = calloc(strlen(data[0]) + 1, sizeof(char));
    
    for (pos=0; pos<strlen(data[0]) - 1; ++pos) {
        zeros = count_char_matching_selector(data, data_size, selector, pos, '0');
        ones = count_char_matching_selector(data, data_size, selector, pos, '1');
        
        if (ones + zeros == 1) {
            break;
        }
        
        if (is_co2) {
            selector[pos] = (ones < zeros) ? '1' : '0';   
        } else {
            selector[pos] = (ones < zeros) ? '0' : '1';
        }
    }
    char* result_s = first_matching_selector(data, data_size, selector, pos);
    if (result_s == NULL) {
        printf("bad result\n");
        result = 0;
    } else {
        result = strtol(result_s, NULL, 2);
    }
    free(selector);
    return result;
} 
