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

int64_t simulate(uint8_t* data, int64_t min_x, int64_t max_x, int64_t min_y, int64_t max_y, int64_t part) {
    int64_t x, y;
    int64_t created_sand = 0;
    uint8_t stop = 0;
    while (1) {
        created_sand++;
        stop = 0;
        
        if (data[map_index(SAND_START_X, SAND_START_Y, min_x, max_x, min_y, max_y)] == 's') {
            break;
        }
        
        x = SAND_START_X;
        y = SAND_START_Y;
        
        while (y <= max_y) {
            if (part == 1 && (x <= min_x || x >= max_x || y >= max_y)) {
                stop = 1;
                break;
            }
            if (y+1 <= max_y && data[map_index(x, y+1, min_x, max_x, min_y, max_y)] == ' ') {
                y++;
                continue;
            }
            if (y+1 <= max_y && x-1 >= min_x && data[map_index(x-1, y+1, min_x, max_x, min_y, max_y)] == ' ') {
                y++;
                x--;
                continue;
            }
            if (y+1 <= max_y && x+1 <= max_x && data[map_index(x+1, y+1, min_x, max_x, min_y, max_y)] == ' ') {
                y++;
                x++;
                continue;
            }

            if (y >= min_y && y <= max_y && x >= min_x && x <= max_x) {
                data[map_index(x, y, min_x, max_x, min_y, max_y)] = 's';
                break;
            } else {
                assert(0);
                stop = 1;
                break;
            }
        }
        if (stop) {
            break;
        }
    }
    return created_sand - 1;
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
    
    set_tuple_i64* points = set_tuple_i64_init(1024);
    
    for (uint64_t i=0; i<data_size; ++i) {
        parse_line(data[i], points);
    }
    
    set_tuple_i64_iterator* iter = set_tuple_i64_iter(points);
    while (set_tuple_i64_next(iter, &x, &y)) {
        min_x = min(x, min_x);
        max_x = max(x, max_x);
        min_y = min(y, min_y);
        max_y = max(y, max_y);
    }
    set_tuple_i64_iter_free(iter);
    
    min_y = min(min_y, SAND_START_Y);
    max_y = max(max_y, SAND_START_Y);
    
    max_y += 2;  // for part 2
    
    max_x = max(max_x, SAND_START_X + (max_y - min_y));
    min_x = min(min_x, SAND_START_X - (max_y - min_y));
    
    uint8_t* grid = malloc((max_x - min_x + 1) * (max_y - min_y + 1) * sizeof(uint8_t));
    memset(grid, ' ', (max_x - min_x + 1) * (max_y - min_y + 1) * sizeof(uint8_t));
    
    iter = set_tuple_i64_iter(points);
    while (set_tuple_i64_next(iter, &x, &y)) {
        grid[map_index(x, y, min_x, max_x, min_y, max_y)] = '#';
    }
    set_tuple_i64_iter_free(iter);
    set_tuple_i64_free(points);
    
    *part1 = simulate(grid, min_x, max_x, min_y, max_y, 1);
    
    for (y=min_y; y<=max_y; ++y) {
        for (x=min_x; x<=max_x; ++x) {
            if(grid[map_index(x, y, min_x, max_x, min_y, max_y)] == 's') {
                grid[map_index(x, y, min_x, max_x, min_y, max_y)] = ' ';
            }
        }
    }
    
    for (x=min_x; x<=max_x; ++x) {
        grid[map_index(x, max_y, min_x, max_x, min_y, max_y)] = '#';
    }
    
    *part2 = simulate(grid, min_x, max_x, min_y, max_y, 2);
    
    free(grid);
}
