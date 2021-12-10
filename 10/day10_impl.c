#include "day10_impl.h"

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    char c, t;
    uint8_t has_error = 0;
    int64_t p1score = 0, p2score = 0;
    list_i64* stack = list_i64_init(20);
    list_i64* p2scores = list_i64_init(data_size);
    
    for (int64_t i=0; i<data_size; ++i) {
        list_i64_clear(stack);
        has_error = 0;
        for (int64_t j=0; j<strlen(data[i]); ++j) {
            c = data[i][j];
            if (c == '\n') {
                break;
            } else if (c == '{' || c == '[' || c == '<' || c == '(') {
                list_i64_push_back(stack, c);
            } else {
                t = list_i64_pop_back(stack);
                if (c == ')' && t != '(') {
                    has_error = 1;
                    p1score += 3;
                    break;
                } else if (c == ']' && t != '[') {
                    has_error = 1;
                    p1score += 57;
                    break;
                } else if (c == '}' && t != '{') {
                    has_error = 1;
                    p1score += 1197;
                    break;
                } else if (c == '>' && t != '<') {
                    has_error = 1;
                    p1score += 25137;
                    break;
                }
            }
        }
        if (!has_error) {
            p2score = 0;
            while (stack->size > 0) {
                c = list_i64_pop_back(stack);
                p2score *= 5;
                if (c == '(') {
                    p2score += 1;
                } else if (c == '[') {
                    p2score += 2;
                } else if (c == '{') {
                    p2score += 3;
                } else {
                    assert(c == '<');
                    p2score += 4;
                }
            }
            list_i64_push_back(p2scores, p2score);
        }
    }
    assert(p2scores->size % 2 == 1 && p2scores->size > 0);
    list_i64_sort_inplace(p2scores);
    
    *part1 = p1score;
    *part2 = list_i64_get(p2scores, (p2scores->size - 1) / 2);
    
    list_i64_free(stack);
    list_i64_free(p2scores);
}
