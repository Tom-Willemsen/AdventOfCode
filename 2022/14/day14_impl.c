#include "day14_impl.h"

#define SAND_START_X 500
#define SAND_START_Y 0

static inline size_t map_index(int64_t x, int64_t y, int64_t min_x, int64_t max_x, int64_t min_y, int64_t max_y) {
    assert(x >= min_x);
    assert(x <= max_x);    
    assert(y >= min_y);
    assert(y <= max_y);
    return (y-min_y)*(max_x-min_x) + (x-min_x);
}

static int64_t simulate(set_tuple_i64* walls, int64_t min_x, int64_t max_x, int64_t min_y, int64_t max_y, int64_t part) {
    int64_t x, y;
    int64_t result;
    int64_t max_visit_size = 0;
    
    list_tuple_i64* to_visit = list_tuple_i64_init(256);
    
    list_tuple_i64_push_back(to_visit, SAND_START_X, SAND_START_Y);
    
    bitset* visited = bitset_init(map_index(max_x, max_y, min_x, max_x, min_y, max_y) /* largest place we might try to index */ + 1);
    
    bitset* walls_bs = bitset_init(map_index(max_x, max_y, min_x, max_x, min_y, max_y) /* largest place we might try to index */ + 1);
    
    set_tuple_i64_iterator* iter = set_tuple_i64_iter(walls);
    while (set_tuple_i64_next(iter, &x, &y)) {
        bitset_set(walls_bs, map_index(x, y, min_x, max_x, min_y, max_y));
    }
    set_tuple_i64_iter_free(iter);
    
    while (list_tuple_i64_size(to_visit)) {
        max_visit_size = max(max_visit_size, list_tuple_i64_size(to_visit));
        list_tuple_i64_pop_back(to_visit, &x, &y);
        
        if (y>=max_y) {
            break;
        }
        
        size_t index = map_index(x, y, min_x, max_x, min_y, max_y);
        if (bitset_get(visited, index)) {
            continue;
        }
        
        bitset_set(visited, index);
        
        if (y+1 <= max_y && x+1 && !bitset_get(walls_bs, map_index(x+1, y+1, min_x, max_x, min_y, max_y))) {
            list_tuple_i64_push_back(to_visit, x+1, y+1);
        }
        
        if (y+1 <= max_y && x-1 && !bitset_get(walls_bs, map_index(x-1, y+1, min_x, max_x, min_y, max_y))) {
            list_tuple_i64_push_back(to_visit, x-1, y+1);
        }
        
        if (y+1 <= max_y && !bitset_get(walls_bs, map_index(x, y+1, min_x, max_x, min_y, max_y))) {
            list_tuple_i64_push_back(to_visit, x, y+1);
        }
    }
    
    result = bitset_popcnt(visited);
    bitset_free(visited);
    bitset_free(walls_bs);
    list_tuple_i64_free(to_visit);
    
    if (part == 1) {
        // In part 1, the last piece of sand to fall will have visited every y coordinate
        // and not come to rest. Hence we need to reduce the visited squares by (max_y-min_y)
        return result - (max_y - min_y);
    } else {
        // In part 2, everything will have come to rest, just count all visited squares.
        return result;
    }
}


void parse_line(char* data, set_tuple_i64* points) {
    assert(data != NULL);
    char* parsed = data;
    int64_t newx=INT64_MIN, newy=INT64_MIN;
    int64_t oldx=INT64_MIN, oldy=INT64_MIN;
    
    while (parsed[0] != '\n') {
        if (parsed[0] == ' ') {
            parsed += 4; // " -> "
        }
        
        newx = strtol(parsed, &parsed, 10);
        parsed++;  // ','
        newy = strtol(parsed, &parsed, 10);
        
        if (oldx != INT64_MIN && oldy != INT64_MIN) {
            if (oldx == newx) {
                if (newy > oldy) {
                    for (int64_t y=oldy; y<=newy; ++y) {
                        set_tuple_i64_add(points, oldx, y);
                    }
                } else {
                    for (int64_t y=oldy; y>=newy; --y) {
                        set_tuple_i64_add(points, oldx, y);
                    }
                }
            } else {
                if (newx > oldx) {
                    for (int64_t x=oldx; x<=newx; ++x) {
                        set_tuple_i64_add(points, x, oldy);
                    }
                } else {
                    for (int64_t x=oldx; x>=newx; --x) {
                        set_tuple_i64_add(points, x, oldy);
                    }
                }
            }
        }
        
        oldx = newx;
        oldy = newy;
    }
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    
    int64_t min_x = INT64_MAX, min_y = INT64_MAX, max_x = INT64_MIN, max_y = INT64_MIN;
    int64_t x = 0, y = 0;
    
    set_tuple_i64* walls = set_tuple_i64_init(1024);
    
    for (uint64_t i=0; i<data_size; ++i) {
        parse_line(data[i], walls);
    }
    
    set_tuple_i64_iterator* iter = set_tuple_i64_iter(walls);
    while (set_tuple_i64_next(iter, &x, &y)) {
        min_x = min(x, min_x);
        max_x = max(x, max_x);
        min_y = min(y, min_y);
        max_y = max(y, max_y);
    }
    set_tuple_i64_iter_free(iter);
    
    min_y = min(min_y, SAND_START_Y);
    max_y = max(max_y, SAND_START_Y);
    
    max_x = max(max_x, SAND_START_X + (max_y - min_y));
    min_x = min(min_x, SAND_START_X - (max_y - min_y));
    
    *part1 = simulate(walls, min_x, max_x, min_y, max_y, 1);
    
    for (x=min_x-2; x<=max_x+2; ++x) {
        set_tuple_i64_add(walls, x, max_y+2);
    }
    
    *part2 = simulate(walls, min_x-2, max_x+2, min_y, max_y+2, 2);
    
    set_tuple_i64_free(walls);
}
