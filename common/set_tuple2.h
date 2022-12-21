#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include "list_tuple2.h"
#include "util.h"
#include "libdivide.h"

typedef struct set_tuple_i64 {
    uint64_t n_buckets;
    list_tuple_i64** buckets;
    struct libdivide_s64_t buckets_fast_divisor;
} set_tuple_i64;

static set_tuple_i64* set_tuple_i64_init (uint64_t n_buckets) {
    set_tuple_i64* set = calloc(1, sizeof(set_tuple_i64));
    assert(n_buckets > 0);
    set->n_buckets = n_buckets;
    set->buckets_fast_divisor = libdivide_s64_gen(n_buckets);
    set->buckets = calloc(n_buckets, sizeof(list_tuple_i64*));
    
    for (uint64_t i=0; i<n_buckets; ++i) {
        set->buckets[i] = NULL;
    }
    return set;
}

static void set_tuple_i64_free(set_tuple_i64* set) {
    for (uint64_t i=0; i<set->n_buckets; ++i) {
        if (set->buckets[i] != NULL) {
            list_tuple_i64_free(set->buckets[i]);
        }
    }
    free(set->buckets);
    free(set);
}

static inline uint64_t set_tuple_i64_hashfunction(set_tuple_i64* set, int64_t x, int64_t y) {
    int64_t key = i64abs(193 * x + y);
    return key - libdivide_s64_do(key, &set->buckets_fast_divisor) * set->n_buckets;
}

static inline list_tuple_i64* set_tuple_i64_get_or_create_bucket(set_tuple_i64* set, int64_t x, int64_t y) {
    uint64_t bucket = set_tuple_i64_hashfunction(set, x, y);
    if (set->buckets[bucket] == NULL) {
        set->buckets[bucket] = list_tuple_i64_init(1);
    }
    return set->buckets[bucket];
}

static inline list_tuple_i64* set_tuple_i64_maybe_get_bucket(set_tuple_i64* set, int64_t x, int64_t y) {
    uint64_t bucket = set_tuple_i64_hashfunction(set, x, y);
    return set->buckets[bucket];
}

static int64_t set_tuple_i64_add(set_tuple_i64* set, int64_t x, int64_t y) {
    list_tuple_i64* bucket = set_tuple_i64_get_or_create_bucket(set, x, y);
    if (!list_tuple_i64_contains(bucket, x, y)) {
        list_tuple_i64_push_back(bucket, x, y);
        return 1;
    }
    return 0;
}

static void set_tuple_i64_add_all(set_tuple_i64* set, list_tuple_i64* to_add) {
    for (uint64_t i=0; i<list_tuple_i64_size(to_add); ++i) {
        int64_t x, y;
        list_tuple_i64_get(to_add, i, &x, &y);
        set_tuple_i64_add(set, x, y);
    }
}

static int64_t set_tuple_i64_contains(set_tuple_i64* set, int64_t x, int64_t y) {
    list_tuple_i64* bucket = set_tuple_i64_maybe_get_bucket(set, x, y);
    return bucket != NULL && list_tuple_i64_contains(bucket, x, y);
}

static int64_t set_tuple_i64_remove(set_tuple_i64* set, int64_t x, int64_t y) {
    list_tuple_i64* bucket = set_tuple_i64_maybe_get_bucket(set, x, y);
    if (bucket == NULL) {
        return 0;
    }
    int64_t index = list_tuple_i64_last_indexof(bucket, x, y);
    if (index != -1) {
        list_tuple_i64_remove(bucket, index);
        return 1;
    }
    return 0;
}

static int64_t set_tuple_i64_size(set_tuple_i64* set) {
    int64_t size = 0;
    for (uint64_t i=0; i<set->n_buckets; ++i) {
        if (set->buckets[i] != NULL) {
            size += list_tuple_i64_size(set->buckets[i]);
        }
    }
    return size;
}


typedef struct set_tuple_i64_iterator {
    set_tuple_i64* set;
    uint64_t bucket;
    uint64_t idx;
} set_tuple_i64_iterator;

static set_tuple_i64_iterator* set_tuple_i64_iter(set_tuple_i64* set) {
    set_tuple_i64_iterator* iter = calloc(1, sizeof(set_tuple_i64_iterator));
    iter->set = set;
    iter->bucket = 0;
    iter->idx = 0;
    return iter;
}

static void set_tuple_i64_iter_free(set_tuple_i64_iterator* iter) {
    free(iter);
}

static int64_t set_tuple_i64_next(set_tuple_i64_iterator* iter, int64_t* x, int64_t* y) {
    uint64_t idx = iter->idx;
    for (uint64_t bucket=iter->bucket; bucket < iter->set->n_buckets; ++bucket) {
        if (iter->set->buckets[bucket] == NULL) {
            continue;
        }
        for (uint64_t i=idx; i<list_tuple_i64_size(iter->set->buckets[bucket]); ++i) {
            iter->bucket = bucket;
            iter->idx = i + 1;
            list_tuple_i64_get(iter->set->buckets[bucket], i, x, y);
            return 1;
        }
        idx = 0;
    }
    *x = 0xBADBADBADBAD;
    *y = 0xBADBADBADBAD;
    return 0;
}

