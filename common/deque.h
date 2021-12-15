#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct deque_i64_node {
    int64_t data;
    struct deque_i64_node* prev;
    struct deque_i64_node* next;
} deque_i64_node;

typedef struct deque_i64 {
    uint64_t size;
    struct deque_i64_node* start;
    struct deque_i64_node* end;
} deque_i64;

deque_i64* deque_i64_init ();
void deque_i64_free(deque_i64* ll);
void deque_i64_push_back(deque_i64* ll, int64_t item);
void deque_i64_push_front(deque_i64* ll, int64_t item);
void deque_i64_insert_before(deque_i64* ll, deque_i64_node* node, int64_t item);
void deque_i64_insert_after(deque_i64* ll, deque_i64_node* node, int64_t item);
deque_i64_node* deque_i64_node_at(deque_i64* ll, uint64_t index);
void deque_i64_remove(deque_i64* ll, uint64_t index);
int64_t deque_i64_peek_back(deque_i64* ll);
int64_t deque_i64_peek_front(deque_i64* ll);
int64_t deque_i64_get(deque_i64* ll, uint64_t index);
int64_t deque_i64_pop_back(deque_i64* ll);
int64_t deque_i64_pop_front(deque_i64* ll);
int64_t deque_i64_contains(deque_i64* ll, int64_t n);
int64_t deque_i64_indexof(deque_i64* ll, int64_t n);
int64_t* deque_i64_as_array(deque_i64* ll, uint64_t* array_size);
deque_i64* deque_i64_merge(deque_i64* ll1, deque_i64* ll2);

static inline int64_t deque_i64_next(deque_i64_node** node, int64_t* value) {
    if (*node == NULL) {
        return 0;
    }
    *value = (*node)->data;
    *node = (*node)->next;
    return 1;
}

static inline int64_t deque_i64_prev(deque_i64_node** node, int64_t* value) {
    if (*node == NULL) {
        return 0;
    }
    *value = (*node)->data;
    *node = (*node)->prev;
    return 1;
}
