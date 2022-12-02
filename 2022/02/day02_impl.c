#include "day02_impl.h"

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    
    for (uint64_t i = 0; i < data_size; ++i) {
        int64_t a = data[i][0] - 'A';
        int64_t b = data[i][2] - 'X';
        *part1 += 1 + b + (((b - a + 4) % 3) * 3);
        *part2 += 1 + ((a + b + 2) % 3) + (3 * b);
    }
}
