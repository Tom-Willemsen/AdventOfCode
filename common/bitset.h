#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

_Static_assert(sizeof(uint64_t) == sizeof(unsigned long long));

typedef struct bitset {
    size_t size;
    uint64_t* data;
} bitset;

[[nodiscard]] static inline size_t bitset_alloc_size(size_t size) {
    return (size + 63) / 64;
}

[[nodiscard]] static bitset* bitset_init(size_t length) {
    assert(length > 0);
    bitset* bs = calloc(1, sizeof(bitset));
    bs->size = length;
    bs->data = calloc(bitset_alloc_size(bs->size), sizeof(uint64_t));
    return bs;
}

static inline void bitset_free(bitset* bs) {
    free(bs->data);
    free(bs);
}

[[nodiscard]] static inline uint8_t bitset_get(bitset* bs, size_t index) {
    assert(index < bs->size);
    return (bs->data[index/64] & (1ULL << (index % 64))) > 0;
}

static inline void bitset_set(bitset* bs, size_t index) {
    assert(index < bs->size);
    bs->data[index/64] |= (1ULL << (index % 64));
}

static inline void bitset_clear(bitset* bs, size_t index) {
    assert(index < bs->size);
    bs->data[index/64] &= (~(1ULL << (index % 64)));
}

static inline void bitset_toggle(bitset* bs, size_t index) {
    assert(index < bs->size);
    bs->data[index/64] ^= (1ULL << (index % 64));
}

[[nodiscard]] static uint64_t bitset_equals(bitset* bs1, bitset* bs2) {
    if (bs1->size != bs2->size) {
        return 0;
    }
    for (uint64_t i=0; i<bitset_alloc_size(bs1->size); ++i) {
        if (bs1->data[i] != bs2->data[i]) {
            return 0;
        }
    }
    return 1;
}

[[nodiscard]] static inline uint64_t bitset_popcnt(bitset* bs) {
    uint64_t result = 0;
    for (uint64_t i=0; i<bitset_alloc_size(bs->size); ++i) {
        result += __builtin_popcountll(bs->data[i]);
    }
    return result;
}
