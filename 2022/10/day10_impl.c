#include "day10_impl.h"


static void update(int64_t x, int64_t cycles, int64_t* part1, char* grid) {
    assert(cycles >= 0);
    assert(cycles < WIDTH*HEIGHT);
    grid[cycles] = ' ';
    for (int64_t r=0; r<SPRITE_WIDTH; ++r) {
        if ((cycles+1) % WIDTH == (x+r) % WIDTH) {
            grid[cycles] = '#';
            break;
        }
    }
    
    if ((cycles+1) % 40 == 20) {
        (*part1) += x * (cycles+1);
    }
}


void calculate(char** data, uint64_t data_size, int64_t* part1, char* part2) {
    int64_t cycles = 0;
    int64_t x = 1;
    char grid[WIDTH*HEIGHT] = {0};
    
    for (uint64_t i = 0; i < data_size; ++i) {
        update(x, cycles, part1, grid);
        cycles++;
        if (strncmp(data[i], "addx ", 5) == 0) {
            int64_t v = strtol(data[i]+5, NULL, 10);
            update(x, cycles, part1, grid);
            cycles++;
            x+=v;
        } 
    }
    
    ocr_6x4_string(grid, part2, 8, WIDTH);
}
