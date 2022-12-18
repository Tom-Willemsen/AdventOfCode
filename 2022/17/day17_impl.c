#include "day17_impl.h"

#define NUM_ROCKS (5)

#define ROCK1_X (4)
#define ROCK1_Y (1)
static const uint8_t ROCK1[ROCK1_Y*ROCK1_X] = { 1, 1, 1, 1 };

#define ROCK2_X (3)
#define ROCK2_Y (3)
static const uint8_t ROCK2[ROCK2_Y*ROCK2_X] = { 0, 1, 0, 1, 1, 1, 0, 1, 0 };

#define ROCK3_X (3)
#define ROCK3_Y (3)
static const uint8_t ROCK3[ROCK3_Y*ROCK3_X] = { 1, 1, 1, 0, 0, 1, 0, 0, 1 };

#define ROCK4_X (1)
#define ROCK4_Y (4)
static const uint8_t ROCK4[ROCK4_Y*ROCK4_X] = { 1, 1, 1, 1 };

#define ROCK5_X (2)
#define ROCK5_Y (2)
static const uint8_t ROCK5[ROCK5_Y*ROCK5_X] = { 1, 1, 1, 1 };

static const uint8_t* ROCKS[NUM_ROCKS] = { &ROCK1[0], &ROCK2[0], &ROCK3[0], &ROCK4[0], &ROCK5[0] };
static const int64_t ROCK_X_SIZES[NUM_ROCKS] = { ROCK1_X, ROCK2_X, ROCK3_X, ROCK4_X, ROCK5_X };
static const int64_t ROCK_Y_SIZES[NUM_ROCKS] = { ROCK1_Y, ROCK2_Y, ROCK3_Y, ROCK4_Y, ROCK5_Y };

#define MAX_CYCLE_LENGTH (32768)


typedef struct rockfall_state {
    uint64_t gust_number;
    uint64_t rock_number;
    int64_t height;
    bitset* top30_rows_state;
} rockfall_state;


static int64_t height_after_n_rocks(uint64_t n_rocks, uint64_t num_gusts, char* gusts) {
    uint64_t rock_number = 0;
    uint64_t gust_number = 0;
    int64_t max_height = 0;
    int64_t x, y, rock_x_dim, rock_y_dim, gas_push_direction, do_move, landed;
    int64_t cycle_length, cycle_score;
    uint64_t n;
    
    set_tuple_i64* occupied = set_tuple_i64_init(65536);
    
    rockfall_state state_cache[MAX_CYCLE_LENGTH];
    
    for (n=0; n<MAX_CYCLE_LENGTH; ++n) {
        rock_number = n % NUM_ROCKS;
        
        rock_x_dim = ROCK_X_SIZES[rock_number];
        rock_y_dim = ROCK_Y_SIZES[rock_number];
        
        x = 2;
        y = max_height + 4;
        landed = 0;
        
        while (!landed) {
            gas_push_direction = gusts[gust_number] == '>' ? 1 : -1;
            gust_number++;
            gust_number %= num_gusts;
            
            do_move = 0;
            
            if (x+gas_push_direction >= 0 && x + rock_x_dim + gas_push_direction <= 7) {
                do_move = 1;
                for (uint64_t rx=0; rx<rock_x_dim; ++rx) {
                    for (uint64_t ry=0; ry<rock_y_dim; ++ry) {
                        if (ROCKS[rock_number][ry * rock_x_dim + rx] && set_tuple_i64_contains(occupied, x + rx + gas_push_direction, y + ry)) {
                            do_move = 0;
                        }
                    }
                }
            }
        
            if (do_move) {
                x += gas_push_direction;
            }
            
            landed = y-1 <= 0;
            if (!landed) {
                for (uint64_t rx=0; rx<rock_x_dim; ++rx) {
                    for (uint64_t ry=0; ry<rock_y_dim; ++ry) {
                        if (ROCKS[rock_number][ry * rock_x_dim + rx] && (y + ry -1 <= 0 || set_tuple_i64_contains(occupied, x + rx, y + ry - 1))) {
                            landed = 1;
                        }
                    }
                }
            }
            
            if (landed) {
                for (uint64_t rx=0; rx<rock_x_dim; ++rx) {
                    for (uint64_t ry=0; ry<rock_y_dim; ++ry) {
                        if (ROCKS[rock_number][ry * rock_x_dim + rx]) {
                            set_tuple_i64_add(occupied, x + rx, y + ry);
                            max_height = max(max_height, y + ry);
                        }
                    }
                }
            } else {
                y--;
            }
        }
        
        state_cache[n].gust_number = gust_number;
        state_cache[n].rock_number = rock_number;
        state_cache[n].height = max_height;
        state_cache[n].top30_rows_state = bitset_init(256);
        
        for (uint64_t ry=max_height; ry>max_height-30; --ry) {
            for (uint64_t rx=0; rx<7; ++rx) {
                if (set_tuple_i64_contains(occupied, rx, ry)) {
                    bitset_set(state_cache[n].top30_rows_state, (max_height - ry) * 7 + rx);
                }
            }
        }
        
        if (n > 0 && n%2 == 0) {
            if (state_cache[n].gust_number == state_cache[n/2].gust_number
                && state_cache[n].rock_number == state_cache[n/2].rock_number
                && bitset_equals(state_cache[n].top30_rows_state, state_cache[n/2].top30_rows_state)
            ) {
                cycle_length = n/2;
                cycle_score = state_cache[n].height - state_cache[n/2].height;
                break;
            }
        }
    }    
    for (int64_t i=0; i<=n; ++i) {
        bitset_free(state_cache[i].top30_rows_state);
    }
    set_tuple_i64_free(occupied);
    
    return cycle_score * ((n_rocks/cycle_length)-1) + state_cache[(cycle_length + n_rocks % cycle_length)-1].height;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    assert(data_size == 1);
    uint64_t num_gusts = strlen(data[0]) - 1;
    
    *part1 = height_after_n_rocks(2022, num_gusts, data[0]);
    *part2 = height_after_n_rocks(1000000000000, num_gusts, data[0]);
}
