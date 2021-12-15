#pragma once
#include "tuple_list.h"
#include "util.h"

typedef struct map_i64 {
    uint64_t n_buckets;
    list_tuple_i64** buckets;
} map_i64;

static map_i64* map_i64_init(uint64_t n_buckets) {
    map_i64* map = calloc(1, sizeof(map_i64));
    assert(n_buckets > 0);
    map->n_buckets = n_buckets;
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

static inline uint64_t map_i64_hashfunction(uint64_t n_buckets, int64_t key) {
    return i64abs(key) % n_buckets;
}

static inline list_tuple_i64* map_i64_get_or_create_bucket(map_i64* map, int64_t key) {
    uint64_t bucket = map_i64_hashfunction(map->n_buckets, key);
    if (map->buckets[bucket] == NULL) {
        map->buckets[bucket] = list_tuple_i64_init(2);
    }
    return map->buckets[bucket];
}

static inline list_tuple_i64* map_i64_maybe_get_bucket(map_i64* map, int64_t key) {
    uint64_t bucket = map_i64_hashfunction(map->n_buckets, key);
    return map->buckets[bucket];
}

static void map_i64_set(map_i64* map, int64_t key, int64_t value) {
    int64_t k, v;
    list_tuple_i64* bucket = map_i64_get_or_create_bucket(map, key);
    for (uint64_t i=0; i<list_tuple_i64_size(bucket); ++i) {
        list_tuple_i64_get(bucket, i, &k, &v);
        if (k == key) {
            list_i64_set(bucket->y, i, value);
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
