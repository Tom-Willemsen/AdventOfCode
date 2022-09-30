#include "day17_impl.h"


static inline int64_t sum_0_to(int64_t x) {
    return (x * (x+1))/2;
}

void calculate(char* data, int64_t* part1, int64_t* part2) {
    int64_t min_target_x, max_target_x, min_target_y, max_target_y;
    int64_t initial_xv, initial_yv, xv, yv, x, y, max_y, s;
    int64_t valid = 0, best_y = 0;
    sscanf(data, "target area: x=%"SCNd64"..%"SCNd64", y=%"SCNd64"..%"SCNd64, 
               &min_target_x, &max_target_x, &min_target_y, &max_target_y);
    
    assert(min_target_x <= max_target_x);
    assert(min_target_y <= max_target_y);
    
    assert(max_target_y < 0);
    assert(min_target_x > 0);
    
    for (initial_yv=min_target_y; initial_yv <= -min_target_y; ++initial_yv) {
        for (initial_xv=1; initial_xv <= max_target_x; ++initial_xv) {
            max_y = 0;
            
            if (initial_yv > 0) {
                // Skip the top "half" of the ballistic curve by directly calculating where it
                // will re-cross the x-axis and starting from there instead.
                s = 2*initial_yv + 1;
                x = min(s, initial_xv) * initial_xv - sum_0_to(min(s, initial_xv)-1);
                y = 0;
                xv = max(initial_xv - s, 0);
                yv = -1*initial_yv - 1;
                max_y = sum_0_to(initial_yv);
            } else {
                x = 0;
                y = 0;
                xv = initial_xv;
                yv = initial_yv;
            }
            
            while(1) {
                x += xv;
                y += yv;
                
                yv--;
                if (xv > 0) {
                    xv--;
                }
                
                max_y = max(max_y, y);
                
                if (x >= min_target_x && y >= min_target_y && x <= max_target_x && y <= max_target_y) {
                    valid++;
                    best_y = max(best_y, max_y);
                    break;
                } else if ((y < min_target_y && yv < 0) || x > max_target_x || (xv == 0 && x < min_target_x)) {
                    break;
                }
            }
        }
    }
    
    *part1 = best_y;
    *part2 = valid;
}
