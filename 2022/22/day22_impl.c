#include "day22_impl.h"


static const int64_t X_DIRS[4] = {1, 0, -1, 0};
static const int64_t Y_DIRS[4] = {0, 1, 0, -1};


static void next_in_direction(list_tuple3_i64* teleport_sources, list_tuple3_i64* teleport_destinations, int64_t x, int64_t y, int64_t dir, int64_t* next_x, int64_t* next_y, int64_t* next_dir) {
    assert(dir >= 0 && dir < 4);
    
    x += X_DIRS[dir];
    y += Y_DIRS[dir];
    
    int64_t teleport_index = -1;
    
    // quick-n-dirty optimisation, we know the only portals are along these lines...
    if (i64modulo_positive(x, 50) == 0 || i64modulo_positive(x, 50) == 49 || i64modulo_positive(y, 50) == 0 || i64modulo_positive(y, 50) == 49) {
        teleport_index = list_tuple3_i64_last_indexof(teleport_sources, x, y, dir);
    }
    
    if (teleport_index == -1) {
        // no teleport
        *next_x = x;
        *next_y = y;
        *next_dir = dir;
    } else {
        list_tuple3_i64_get(teleport_destinations, teleport_index, next_x, next_y, next_dir);
    }
}

static int64_t simulate_path(set_tuple_i64* walls, list_tuple_i64* moves, list_tuple3_i64* teleport_sources, list_tuple3_i64* teleport_destinations) {
    int64_t dir = 0;
    
    // FIXME: non-general.
    int64_t x = 50;
    int64_t y = 0;
    
    for (uint64_t i=0; i<list_tuple_i64_size(moves); ++i) {
        int64_t move_dist, move_dir;
        list_tuple_i64_get(moves, i, &move_dist, &move_dir);
        
        for (uint64_t n=0; n<move_dist; ++n) {
            int64_t next_x, next_y, next_dir;
            next_in_direction(teleport_sources, teleport_destinations, x, y, dir, &next_x, &next_y, &next_dir);
            
            if (set_tuple_i64_contains(walls, next_x, next_y)) {
                break;
            }
            
            x = next_x;
            y = next_y;
            dir = next_dir;
        }
        
        dir = i64modulo_positive(dir + move_dir, 4);
    }
    
    return 1000 * (y + 1) + 4 * (x+1) + dir;
}

static void add_p1_teleports(list_tuple3_i64* sources, list_tuple3_i64* destinations) {
    // FIXME: this is non-general.
    
    // segment 1, left edge <-> segment 2, right edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 49, i, 2);
        list_tuple3_i64_push_back(destinations, 149, i, 2);
        
        list_tuple3_i64_push_back(sources, 150, i, 0);
        list_tuple3_i64_push_back(destinations, 50, i, 0);
    }
    
    // segment 3, left edge <-> segment 3, right edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 49, 50+i, 2);
        list_tuple3_i64_push_back(destinations, 99, 50+i, 2);
        
        list_tuple3_i64_push_back(sources, 100, 50+i, 0);
        list_tuple3_i64_push_back(destinations, 50, 50+i, 0);
    }
    
    // segment 4, left edge <-> segment 5, right edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, -1, 100+i, 2);
        list_tuple3_i64_push_back(destinations, 99, 100+i, 2);
        
        list_tuple3_i64_push_back(sources, 100, 100+i, 0);
        list_tuple3_i64_push_back(destinations, 0, 100+i, 0);
    }
    
    // segment 6, left edge <-> segment 6, right edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, -1, 150+i, 2);
        list_tuple3_i64_push_back(destinations, 49, 150+i, 2);
        
        list_tuple3_i64_push_back(sources, 50, 150+i, 0);
        list_tuple3_i64_push_back(destinations, 0, 150+i, 0);
    }
    
    // segment 4, top edge <-> segment 6, bottom edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, i, 99, 3);
        list_tuple3_i64_push_back(destinations, i, 199, 3);
        
        list_tuple3_i64_push_back(sources, i, 200, 1);
        list_tuple3_i64_push_back(destinations, i, 100, 1);
    }
    
    // segment 1, top edge <-> segment 5, bottom edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 50+i, -1, 3);
        list_tuple3_i64_push_back(destinations, 50+i, 149, 3);
        
        list_tuple3_i64_push_back(sources, 50+i, 150, 1);
        list_tuple3_i64_push_back(destinations, 50+i, 0, 1);
    }
    
    // segment 2, top edge <-> segment 2, bottom edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 100+i, -1, 3);
        list_tuple3_i64_push_back(destinations, 100+i, 49, 3);
        
        list_tuple3_i64_push_back(sources, 100+i, 50, 1);
        list_tuple3_i64_push_back(destinations, 100+i, 0, 1);
    }

}

static void add_p2_teleports(list_tuple3_i64* sources, list_tuple3_i64* destinations) {
    // FIXME: this is non-general.
    
    // segment 3, left edge <-> segment 4, top edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 49, 50+i, 2);
        list_tuple3_i64_push_back(destinations, i, 100, 1);
        
        list_tuple3_i64_push_back(sources, i, 99, 3);
        list_tuple3_i64_push_back(destinations, 50, 50+i, 0);
    }

    // segment 1, left edge <-> segment 4, left edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 49, i, 2);
        list_tuple3_i64_push_back(destinations, 0, 149-i, 0);
        
        list_tuple3_i64_push_back(sources, -1, 149-i, 2);
        list_tuple3_i64_push_back(destinations, 50, i, 0);
    }

    // segment 1, top edge <-> segment 6, left edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 50+i, -1, 3);
        list_tuple3_i64_push_back(destinations, 0, 150+i, 0);
        
        list_tuple3_i64_push_back(sources, -1, 150+i, 2);
        list_tuple3_i64_push_back(destinations, 50+i, 0, 1);
    }

    // segment 2, top edge <-> segment 6, bottom edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 100+i, -1, 3);
        list_tuple3_i64_push_back(destinations, i, 199, 3);
        
        list_tuple3_i64_push_back(sources, i, 200, 1);
        list_tuple3_i64_push_back(destinations, 100+i, 0, 1);
    }

    // segment 2, right edge <-> segment 5, right edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 150, 49-i, 0);
        list_tuple3_i64_push_back(destinations, 99, 100+i, 2);
        
        list_tuple3_i64_push_back(sources, 100, 100+i, 0);
        list_tuple3_i64_push_back(destinations, 149, 49-i, 2);
    }

    // segment 2, bottom edge <-> segment 3, right edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 100+i, 50, 1);
        list_tuple3_i64_push_back(destinations, 99, 50+i, 2);
        
        list_tuple3_i64_push_back(sources, 100, 50+i, 0);
        list_tuple3_i64_push_back(destinations, 100+i, 49, 3);
    }

    // segment 5, bottom edge <-> segment 6, right edge
    for (uint64_t i=0; i<50; ++i) {
        list_tuple3_i64_push_back(sources, 50+i, 150, 1);
        list_tuple3_i64_push_back(destinations, 49, 150+i, 2);
        
        list_tuple3_i64_push_back(sources, 50, 150+i, 0);
        list_tuple3_i64_push_back(destinations, 50+i, 149, 3);
    }
}


list_tuple_i64* parse_moves(char* moves) {
    char* curr_ptr = moves;
    char* next_ptr;
    int64_t n, d;
    list_tuple_i64* result = list_tuple_i64_init(1);
    
    while (1) {
        n = strtol(curr_ptr, &next_ptr, 10);
        if (curr_ptr == next_ptr) {
            break;
        }
        d = next_ptr[0];
        if (d == '\n') {
            d = 0;
        } else if (d == 'L') {
            d = -1;
        } else if (d == 'R') {
            d = 1;
        } else {
            assert(0);
        }
        next_ptr++;
        curr_ptr = next_ptr;
        list_tuple_i64_push_back(result, n, d);
    }
    return result;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    uint64_t max_x_size = 0;
    uint64_t max_y_size = data_size - 2;
    
    
    set_tuple_i64* walls = set_tuple_i64_init(16384);
    
    for (uint64_t y=0; y<max_y_size; ++y) {
        uint64_t x_data_len = strlen(data[y]) - 1;
        max_x_size = max(max_x_size, x_data_len);
        for (uint64_t x=0; x < x_data_len; ++x) {
            if(data[y][x] == '#') {
                set_tuple_i64_add(walls, x, y);
            }
        }
    }
    
    list_tuple_i64* moves = parse_moves(data[data_size-1]);
    assert(list_tuple_i64_size(moves) > 0);
    
    assert(max_x_size > 0);
    assert(max_y_size > 0);
    
    // Non-general assumptions: FIXME.
    assert(max_x_size % 50 == 0);
    assert(max_y_size % 50 == 0);
    
    list_tuple3_i64* teleport_sources = list_tuple3_i64_init(1);
    list_tuple3_i64* teleport_destinations = list_tuple3_i64_init(1);
    
    add_p1_teleports(teleport_sources, teleport_destinations);
    *part1 = simulate_path(walls, moves, teleport_sources, teleport_destinations);
    
    list_tuple3_i64_clear(teleport_sources);
    list_tuple3_i64_clear(teleport_destinations);
    
    add_p2_teleports(teleport_sources, teleport_destinations);
    *part2 = simulate_path(walls, moves, teleport_sources, teleport_destinations);
    
    list_tuple3_i64_free(teleport_destinations);
    list_tuple3_i64_free(teleport_sources);
    
    set_tuple_i64_free(walls);
    list_tuple_i64_free(moves);
}
