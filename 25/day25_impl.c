#include "day25_impl.h"

static char** copy_arr(char** data, uint64_t ydim, uint64_t xdim) {
    char** out = calloc(ydim, sizeof(char*));
    for (uint64_t y=0; y<ydim; ++y) {
        out[y] = calloc(xdim, sizeof(char));
        for (uint64_t x=0; x<xdim; ++x) {
            out[y][x] = data[y][x];
        }
    }
    return out;
}

static void free_arr(char** data, uint64_t ydim) {
    for (uint64_t y=0; y<ydim; ++y) {
        free(data[y]);
    }
    free(data);
}

static int64_t move_east(char*** data_p, uint64_t ydim, uint64_t xdim) {
    int64_t any_moved = 0;
    char** out = copy_arr(*data_p, ydim, xdim);
    char** arr = *data_p;
    
    for (uint64_t y=0; y<ydim; ++y) {
        for (uint64_t x=0; x<xdim; ++x) {
            if (arr[y][x] == '>' && arr[y][(x+1)%xdim] == '.') {
                out[y][x] = '.';
                out[y][(x+1)%xdim] = '>';
                any_moved = 1;
            }
        }
    }
    
    free_arr(*data_p, ydim);
    *data_p = out;
    return any_moved;
}

static int64_t move_south(char*** data_p, uint64_t ydim, uint64_t xdim) {
    int64_t any_moved = 0;
    char** out = copy_arr(*data_p, ydim, xdim);
    char** arr = *data_p;
    
    for (uint64_t y=0; y<ydim; ++y) {
        for (uint64_t x=0; x<xdim; ++x) {
            if (arr[y][x] == 'v' && arr[(y+1)%ydim][x] == '.') {
                out[y][x] = '.';
                out[(y+1)%ydim][x] = 'v';
                any_moved = 1;
            }
        }
    }
    
    free_arr(*data_p, ydim);
    *data_p = out;
    return any_moved;
}

void calculate(char** data, uint64_t data_size, int64_t* part1) {
    uint64_t ydim = data_size;
    uint64_t xdim = strlen(data[0])-1;
    
    char** arr = copy_arr(data, ydim, xdim);
    
    *part1 = 0;
    while (1) {
        int64_t moved_east = move_east(&arr, ydim, xdim);
        int64_t moved_south = move_south(&arr, ydim, xdim);
        (*part1)++;

        if (moved_east == 0 && moved_south == 0) {
            break;
        }
    }
    free_arr(arr, ydim);
}
