#include "day09_impl.h"

static inline uint8_t is_low_point(uint8_t** data, uint64_t ysize, uint64_t xsize, int64_t y, int64_t x) {
    return (x-1 < 0 || data[y][x-1] > data[y][x]) &&
           (x+1 >= xsize || data[y][x+1] > data[y][x]) &&
           (y-1 < 0 || data[y-1][x] > data[y][x]) &&
           (y+1 >= ysize || data[y+1][x] > data[y][x]);
}

static void find_basin(uint8_t** data, int64_t ysize, uint64_t xsize, int64_t y, int64_t x, list_tuple_i64* clist) {
    int64_t nb_y[4] = {y+1, y-1, y, y};
    int64_t nb_x[4] = {x, x, x+1, x-1};
    
    for (uint64_t i=0; i<4; ++i) {
        if (nb_y[i] >= 0 && nb_y[i] < ysize && nb_x[i] >= 0 && nb_x[i] < xsize && 
            8 >= data[nb_y[i]][nb_x[i]] && !list_tuple_i64_contains(clist, nb_y[i], nb_x[i])) 
        {
            list_tuple_i64_push_back(clist, nb_y[i], nb_x[i]);
            find_basin(data, ysize, xsize, nb_y[i], nb_x[i], clist);
        }
    }
}

void calculate(uint8_t** data, uint64_t ysize, uint64_t xsize, int64_t* part1, int64_t* part2) {
    int64_t x, y, v1 = 0, v2 = 0, v3 = 0;
    uint64_t size = 0;
    *part1 = 0;
    
    list_tuple_i64* clist = list_tuple_i64_init(150);
    for (x=0; x<xsize; ++x) {
        for (y=0; y<ysize; ++y) {
            if (is_low_point(data, ysize, xsize, y, x)) {
                *part1 += (1 + data[y][x]);
                
                list_tuple_i64_clear(clist);
                list_tuple_i64_push_back(clist, y, x);
                find_basin(data, ysize, xsize, y, x, clist);
                size = list_tuple_i64_size(clist);
                if (size > v1) {
                    v3 = v2;
                    v2 = v1;
                    v1 = size;
                } else if (size > v2) {
                    v3 = v2;
                    v2 = size;
                } else if (size > v3) {
                    v3 = size;
                }
            }
        }
    }
    list_tuple_i64_free(clist);
    *part2 = v1 * v2 * v3;
}
