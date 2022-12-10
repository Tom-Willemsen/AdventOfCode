#include "day09_impl.h"

#define NUM_KNOTS 10
#define HEAD 0
#define P1_TAIL 1
#define P2_TAIL 9

static void update_knots(int64_t* knots_x, int64_t* knots_y) {
    for (size_t k=1; k<NUM_KNOTS; ++k) {
        int64_t dx = knots_x[k-1] - knots_x[k];
        int64_t dy = knots_y[k-1] - knots_y[k];
        
        if (i64abs(dx) > 1 || i64abs(dy) > 1) {
            knots_x[k] += i64sign(dx);
            knots_y[k] += i64sign(dy);
        } else {
            return;
        }
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    char dir;
    int64_t dist;
    
    int64_t knots_x[NUM_KNOTS] = {0};
    int64_t knots_y[NUM_KNOTS] = {0};
    
    int64_t min_x=0, min_y=0, max_x=0, max_y=0, x=0, y=0;
    
    char* dirs = calloc(data_size, sizeof(char));
    int64_t* dists = calloc(data_size, sizeof(int64_t));
    
    // Precompute needed grid size
    for (uint64_t i = 0; i < data_size; ++i) {
        dir = data[i][0];
        dist = strtol(data[i]+2, NULL, 10);
        dirs[i] = dir;
        dists[i] = dist;
        if (dir == 'U') {
            y += dist;
        } else if (dir == 'D') {
            y -= dist;
        } else if (dir == 'R') {
            x += dist;
        } else {
            x -= dist;
        }
        min_x = min(min_x, x);
        max_x = max(max_x, x);
        min_y = min(min_y, y);
        max_y = max(max_y, y);
    }
    
    max_x++;
    max_y++;
    
    bitset* bs1 = bitset_init((max_x-min_x)*(max_y-min_y));
    bitset* bs2 = bitset_init((max_x-min_x)*(max_y-min_y));
    
    for (uint64_t i = 0; i < data_size; ++i) {
        dir = dirs[i];
        dist = dists[i];
        
        for (int64_t d=0; d<dist; ++d) {
            if (dir == 'U') {
                knots_y[HEAD] += 1;
            } else if (dir == 'D') {
                knots_y[HEAD] -= 1;
            } else if (dir == 'R') {
                knots_x[HEAD] += 1;
            } else {
                knots_x[HEAD] -= 1;
            } 
            update_knots(knots_x, knots_y);
            
            bitset_set(bs1, (knots_x[P1_TAIL]-min_x)*(max_y-min_y) + knots_y[P1_TAIL] - min_y);
            bitset_set(bs2, (knots_x[P2_TAIL]-min_x)*(max_y-min_y) + knots_y[P2_TAIL] - min_y);
        }
    }
    
    free(dists);
    free(dirs);
    
    *part1 = bitset_popcnt(bs1);
    *part2 = bitset_popcnt(bs2);

    bitset_free(bs2);
    bitset_free(bs1);
}
