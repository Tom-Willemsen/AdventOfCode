#include "day11_impl.h"

void flash_recursive(uint8_t** data, int64_t y, int64_t x, uint64_t ysize, uint64_t xsize, list_tuple_i64* visited) {
    int64_t nb_y[8] = {y-1, y-1, y-1, y, y, y+1, y+1, y+1};
    int64_t nb_x[8] = {x-1, x, x+1, x-1, x+1, x-1, x, x+1};
    list_tuple_i64_push_back(visited, y, x);
    
    for (uint64_t i=0; i<8; ++i) {
        if (nb_y[i] >= 0 && nb_x[i] >= 0 && nb_y[i] < ysize && nb_x[i] < xsize) {
            data[nb_y[i]][nb_x[i]]++;
            if (data[nb_y[i]][nb_x[i]] > 9 && !list_tuple_i64_contains(visited, nb_y[i], nb_x[i])) {
                flash_recursive(data, nb_y[i], nb_x[i], ysize, xsize, visited);
            }
        }
    }
}

void calculate(uint8_t** data, uint64_t ysize, uint64_t xsize, int64_t* part1, int64_t* part2) {
    int64_t y = 0, x = 0;
    list_tuple_i64* visited = list_tuple_i64_init(xsize * ysize);
    
    *part1 = 0;
    *part2 = 0;
    
    for (int64_t step=0; step<INT64_MAX; ++step) {
        for (y=0; y<ysize; ++y) {
            for (x=0; x<xsize; ++x) {
                if (data[y][x] > 8) {
                    if (!list_tuple_i64_contains(visited, y, x)) {
                        flash_recursive(data, y, x, ysize, xsize, visited);
                    }
                } else {
                    data[y][x]++;
                }
            }
        }
        
        if (list_tuple_i64_size(visited) == ysize * xsize) {
            *part2 = step + 1;
            break;
        }
        
        while (list_tuple_i64_size(visited) > 0) {
            list_tuple_i64_pop_back(visited, &y, &x);
            data[y][x] = 0;
            if (step < 100) {
                (*part1)++;
            }
        }
    }
    list_tuple_i64_free(visited);
}
