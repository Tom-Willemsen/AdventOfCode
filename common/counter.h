#pragma once

#include "list.h"

typedef struct counter_i64 {
    list_i64* keys;
    list_i64* values;
} counter_i64;

static counter_i64* counter_i64_init(uint64_t initial_capacity) {
    counter_i64* counter = calloc(1, sizeof(counter_i64));
    counter->keys = list_i64_init(initial_capacity);
    counter->values = list_i64_init(initial_capacity);
    return counter;
}

static void counter_i64_free(counter_i64* counter) {
    list_i64_free(counter->keys);
    list_i64_free(counter->values);
    free(counter);
}

static inline void counter_i64_clear(counter_i64* counter) {
    list_i64_clear(counter->keys);
    list_i64_clear(counter->values);
}

static inline uint64_t counter_i64_size(counter_i64* counter) {
    assert(list_i64_size(counter->keys) == list_i64_size(counter->values));
    return list_i64_size(counter->keys);
}

static int64_t counter_i64_get(counter_i64* counter, int64_t key) {
    for (uint64_t i=0; i<counter_i64_size(counter); ++i) {
        if (list_i64_get(counter->keys, i) == key) {
            return list_i64_get(counter->values, i);
        }
    }
    return 0;
}

static inline void counter_i64_get_by_index(counter_i64* counter, int64_t index, int64_t* key, int64_t* value) {
    *key = list_i64_get(counter->keys, index);
    *value = list_i64_get(counter->values, index);
}

static void counter_i64_set(counter_i64* counter, int64_t key, int64_t value) {
    for (uint64_t i=0; i<counter_i64_size(counter); ++i) {
        if (list_i64_get(counter->keys, i) == key) {
            list_i64_set(counter->values, i, value);
            return;
        }
    }
    list_i64_push_back(counter->keys, key);
    list_i64_push_back(counter->values, value);
}

static void counter_i64_incrementby(counter_i64* counter, int64_t key, int64_t x) {
    int64_t index = list_i64_indexof(counter->keys, key);
    if (index != -1) {
        list_i64_set(counter->values, index, list_i64_get(counter->values, index) + x);
    } else {
        list_i64_push_back(counter->keys, key);
        list_i64_push_back(counter->values, x);
    }
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

static int64_t counter_i64_max(counter_i64* counter) {
    return list_i64_max(counter->values);
}

static int64_t counter_i64_min(counter_i64* counter) {
    return list_i64_min(counter->values);
}
