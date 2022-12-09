#include "day09_impl.h"

static const size_t NUM_KNOTS = 10;
static const size_t HEAD = 0;
static const size_t P1_TAIL = 1;
static const size_t P2_TAIL = 9;
static const int64_t GRID = 512;

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
    
    bitset* bs1 = bitset_init(GRID*GRID);
    bitset* bs2 = bitset_init(GRID*GRID);
    
    set_tuple_i64* s1 = set_tuple_i64_init(32);
    set_tuple_i64* s2 = set_tuple_i64_init(32);
    
    for (uint64_t i = 0; i < data_size; ++i) {
        sscanf(data[i], "%c %"SCNd64, &dir, &dist);
        assert(dist > 0);
        assert(dir == 'U' || dir == 'D' || dir == 'R' || dir == 'L');
        
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
            
            // hybrid approach seems to give best performance - use a bitset to capture squares between (256, 256) and (-256, -256)
            // a small number of points go outside this region, keep track of these using sets instead.
            // this also keeps the approach general - the 'rope' can stray outside the bitset region without affecting correctness.
            if (knots_x[P1_TAIL] >= (-GRID/2) && knots_x[P1_TAIL] < GRID/2 && knots_y[P1_TAIL] >= (-GRID/2) && knots_y[P1_TAIL] < GRID/2) {
                bitset_set(bs1, (GRID/2+knots_x[P1_TAIL])*GRID + GRID/2 + knots_y[P1_TAIL]);
            } else {
                set_tuple_i64_add(s1, knots_x[P1_TAIL], knots_y[P1_TAIL]);
            }
            
            if (knots_x[P2_TAIL] >= (-GRID/2) && knots_x[P2_TAIL] < GRID/2 && knots_y[P2_TAIL] >= (-GRID/2) && knots_y[P2_TAIL] < GRID/2) {
                bitset_set(bs2, (GRID/2+knots_x[P2_TAIL])*GRID + GRID/2 + knots_y[P2_TAIL]);
            } else {
                set_tuple_i64_add(s2, knots_x[P2_TAIL], knots_y[P2_TAIL]);
            }
        }
    }
    
    *part1 = bitset_popcnt(bs1) + set_tuple_i64_size(s1);
    *part2 = bitset_popcnt(bs2) + set_tuple_i64_size(s2);

    set_tuple_i64_free(s2);
    set_tuple_i64_free(s1);
    bitset_free(bs2);
    bitset_free(bs1);
}
