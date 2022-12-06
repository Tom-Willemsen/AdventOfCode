#include "day06_impl.h"

int64_t find(char* data, uint64_t num) {
    set_i64* set = set_i64_init(10);
    for (uint64_t i=num; i<strlen(data); ++i) {
        uint64_t all_added = 1;
        for (uint64_t j=(i-num); j<i; ++j) {
            if (!set_i64_add(set, data[j])) {
                all_added = 0;
                break;
            }
        }
        if (all_added) {
            set_i64_free(set);
            return i;
        }
        set_i64_clear(set);
    }
    set_i64_free(set);
    return -1;
}

void calculate(char* data, int64_t* part1, int64_t* part2) {
    *part1 = find(data, 4);
    *part2 = find(data, 14);
}
