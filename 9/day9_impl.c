#include "day9_impl.h"

typedef struct coord_list {
    list_i64* x;
    list_i64* y;
} coord_list;

static coord_list* coord_list_init() {
    coord_list* list = calloc(1, sizeof(coord_list));
    list->x = list_i64_init(150);
    list->y = list_i64_init(150);
    return list;
}

static void coord_list_free(coord_list* list) {
    list_i64_free(list->x);
    list_i64_free(list->y);
    free(list);
}

static inline void coord_list_clear(coord_list* list) {
    list->y->size = 0;
    list->x->size = 0;
}

static inline void coord_list_append(coord_list* list, int64_t y, int64_t x) {
    list_i64_push_back(list->y, y);
    list_i64_push_back(list->x, x);
}

static int64_t coord_list_contains(coord_list* list, int64_t y, int64_t x) {
    assert(list->x->size == list->y->size);
    for (int64_t i=list->x->size - 1; i>=0; --i) {
        if (list_i64_get(list->x, i) == x && list_i64_get(list->y, i) == y) {
            return 1;
        }
    }
    return 0;
}

static inline uint64_t coord_list_size(coord_list* list) {
    assert(list->x->size == list->y->size);
    return list->x->size;
}

static uint8_t is_low_point(uint8_t** data, uint64_t ysize, uint64_t xsize, int64_t y, int64_t x) {
    return !(
        (x-1 >= 0 && data[y][x-1] <= data[y][x]) || 
        (x+1 < xsize && data[y][x+1] <= data[y][x]) || 
        (y-1 >= 0 && data[y-1][x] <= data[y][x]) || 
        (y+1 < ysize && data[y+1][x] <= data[y][x])
    );
}

static void find_basin(uint8_t** data, int64_t ysize, uint64_t xsize, int64_t y, int64_t x, coord_list* coord_list) {
    if (x-1 >= 0 && 8 >= data[y][x-1] && !coord_list_contains(coord_list, y, x-1)) {
        coord_list_append(coord_list, y, x-1);
        find_basin(data, ysize, xsize, y, x-1, coord_list);
    }
    if (x+1 < xsize && 8 >= data[y][x+1] && !coord_list_contains(coord_list, y, x+1)) {
        coord_list_append(coord_list, y, x+1);
        find_basin(data, ysize, xsize, y, x+1, coord_list);
    }
    if (y-1 >= 0 && 8 >= data[y-1][x] && !coord_list_contains(coord_list, y-1, x)) {
        coord_list_append(coord_list, y-1, x);
        find_basin(data, ysize, xsize, y-1, x, coord_list);
    }
    if (y+1 < ysize && 8 >= data[y+1][x] && !coord_list_contains(coord_list, y+1, x)) {
        coord_list_append(coord_list, y+1, x);
        find_basin(data, ysize, xsize, y+1, x, coord_list);
    }
}

void calculate(uint8_t** data, uint64_t ysize, uint64_t xsize, int64_t* part1, int64_t* part2) {
    int64_t x, y, v1 = 0, v2 = 0, v3 = 0;
    uint64_t size = 0;
    *part1 = 0;
    
    coord_list* clist = coord_list_init();
    for (y=0; y<ysize; ++y) {
        for (x=0; x<xsize; ++x) {
            if (is_low_point(data, ysize, xsize, y, x)) {
                *part1 += (1 + data[y][x]);
                
                coord_list_clear(clist);
                coord_list_append(clist, y, x);
                find_basin(data, ysize, xsize, y, x, clist);
                size = coord_list_size(clist);
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
    coord_list_free(clist);
    *part2 = v1 * v2 * v3;
}
