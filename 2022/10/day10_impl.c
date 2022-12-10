#include "day10_impl.h"


static void update(int64_t x, int64_t cycles, int64_t* part1, char* part2) {
    assert(cycles >= 0);
    assert(cycles < WIDTH*HEIGHT);
    part2[cycles] = ' ';
    for (int64_t r=0; r<SPRITE_WIDTH; ++r) {
        if ((cycles+1) % WIDTH == (x+r) % WIDTH) {
            part2[cycles] = '#';
        }
    }
    
    if ((cycles+1) % 40 == 20) {
        (*part1) += x * (cycles+1);
    }
}


void calculate(char** data, uint64_t data_size, int64_t* part1, char* part2) {
    int64_t cycles = 0;
    int64_t x = 1;
    
    for (uint64_t i = 0; i < data_size; ++i) {
        update(x, cycles, part1, part2);
        cycles++;
        if (strncmp(data[i], "addx ", 5) == 0) {
            int64_t v = strtol(data[i]+5, NULL, 10);
            update(x, cycles, part1, part2);
            cycles++;
            x+=v;
        } 
    }
}
