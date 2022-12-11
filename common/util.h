#pragma once
#include <inttypes.h>

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

[[nodiscard]] static inline int64_t min(int64_t x, int64_t y) {
    if (x > y) {
        return y;
    }
    return x;
}

[[nodiscard]] static inline int64_t max(int64_t x, int64_t y) {
    if (x > y) {
        return x;
    }
    return y;
} 

[[nodiscard]] static inline int64_t i64abs(int64_t x) {
    assert(x != INT64_MIN);
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

[[nodiscard]] static inline int64_t i64sign(int64_t x) {
    return (x>0) - (x<0);
}

// Computes x % y
// Only useful if this is *inside* a hot loop but y_inverse can be computed *outside* that hot loop - in which
// case it can outperform a simple x % y inside the loop.
[[nodiscard]] static inline int64_t i64_modulo_mulinv(int64_t x, int64_t y, double y_inverse) {
    return x - ((int64_t) (((double) x) * y_inverse)) * y;
}
