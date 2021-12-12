#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_i64 {
    uint64_t size;
    uint64_t capacity;
    int64_t* array;
} list_i64;

list_i64* list_i64_init (size_t initilist_capacity);
void list_i64_free(list_i64* list);

static inline int64_t list_i64_size(list_i64* list) {
    return list->size;
}

void list_i64_push_back(list_i64* list, int64_t item);
void list_i64_push_front(list_i64* list, int64_t item);
void list_i64_remove(list_i64* list, uint64_t index);

static inline void list_i64_clear(list_i64* list) {
    list->size = 0;
}

static inline int64_t list_i64_peek_back(list_i64* list) {
    assert(list->size > 0);
    return list->array[list->size - 1];    
}

static inline int64_t list_i64_peek_front(list_i64* list) {
    assert(list->size > 0);
    return list->array[0];
}

static inline int64_t list_i64_get(list_i64* list, uint64_t index) {
    assert(list->size > index);
    return list->array[index];
}

int64_t list_i64_pop_back(list_i64* list);
int64_t list_i64_pop_front(list_i64* list);
int64_t list_i64_contains(list_i64* list, int64_t n);
int64_t list_i64_count(list_i64* list, int64_t n);
int64_t list_i64_indexof(list_i64* list, int64_t n);
int64_t list_i64_min(list_i64* list);
int64_t list_i64_max(list_i64* list);
int64_t* list_i64_as_array(list_i64* list, uint64_t* array_size);
list_i64* list_i64_merge(list_i64* list1, list_i64* list2);
void list_i64_sort_inplace(list_i64* list);
