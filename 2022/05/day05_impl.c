#include "day05_impl.h"


void calculate(char** data, uint64_t data_size, char** part1, char** part2) {
    assert(data_size > 0);
    
    uint64_t n_stacks = strlen(data[0]) / 4;
    list_i64** p1_stacks = calloc(n_stacks, sizeof(list_i64*));
    list_i64** p2_stacks = calloc(n_stacks, sizeof(list_i64*));
    *part1 = calloc(n_stacks + 1, sizeof(char));
    *part2 = calloc(n_stacks + 1, sizeof(char));
    
    
    for (uint64_t i = 0; i < n_stacks; ++i) {
        p1_stacks[i] = list_i64_init(1);
        p2_stacks[i] = list_i64_init(1);
    }
    
    for (int64_t line = data_size - 1; line >= 0; --line) {
        if (strchr(data[line], '[') != NULL) {
            for(uint64_t i = 0; i < n_stacks; ++i) {
                char c = data[line][(i*4)+1];
                if (c != ' ' && c != '\n') {
                    list_i64_push_back(p1_stacks[i], c);
                    list_i64_push_back(p2_stacks[i], c);
                }
            } 
        }
    }
            
    list_i64* popped = list_i64_init(1);
    
    for (uint64_t line = 0; line < data_size; ++line) {
        if (strlen(data[line]) > 4 && data[line][0] == 'm') {
            int64_t num, from, to;
            sscanf(data[line], "move %"SCNd64" from %"SCNd64" to %"SCNd64, &num, &from, &to);
            from--;
            to--;
            assert(num >= 0);
            assert(from >= 0 && from < n_stacks);
            assert(to >= 0 && to < n_stacks);
            for (uint64_t i=0; i<num; ++i) {
                list_i64_push_back(p1_stacks[to], list_i64_pop_back(p1_stacks[from]));
                list_i64_push_back(popped, list_i64_pop_back(p2_stacks[from]));
            }
            
            while (list_i64_size(popped) > 0) {
                list_i64_push_back(p2_stacks[to], list_i64_pop_back(popped));
            }
        }
    }
            
    list_i64_free(popped);
    
    for (uint64_t i = 0; i < n_stacks; ++i) {
        (*part1)[i] = list_i64_peek_back(p1_stacks[i]);
        (*part2)[i] = list_i64_peek_back(p2_stacks[i]);
        list_i64_free(p1_stacks[i]);
        list_i64_free(p2_stacks[i]);
    }
    
    free(p1_stacks);
    free(p2_stacks);
}
