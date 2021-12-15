#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include "list.h"
#include "util.h"

typedef struct set_i64 {
    uint64_t n_buckets;
    list_i64** buckets;
} set_i64;

static set_i64* set_i64_init (uint64_t n_buckets) {
    set_i64* set = calloc(1, sizeof(set_i64));
    assert(n_buckets > 0);
    set->n_buckets = n_buckets;
    set->buckets = calloc(n_buckets, sizeof(list_i64*));
    
    for (uint64_t i=0; i<n_buckets; ++i) {
        set->buckets[i] = NULL;
    }
    return set;
}

static void set_i64_free(set_i64* set) {
    for (uint64_t i=0; i<set->n_buckets; ++i) {
        if (set->buckets[i] != NULL) {
            list_i64_free(set->buckets[i]);
        }
    }
    free(set->buckets);
    free(set);
}

static inline uint64_t set_i64_hashfunction(uint64_t n_buckets, int64_t item) {
    return i64abs(item) % n_buckets;
}

static inline list_i64* set_i64_get_or_create_bucket(set_i64* set, int64_t value) {
    uint64_t bucket = set_i64_hashfunction(set->n_buckets, value);
    if (set->buckets[bucket] == NULL) {
        set->buckets[bucket] = list_i64_init(1);
    }
    return set->buckets[bucket];
}

static inline list_i64* set_i64_maybe_get_bucket(set_i64* set, int64_t value) {
    uint64_t bucket = set_i64_hashfunction(set->n_buckets, value);
    return set->buckets[bucket];
}

static int64_t set_i64_add(set_i64* set, int64_t value) {
    list_i64* bucket = set_i64_get_or_create_bucket(set, value);
    if (!list_i64_contains(bucket, value)) {
        list_i64_push_back(bucket, value);
        return 1;
    }
    return 0;
}

static int64_t set_i64_contains(set_i64* set, int64_t value) {
    list_i64* bucket = set_i64_maybe_get_bucket(set, value);
    return bucket != NULL && list_i64_contains(bucket, value);
}

static int64_t set_i64_remove(set_i64* set, int64_t value) {
    list_i64* bucket = set_i64_maybe_get_bucket(set, value);
    if (bucket == NULL) {
        return 0;
    }
    int64_t index = list_i64_indexof(bucket, value);
    if (index != -1) {
        list_i64_remove(bucket, index);
        return 1;
    }
    return 0;
}