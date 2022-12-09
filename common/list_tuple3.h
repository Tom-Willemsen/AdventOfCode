#pragma once
#include "list.h"

typedef struct list_tuple3_i64 {
    list_i64* x;
    list_i64* y;
    list_i64* z;
} list_tuple3_i64;

static list_tuple3_i64* list_tuple3_i64_init(uint64_t initial_capacity) {
    list_tuple3_i64* list = calloc(1, sizeof(list_tuple3_i64));
    list->x = list_i64_init(initial_capacity);
    list->y = list_i64_init(initial_capacity);
    list->z = list_i64_init(initial_capacity);
    return list;
}

static void list_tuple3_i64_free(list_tuple3_i64* list) {
    assert(list->x->size == list->y->size);
    list_i64_free(list->x);
    list_i64_free(list->y);
    list_i64_free(list->z);
    free(list);
}

static inline uint64_t list_tuple3_i64_size(list_tuple3_i64* list) {
    assert(list->x->size == list->y->size);
    assert(list->y->size == list->z->size);
    return list->x->size;
}

static inline void list_tuple3_i64_clear(list_tuple3_i64* list) {
    assert(list->x->size == list->y->size);
    assert(list->y->size == list->z->size);
    list_i64_clear(list->x);
    list_i64_clear(list->y);
    list_i64_clear(list->z);
}

static inline void list_tuple3_i64_push_back(list_tuple3_i64* list, int64_t x, int64_t y, int64_t z) {
    assert(list->x->size == list->y->size);
    assert(list->y->size == list->z->size);
    list_i64_push_back(list->x, x);
    list_i64_push_back(list->y, y);
    list_i64_push_back(list->z, z);
}

static inline void list_tuple3_i64_pop_back(list_tuple3_i64* list, int64_t* x, int64_t* y, int64_t* z) {
    assert(list->x->size == list->y->size);
    assert(list->y->size == list->z->size);
    *x = list_i64_pop_back(list->x);
    *y = list_i64_pop_back(list->y);
    *z = list_i64_pop_back(list->z);
}

static inline void list_tuple3_i64_get(list_tuple3_i64* list, uint64_t index, int64_t* x, int64_t* y, int64_t* z) {
    assert(list->x->size == list->y->size);
    assert(list->y->size == list->z->size);
    *x = list_i64_get(list->x, index);
    *y = list_i64_get(list->y, index);
    *z = list_i64_get(list->z, index);
}

static inline void list_tuple3_i64_set(list_tuple3_i64* list, uint64_t index, int64_t x, int64_t y, int64_t z) {
    assert(list->x->size == list->y->size);
    assert(list->y->size == list->z->size);
    list_i64_set(list->x, index, x);
    list_i64_set(list->y, index, y);
    list_i64_set(list->z, index, z);
}

static inline void list_tuple3_i64_remove(list_tuple3_i64* list, uint64_t index) {
    assert(list->x->size == list->y->size);
    assert(list->y->size == list->z->size);
    list_i64_remove(list->x, index);
    list_i64_remove(list->y, index);
    list_i64_remove(list->z, index);
}

static int64_t list_tuple3_i64_indexof(list_tuple3_i64* list, int64_t x, int64_t y, int64_t z) {
    for (int64_t i=list_tuple3_i64_size(list) - 1; i>=0; --i) {
        if (list_i64_get(list->x, i) == x && list_i64_get(list->y, i) == y && list_i64_get(list->z, i) == z) {
            return i;
        }
    }
    return -1;
} 

static int64_t list_tuple3_i64_contains(list_tuple3_i64* list, int64_t x, int64_t y, int64_t z) {
    return list_tuple3_i64_indexof(list, x, y, z) != -1;
}
