#include "day8_impl.h"

static void parse_line(char* data, char** patterns, char** output) {
    sscanf(data, "%s %s %s %s %s %s %s %s %s %s | %s %s %s %s", 
               patterns[0], patterns[1], patterns[2], patterns[3], patterns[4], 
               patterns[5], patterns[6], patterns[7], patterns[8], patterns[9],
               output[0], output[1], output[2], output[3]);
}

static inline uint_fast8_t str_contains(char* str, char c) {
    return (strchr(str, c) != NULL);
}

static uint_fast8_t str_contains_all(char* str, list_i64* list) {
    for (uint64_t i = 0; i<list->size; ++i) {
        if (!str_contains(str, list_i64_get(list, i))) {
            return 0;
        }
    }
    return 1;
}

list_i64* chars_from_str_with_len(char** patterns, uint64_t len) {
    uint64_t i, j, slen;
    list_i64* result = list_i64_init(10);
    
    for (i=0; i<10; ++i) {
        slen = strnlen(patterns[i], 10);
        if (slen == len) {
            for (j=0; j<slen; ++j) {
                if (!list_i64_contains(result, patterns[i][j])) {
                    list_i64_push_back(result, patterns[i][j]);
                }
            }
        }
    }
    return result;
}

static inline uint_fast8_t is_5(char* c, list_i64* ones, list_i64* fours) {
    int64_t f;
    for (uint64_t i=0; i<fours->size; ++i) {
        f = list_i64_get(fours, i);
        if (!list_i64_contains(ones, f) && !str_contains(c, f)) {
            return 0;
        }
    }
    return 1;
}

static int64_t decode_str(char* c, list_i64* ones, list_i64* fours, list_i64* sevens) {
    uint64_t len_c = strnlen(c, 10);
    
    if (len_c == 2) {
        return 1;
    } else if (len_c == 3) {
        return 7;
    } else if (len_c == 4) {
        return 4;
    } else if (len_c == 7) {
        return 8;
    } else if (len_c == 5) {
        if (str_contains_all(c, sevens)) {
            return 3;
        } else if (is_5(c, ones, fours)) {
            return 5;  
        } else {
            return 2;
        }
    } else if (len_c == 6) {
        if (str_contains_all(c, fours) && str_contains_all(c, ones)) {
            return 9;
        } else if (!str_contains_all(c, sevens) && !str_contains_all(c, ones)) {
            return 6;
        } else {
            return 0;
        }
    } else {
        printf("invalid string to decode '%s', len_c=%"PRIu64"\n", c, len_c);
        return 0;
    }
}

static int64_t calculate_p1(char** patterns, char** output) {
    int64_t len, result = 0;
    for (uint64_t i=0; i<4; ++i) {
        len = strnlen(output[i], 10);
        if (len == 2 || len == 3 || len == 4 || len == 7) {
            result++;
        }
    }
    return result;
}

static int64_t calculate_p2(char** patterns, char** output) {
    list_i64 *ones, *fours, *sevens;
    
    // could also choose to pass output to these functions, but the
    // challenge/test inputs don't require this.
    ones = chars_from_str_with_len(patterns, 2);
    fours = chars_from_str_with_len(patterns, 4);
    sevens = chars_from_str_with_len(patterns, 3);
    
    int64_t n = 0;
    for (uint64_t i=0; i<4; ++i) {
        n *= 10;
        n += decode_str(output[i], ones, fours, sevens);
    }
    list_i64_free(ones);
    list_i64_free(fours);
    list_i64_free(sevens);
    return n;
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    char* patterns[10];
    char* output[4];
    uint64_t i;
    
    for (i=0; i<10; ++i) {
        patterns[i] = calloc(10, sizeof(char));
    }
    for (i=0; i<4; ++i) {
        output[i] = calloc(10, sizeof(char));
    }
    
    for (uint64_t i=0; i<data_size; ++i) {
        parse_line(data[i], patterns, output);
        *part1 += calculate_p1(patterns, output);
        *part2 += calculate_p2(patterns, output);
    }
    
    for (i=0; i<10; ++i) {
        free(patterns[i]);
    }
    for (i=0; i<4; ++i) {
        free(output[i]);
    }
}
