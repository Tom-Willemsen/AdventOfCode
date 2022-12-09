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
