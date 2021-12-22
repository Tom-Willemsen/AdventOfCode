#pragma once

#include "map.h"

typedef struct counter_i64 {
    map_i64* map;
} counter_i64;

static counter_i64* counter_i64_init(uint64_t n_buckets) {
    counter_i64* counter = calloc(1, sizeof(counter_i64));
    counter->map = map_i64_init(n_buckets);
    return counter;
}

static void counter_i64_free(counter_i64* counter) {
    map_i64_free(counter->map);
    free(counter);
}

// static inline void counter_i64_clear(counter_i64* counter) {
//     map_i64_clear(counter->map);
// }

static inline uint64_t counter_i64_size(counter_i64* counter) {
    return map_i64_size(counter->map);
}

static int64_t counter_i64_get(counter_i64* counter, int64_t key) {
    return map_i64_get(counter->map, key, 0);
}

static void counter_i64_set(counter_i64* counter, int64_t key, int64_t value) {
    map_i64_set(counter->map, key, value);
}

static void counter_i64_incrementby(counter_i64* counter, int64_t key, int64_t x) {
    int64_t value = counter_i64_get(counter, key) + x;
    counter_i64_set(counter, key, value);
}

static void counter_i64_decrementby(counter_i64* counter, int64_t key, int64_t x) {
    counter_i64_incrementby(counter, key, -x);
}

static void counter_i64_increment(counter_i64* counter, int64_t key) {
    counter_i64_incrementby(counter, key, 1);
}

static void counter_i64_decrement(counter_i64* counter, int64_t key) {
    counter_i64_incrementby(counter, key, -1);
}

typedef struct counter_i64_iterator {
    counter_i64* counter;
    uint64_t bucket;
    uint64_t idx;
} counter_i64_iterator;

static counter_i64_iterator* counter_i64_iter(counter_i64* counter) {
    counter_i64_iterator* iter = calloc(1, sizeof(counter_i64_iterator));
    iter->counter = counter;
    iter->bucket = 0;
    iter->idx = 0;
    return iter;
}

static void counter_i64_iter_free(counter_i64_iterator* iter) {
    free(iter);
}

static int64_t counter_i64_next(counter_i64_iterator* iter, int64_t* key, int64_t* value) {
    uint64_t idx = iter->idx;
    for (uint64_t bucket=iter->bucket; bucket < iter->counter->map->n_buckets; ++bucket) {
        if (iter->counter->map->buckets[bucket] == NULL) {
            continue;
        }
        for (uint64_t i=idx; i<list_tuple_i64_size(iter->counter->map->buckets[bucket]); ++i) {
            iter->bucket = bucket;
            iter->idx = i + 1;
            list_tuple_i64_get(iter->counter->map->buckets[bucket], i, key, value);
            return 1;
        }
        idx = 0;
    }
    *key = 0xBADBADBADBAD;
    *value = 0xBADBADBADBAD;
    return 0;
}

static int64_t counter_i64_max(counter_i64* counter) {
    int64_t result = INT64_MIN, key, value;
    counter_i64_iterator* iter = counter_i64_iter(counter);
    while (counter_i64_next(iter, &key, &value)) {
        result = max(result, value);
    }
    counter_i64_iter_free(iter);
    return result;
}

static int64_t counter_i64_min(counter_i64* counter) {
    int64_t result = INT64_MAX, key, value;
    counter_i64_iterator* iter = counter_i64_iter(counter);
    while (counter_i64_next(iter, &key, &value)) {
        result = min(result, value);
    }
    counter_i64_iter_free(iter);
    return result;
}
