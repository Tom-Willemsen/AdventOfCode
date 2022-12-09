#pragma once
#include "list.h"

typedef struct list_tuple_i64 {
    list_i64* x;
    list_i64* y;
} list_tuple_i64;

static list_tuple_i64* list_tuple_i64_init(uint64_t initial_capacity) {
    list_tuple_i64* list = calloc(1, sizeof(list_tuple_i64));
    list->x = list_i64_init(initial_capacity);
    list->y = list_i64_init(initial_capacity);
    return list;
}

static void list_tuple_i64_free(list_tuple_i64* list) {
    assert(list->x->size == list->y->size);
    list_i64_free(list->x);
    list_i64_free(list->y);
    free(list);
}

static inline uint64_t list_tuple_i64_size(list_tuple_i64* list) {
    assert(list->x->size == list->y->size);
    return list->x->size;
}

static inline void list_tuple_i64_clear(list_tuple_i64* list) {
    assert(list->x->size == list->y->size);
    list_i64_clear(list->y);
    list_i64_clear(list->x);
}

static inline void list_tuple_i64_push_back(list_tuple_i64* list, int64_t y, int64_t x) {
    assert(list->x->size == list->y->size);
    list_i64_push_back(list->y, y);
    list_i64_push_back(list->x, x);
}

static inline void list_tuple_i64_pop_back(list_tuple_i64* list, int64_t* y, int64_t* x) {
    assert(list->x->size == list->y->size);
    *y = list_i64_pop_back(list->y);
    *x = list_i64_pop_back(list->x);
}

static inline void list_tuple_i64_get(list_tuple_i64* list, uint64_t index, int64_t* y, int64_t* x) {
    assert(list->x->size == list->y->size);
    *y = list_i64_get(list->y, index);
    *x = list_i64_get(list->x, index);
}

static inline void list_tuple_i64_set(list_tuple_i64* list, uint64_t index, int64_t y, int64_t x) {
    assert(list->x->size == list->y->size);
    list_i64_set(list->y, index, y);
    list_i64_set(list->x, index, x);
}

static inline void list_tuple_i64_remove(list_tuple_i64* list, uint64_t index) {
    assert(list->x->size == list->y->size);
    list_i64_remove(list->x, index);
    list_i64_remove(list->y, index);
}

static int64_t list_tuple_i64_last_indexof(list_tuple_i64* list, int64_t y, int64_t x) {
    for (int64_t i=list_tuple_i64_size(list) - 1; i>=0; --i) {
        if (list_i64_get(list->y, i) == x && list_i64_get(list->x, i) == y) {
            return i;
        }
    }
    return -1;
} 

static int64_t list_tuple_i64_contains(list_tuple_i64* list, int64_t y, int64_t x) {
    for (int64_t i=list_tuple_i64_size(list) - 1; i>=0; --i) {
        if (list_i64_get(list->x, i) == x && list_i64_get(list->y, i) == y) {
            return 1;
        }
    }
    return 0;
} 
