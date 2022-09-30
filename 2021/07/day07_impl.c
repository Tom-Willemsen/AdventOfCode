#include "day07_impl.h"

static inline int64_t p1cost(int64_t dist) {
    return dist;
}

static inline int64_t p2cost(int64_t dist) {
    return (dist * (dist + 1)) / 2;
}

static inline int64_t calculate(list_i64* positions, int64_t (*costfunction)(int64_t)) {
    int64_t mincost = INT64_MAX, cost, diff;
    int64_t minpos = list_i64_min(positions);
    int64_t maxpos = list_i64_max(positions);
    
    for (int64_t pos=minpos; pos<maxpos; ++pos) {
        cost = 0;
        for (int64_t i=0; i<positions->size; ++i) {
            diff = labs(pos - list_i64_get(positions, i));
            cost += (*costfunction)(diff);
        }
        if (cost < mincost) {
            mincost = cost;
        } else {
            break;
        }
    }
    return mincost;
}

int64_t part1(list_i64* positions) {
    return calculate(positions, p1cost);
}

int64_t part2(list_i64* positions) {
    return calculate(positions, p2cost);
}
