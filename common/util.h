#pragma once
#include <inttypes.h>

static inline int64_t min(int64_t x, int64_t y) {
    if (x > y) {
        return y;
    }
    return x;
}

static inline int64_t max(int64_t x, int64_t y) {
    if (x > y) {
        return x;
    }
    return y;
} 
