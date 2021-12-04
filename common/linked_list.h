#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ll_i64_node {
    int64_t data;
    struct ll_i64_node* prev;
    struct ll_i64_node* next;
} ll_i64_node;

typedef struct ll_i64 {
    uint64_t size;
    struct ll_i64_node* start;
    struct ll_i64_node* end;
} ll_i64;

ll_i64* ll_i64_init ();
void ll_i64_free(ll_i64* ll);
void ll_i64_push_back(ll_i64* ll, int64_t item);
void ll_i64_push_front(ll_i64* ll, int64_t item);
ll_i64_node* ll_i64_node_at(ll_i64* ll, uint64_t index);
void ll_i64_remove(ll_i64* ll, uint64_t index);
int64_t ll_i64_peek_back(ll_i64* ll);
int64_t ll_i64_peek_front(ll_i64* ll);
int64_t ll_i64_get(ll_i64* ll, uint64_t index);
int64_t ll_i64_pop_back(ll_i64* ll);
int64_t ll_i64_pop_front(ll_i64* ll);
int64_t ll_i64_contains(ll_i64* ll, int64_t n);
int64_t ll_i64_indexof(ll_i64* ll, int64_t n);
int64_t* ll_i64_as_array(ll_i64* ll, uint64_t* array_size);
ll_i64* ll_i64_merge(ll_i64* ll1, ll_i64* ll2);
int64_t ll_i64_next(ll_i64_node** ll, int64_t* value);
