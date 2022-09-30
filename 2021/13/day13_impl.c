#include "day13_impl.h"

static void append_dot(list_tuple_i64* dots, int64_t x, int64_t y) {
    if (!list_tuple_i64_contains(dots, x, y)) {
        list_tuple_i64_push_back(dots, x, y);
    }
}

static list_tuple_i64* fold_along_x_axis(list_tuple_i64* dots, int64_t f, int64_t* max_x) {
    int64_t new_max_x = 0, x, y;
    list_tuple_i64* newdots = list_tuple_i64_init(list_tuple_i64_size(dots));
    while (list_tuple_i64_size(dots) > 0) {
        list_tuple_i64_pop_back(dots, &x, &y);
        assert(x != f);
        if (x > f) {
            append_dot(newdots, 2*f - x, y);
            new_max_x = max(new_max_x, 2*f - x);
        } else {
            append_dot(newdots, x, y);
            new_max_x = max(new_max_x, x);
        }
    }
    list_tuple_i64_free(dots);
    *max_x = new_max_x;
    return newdots;
}

static list_tuple_i64* fold_along_y_axis(list_tuple_i64* dots, int64_t f, int64_t* max_y) {
    int64_t new_max_y = 0, x, y;
    list_tuple_i64* newdots = list_tuple_i64_init(list_tuple_i64_size(dots));
    while (list_tuple_i64_size(dots) > 0) {
        list_tuple_i64_pop_back(dots, &x, &y);
        assert(y != f);
        if (y > f) {
            append_dot(newdots, x, 2*f - y);
            new_max_y = max(new_max_y, 2*f - y);
        } else {
            append_dot(newdots, x, y);
            new_max_y = max(new_max_y, y);
        }
    }
    list_tuple_i64_free(dots);
    *max_y = new_max_y;
    return newdots;
}

void calculate(char** data, uint64_t data_size, int64_t* part1, char*** part2, int64_t* part2_y_size, int64_t* part2_x_size) {
    int64_t x, y, f, max_x= 0, max_y = 0, axis;
    char a;
    uint64_t i;
    list_tuple_i64* dots = list_tuple_i64_init(data_size);
    list_tuple_i64* folds = list_tuple_i64_init(15);
    
    for (i=0; i<data_size; ++i) {
        if (data[i][0] >= '0' && data[i][0] <= '9') {
            sscanf(data[i], "%"SCNd64",%"SCNd64, &x, &y);
            append_dot(dots, x, y);
            max_x = max(x, max_x);
            max_y = max(y, max_y);
        } else if (data[i][0] == 'f') {
            sscanf(data[i], "fold along %c=%"SCNd64, &a, &f);
            list_tuple_i64_push_back(folds, a, f);
        }
    }
    
    for (i=0; i<list_tuple_i64_size(folds); ++i) {
        list_tuple_i64_get(folds, i, &axis, &f);
        if (axis == 'x') {
            dots = fold_along_x_axis(dots, f, &max_x);
        } else {
            dots = fold_along_y_axis(dots, f, &max_y);
        }
        if (i == 0) {
            *part1 = list_tuple_i64_size(dots);
        }
    }
    
    *part2 = calloc(max_y+1, sizeof(char*));
    *part2_x_size = max_x + 1;
    *part2_y_size = max_y + 1;
    for (y=0; y<=max_y; ++y) {
        (*part2)[y] = calloc(max_x+1, sizeof(char));
        for (x=0; x<=max_x; ++x) {
            (*part2)[y][x] = list_tuple_i64_contains(dots, x, y) ? '#' : ' ';
        }
    }
    
    list_tuple_i64_free(dots);
    list_tuple_i64_free(folds);
}
