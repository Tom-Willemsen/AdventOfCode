#pragma once
#include "list_tuple2.h"
#include "util.h"
#include "libdivide.h"

typedef struct map_i64 {
    uint64_t n_buckets;
    list_tuple_i64** buckets;
    struct libdivide_s64_t buckets_fast_divisor;
} map_i64;

static map_i64* map_i64_init(uint64_t n_buckets) {
    map_i64* map = calloc(1, sizeof(map_i64));
    assert(n_buckets > 0);
    map->n_buckets = n_buckets;
    map->buckets_fast_divisor = libdivide_s64_gen(n_buckets);
    map->buckets = calloc(n_buckets, sizeof(list_tuple_i64*));
    
    for (uint64_t i=0; i<n_buckets; ++i) {
        map->buckets[i] = NULL;
    }
    return map;
}

static void map_i64_free(map_i64* map) {
    for (uint64_t i=0; i<map->n_buckets; ++i) {
        if (map->buckets[i] != NULL) {
            list_tuple_i64_free(map->buckets[i]);
        }
    }
    free(map->buckets);
    free(map);
}

static void map_i64_clear(map_i64* map) {
    for (uint64_t i=0; i<map->n_buckets; ++i) {
        if (map->buckets[i] != NULL) {
            list_tuple_i64_free(map->buckets[i]);
        }
        map->buckets[i] = NULL;
    }
}

static uint64_t map_i64_size(map_i64* map) {
    uint64_t result = 0;
    for (uint64_t i=0; i<map->n_buckets; ++i) {
        if (map->buckets[i] != NULL) {
            result += list_tuple_i64_size(map->buckets[i]);
        }
    }
    return result;
}

static inline uint64_t map_i64_hashfunction(map_i64* map, int64_t key) {
    return key - libdivide_s64_do(key, &map->buckets_fast_divisor) * map->n_buckets;
}

static inline list_tuple_i64* map_i64_get_or_create_bucket(map_i64* map, int64_t key) {
    uint64_t bucket = map_i64_hashfunction(map, key);
    if (map->buckets[bucket] == NULL) {
        map->buckets[bucket] = list_tuple_i64_init(2);
    }
    return map->buckets[bucket];
}

static inline list_tuple_i64* map_i64_maybe_get_bucket(map_i64* map, int64_t key) {
    uint64_t bucket = map_i64_hashfunction(map, key);
    return map->buckets[bucket];
}

static void map_i64_set(map_i64* map, int64_t key, int64_t value) {
    int64_t k, v;
    list_tuple_i64* bucket = map_i64_get_or_create_bucket(map, key);
    for (uint64_t i=0; i<list_tuple_i64_size(bucket); ++i) {
        list_tuple_i64_get(bucket, i, &k, &v);
        if (k == key) {
            list_i64_set(bucket->x, i, value);
            return;
        }
    }
    list_tuple_i64_push_back(bucket, key, value);
}

static int64_t map_i64_get(map_i64* map, int64_t key, int64_t def) {
    int64_t k, v;
    list_tuple_i64* bucket = map_i64_maybe_get_bucket(map, key);
    if (bucket != NULL) {
        for (uint64_t i=0; i<list_tuple_i64_size(bucket); ++i) {
            list_tuple_i64_get(bucket, i, &k, &v);
            if (k == key) {
                return v;
            }
        }
    }
    return def;
}

static int64_t map_i64_contains_key(map_i64* map, int64_t key) {
    int64_t k, v;
    list_tuple_i64* bucket = map_i64_maybe_get_bucket(map, key);
    if (bucket != NULL) {
        for (uint64_t i=0; i<list_tuple_i64_size(bucket); ++i) {
            list_tuple_i64_get(bucket, i, &k, &v);
            if (k == key) {
                return 1;
            }
        }
    }
    return 0;
}

typedef struct map_i64_iterator {
    map_i64* map;
    uint64_t bucket;
    uint64_t idx;
} map_i64_iterator;

static map_i64_iterator* map_i64_iter(map_i64* map) {
    map_i64_iterator* iter = calloc(1, sizeof(map_i64_iterator));
    iter->map = map;
    iter->bucket = 0;
    iter->idx = 0;
    return iter;
}

static void map_i64_iter_free(map_i64_iterator* iter) {
    free(iter);
}

static int64_t map_i64_next(map_i64_iterator* iter, int64_t* key, int64_t* value) {
    uint64_t idx = iter->idx;
    for (uint64_t bucket=iter->bucket; bucket < iter->map->n_buckets; ++bucket) {
        if (iter->map->buckets[bucket] == NULL) {
            continue;
        }
        for (uint64_t i=idx; i<list_tuple_i64_size(iter->map->buckets[bucket]); ++i) {
            iter->bucket = bucket;
            iter->idx = i + 1;
            list_tuple_i64_get(iter->map->buckets[bucket], i, key, value);
            return 1;
        }
        idx = 0;
    }
    *key = 0xBADBADBADBAD;
    *value = 0xBADBADBADBAD;
    return 0;
}
