#include "day5_impl.h"

static int64_t** parse_points(char** strings, uint64_t data_size) {
    int64_t** points = calloc(data_size, sizeof(int64_t*));
    for (uint64_t i=0; i<data_size; ++i) {
        points[i] = calloc(4, sizeof(int64_t));
        sscanf(strings[i], "%"SCNd64",%"SCNd64" -> %"SCNd64",%"SCNd64, 
               &points[i][0], &points[i][1], &points[i][2], &points[i][3]);
    }
    return points;
}

static int64_t count_gt_2(uint16_t** array, int64_t max_x, int64_t max_y) {
    int64_t count = 0;
    for (int64_t x = 0; x<max_x; ++x) {
        for (int64_t y = 0; y<max_y; ++y) {
            if (array[x][y] >= 2) {
                count++;
            }
        }
    }
    return count;
}

static inline void unpack_array(int64_t* points, int64_t* x1, int64_t* y1, int64_t* x2, int64_t* y2) {
    *x1 = points[0];
    *y1 = points[1];
    *x2 = points[2];
    *y2 = points[3];
}

static void mark_straight(uint16_t** array, int64_t** points, uint64_t data_size) {
    int64_t x1,y1,x2,y2,i,x,y;
    for (i=0; i<data_size; ++i) {
        unpack_array(points[i], &x1, &y1, &x2, &y2);
        if (x1 == x2) {
            for (y = min(y1, y2); y<=max(y1, y2); y++) {
                array[x1][y]++;
            }
        } else if (y1 == y2) {
            for (x = min(x1, x2); x<=max(x1, x2); x++) {
                array[x][y1]++;
            }
        }
    }
}

static void mark_diagonal(uint16_t** array, int64_t** points, uint64_t data_size) {
    int64_t x1,y1,x2,y2,i,x;
    for (i=0; i<data_size; ++i) {
        unpack_array(points[i], &x1, &y1, &x2, &y2);
        if (x2 - x1 == y2 - y1) {
            for (x = min(x1, x2); x<=max(x1, x2); x++) {
                array[x][y1 - x1 + x]++;
            }
        } else if (x2 - x1 == -(y2 - y1)) {
            for (x = min(x1, x2); x<=max(x1, x2); x++) {
                array[x][y1 + x1 - x]++;
            }
        }
    }
}

void day5(char** points_s, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t max_x = 0, max_y = 0, i;
    int64_t** points = parse_points(points_s, data_size);
    
    assert(data_size < UINT16_MAX);
    
    for (i=0; i<data_size; ++i) {
        max_x = max(max_x, max(points[i][0]+1, points[i][2]+1));
        max_y = max(max_y, max(points[i][1]+1, points[i][3]+1));
    }
    
    // using int64_t here doubles the execution time.
    uint16_t** array = calloc(max_y, sizeof(uint16_t*));
    for (i=0; i<max_y; ++i) {
        array[i] = calloc(max_x, sizeof(uint16_t));
    }
    
    mark_straight(array, points, data_size);
    *part1 = count_gt_2(array, max_x, max_y);
    mark_diagonal(array, points, data_size);
    *part2 = count_gt_2(array, max_x, max_y);
    
    for (i=0; i<max_y; ++i) {
        free(array[i]);
    }
    free(array);
    for (i=0; i<data_size; ++i) {
        free(points[i]);
    }
    free(points);
}
