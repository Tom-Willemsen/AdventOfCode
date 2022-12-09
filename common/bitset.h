#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct bitset {
    size_t size;
    uint64_t* data;
} bitset;

static bitset* bitset_init(size_t length) {
    assert(length % 64 == 0);
    bitset* bs = calloc(1, sizeof(bitset));
    bs->size = length;
    bs->data = calloc(bs->size/64, sizeof(uint64_t));
    return bs;
}

static inline void bitset_free(bitset* bs) {
    free(bs->data);
    free(bs);
}

static inline uint8_t bitset_get(bitset* bs, size_t index) {
    assert(index < bs->size);
    return (bs->data[index/64] & (((uint64_t) 1) << (index % 64))) > 0;
}

static inline void bitset_set(bitset* bs, size_t index) {
    assert(index < bs->size);
    bs->data[index/64] |= (((uint64_t) 1) << (index % 64));
}

static inline void bitset_clear(bitset* bs, size_t index) {
    assert(index < bs->size);
    bs->data[index/64] &= (~(((uint64_t) 1) << (index % 64)));
}

static inline void bitset_toggle(bitset* bs, size_t index) {
    assert(index < bs->size);
    bs->data[index/64] ^= (((uint64_t) 1) << (index % 64));
}

static inline uint64_t bitset_popcnt(bitset* bs) {
    uint64_t result = 0;
    for (uint64_t i=0; i<(bs->size / 64); ++i) {
        result += __builtin_popcountll(bs->data[i]);
    }
    return result;
}
