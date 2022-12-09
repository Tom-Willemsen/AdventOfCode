#include "day09_impl.h"

static const int64_t NUM_KNOTS = 10;

static void update_knots(list_tuple_i64* knots) {
    for (int64_t k=NUM_KNOTS-2; k>=0; --k) {
        int64_t xprev, yprev, x, y;
        list_tuple_i64_get(knots, k+1, &xprev, &yprev);
        list_tuple_i64_get(knots, k, &x, &y);
        
        if (!(xprev + 1 >= x && xprev - 1 <= x && yprev + 1 >= y && yprev - 1 <= y)) {
            if (x < xprev) {
                x++;
            } else if (x > xprev) {
                x--;
            }
            
            if (y < yprev) {
                y++;
            } else if (y > yprev) {
                y--;
            }
            list_tuple_i64_set(knots, k, x, y);
        } else {
            break;
        }
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    char dir;
    int64_t dist, head_x, head_y, x, y;
    
    list_tuple_i64* knots = list_tuple_i64_init(NUM_KNOTS);
    
    set_tuple3_i64* s1 = set_tuple3_i64_init(1024);
    set_tuple3_i64* s2 = set_tuple3_i64_init(1024);
    
    for (int64_t k=0; k<NUM_KNOTS; ++k) {
        list_tuple_i64_push_back(knots, 0, 0);
    }
    
    for (uint64_t i = 0; i < data_size; ++i) {
        sscanf(data[i], "%c %"SCNd64, &dir, &dist);
        assert(dist > 0);
        assert(dir == 'U' || dir == 'D' || dir == 'R' || dir == 'L');
        
        for (int64_t d=0; d<dist; ++d) {
            list_tuple_i64_get(knots, NUM_KNOTS-1, &head_x, &head_y);
            if (dir == 'U') {
                list_tuple_i64_set(knots, NUM_KNOTS-1, head_x, head_y + 1);
            } else if (dir == 'D') {
                list_tuple_i64_set(knots, NUM_KNOTS-1, head_x, head_y - 1);
            } else if (dir == 'R') {
                list_tuple_i64_set(knots, NUM_KNOTS-1, head_x + 1, head_y);
            } else {
                list_tuple_i64_set(knots, NUM_KNOTS-1, head_x - 1, head_y);
            } 
            update_knots(knots);
            
            list_tuple_i64_get(knots, NUM_KNOTS-2, &x, &y);
            set_tuple3_i64_add(s1, 0, x, y);
            
            list_tuple_i64_get(knots, 0, &x, &y);
            set_tuple3_i64_add(s2, 0, x, y);
        }
    }
    
    *part1 = set_tuple3_i64_size(s1);
    *part2 = set_tuple3_i64_size(s2);
    
    set_tuple3_i64_free(s1);
    set_tuple3_i64_free(s2);
    list_tuple_i64_free(knots);
}
