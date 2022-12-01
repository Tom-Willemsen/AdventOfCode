#include "day01_impl.h"

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    list_i64* elves = list_i64_init(1);
    
    int64_t total = 0;
    for (uint64_t i = 0; i < data_size; ++i) {
        if (data[i][0] == '\n') {
            list_i64_push_back(elves, total);
            total = 0;
            continue;
        }
        total += strtol(data[i], NULL, 10);
    }
    list_i64_push_back(elves, total);
    
    list_i64_sort_inplace(elves);
    
    assert(list_i64_size(elves) >= 3);
    
    *part1 = list_i64_get(elves, list_i64_size(elves) - 1);
    *part2 = list_i64_get(elves, list_i64_size(elves) - 1) + list_i64_get(elves, list_i64_size(elves) - 2) + list_i64_get(elves, list_i64_size(elves) - 3);
    
    list_i64_free(elves);
}
