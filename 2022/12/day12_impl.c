#include "day12_impl.h"

static inline int64_t id_from_coord(size_t x_size, size_t y_size, int64_t x, int64_t y) {
    return x_size * y + x;
}

static inline void coord_from_id(int64_t id, size_t x_size, size_t y_size, int64_t* x, int64_t* y) {
    *y = id / x_size;
    *x = id % x_size;
}

static inline char value_at(char** data, size_t x, size_t y) {
    if (data[y][x] == 'S') {
        return 'a';
    } else if (data[y][x] == 'E') {
        return 'z';
    } else {
        return data[y][x];
    }
}

static int64_t best_path_length(char** data, size_t x_size, size_t y_size, int64_t start_x, int64_t start_y, int64_t end_x, int64_t end_y, int64_t break_cost) {
    int64_t current, next, cx, cy, cost, currcost;
    int64_t nx[4], ny[4];
    
    // worst-case optimal path, visiting every single square.
    int64_t worst_cost = min(x_size * y_size, break_cost);
    
    priorityQ_i64* openset = priorityQ_i64_init();
    priorityQ_i64_push_bbias(openset, 0, id_from_coord(x_size, y_size, start_x, start_y));

    map_i64* knowncosts = map_i64_init(x_size * y_size);
    map_i64_set(knowncosts, id_from_coord(x_size, y_size, start_x, start_y), 0);
    
    
    while (priorityQ_i64_size(openset) > 0) {
        current = priorityQ_i64_pop(openset);
        coord_from_id(current, x_size, y_size, &cx, &cy);
        
        nx[0] = cx+1;  ny[0] = cy;
        nx[1] = cx;    ny[1] = cy+1;
        nx[2] = cx-1;  ny[2] = cy;
        nx[3] = cx;    ny[3] = cy-1;
        
        currcost = map_i64_get(knowncosts, current, worst_cost);
        
        if (currcost > break_cost || data[cy][cx] == 'E') {
            break;
        }
        
        for (uint64_t i=0; i<4; ++i) {
            if (nx[i] < x_size 
                && ny[i] < y_size 
                && nx[i] >= 0 
                && ny[i] >= 0 
                && (value_at(data, nx[i], ny[i]) <= value_at(data, cx, cy) + 1)
            ) {
                
                next = id_from_coord(x_size, y_size, nx[i], ny[i]);
                cost = currcost + 1;
                
                if (cost < map_i64_get(knowncosts, next, worst_cost)) {
                    map_i64_set(knowncosts, next, cost);
                    priorityQ_i64_push_bbias(openset, cost, next);
                }
            }
        }
    }
    
    cost = map_i64_get(knowncosts, id_from_coord(x_size, y_size, end_x, end_y), worst_cost);

    priorityQ_i64_free(openset);
    map_i64_free(knowncosts);
    
    return cost;
}

static inline void find_char(char** data, size_t x_size, size_t y_size, int64_t* end_x, int64_t* end_y, char c) {
    for (int64_t y=0; y<y_size; ++y) {
        for (int64_t x=0; x<x_size; ++x) {
            if (data[y][x] == c) {
                *end_x = x;
                *end_y = y;
                return;
            }
        }
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    size_t x_size = strlen(data[0]) - 1;
    size_t y_size = data_size;
    int64_t end_x = -1, end_y = -1;
    int64_t p1_start_x = -1, p1_start_y = -1;
    
    find_char(data, x_size, y_size, &end_x, &end_y, 'E');
    find_char(data, x_size, y_size, &p1_start_x, &p1_start_y, 'S');
    
    assert(end_x != -1 && end_y != -1 && p1_start_x != -1 && p1_start_y != -1);
    
    *part1 = best_path_length(data, x_size, y_size, p1_start_x, p1_start_y, end_x, end_y, 1000000);
    *part2 = *part1;
    
    #pragma omp parallel for collapse(2)
    for (size_t y=0; y<y_size; ++y) {
        for (size_t x=0; x<x_size; ++x) {
            if (data[y][x] == 'a') {
                int64_t path = best_path_length(data, x_size, y_size, x, y, end_x, end_y, *part2);
                
                #pragma omp critical
                {
                    *part2 = min(path, *part2);
                }
            }
        }
    }
}
