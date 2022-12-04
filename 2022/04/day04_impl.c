#include "day04_impl.h"


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t a, b, c, d;
    
    for (uint64_t i = 0; i < data_size; ++i) {
        sscanf(data[i], "%"SCNd64"-%"SCNd64",%"SCNd64"-%"SCNd64, &a, &b, &c, &d);
        
        if ((c >= a && d <= b) || (a >= c && b <= d)) {
            (*part1)++;
        }
            
        if (c <= b && d >= a) {
            (*part2)++;
        }
    }
}
