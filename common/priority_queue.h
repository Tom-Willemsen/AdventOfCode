#pragma once 
#include "deque.h"

typedef struct priorityQ_i64 {
    deque_i64* priorities;
    deque_i64* values;
} priorityQ_i64;

static priorityQ_i64* priorityQ_i64_init() {
    priorityQ_i64* q = calloc(1, sizeof(priorityQ_i64));
    q->priorities = deque_i64_init();
    q->values = deque_i64_init();
    return q;
}

static void priorityQ_i64_free(priorityQ_i64* q) {
    deque_i64_free(q->priorities);
    deque_i64_free(q->values);
    free(q);
}

static inline uint64_t priorityQ_i64_size(priorityQ_i64* q) {
    assert(q->priorities->size == q->values->size);
    return q->values->size;
}

static void priorityQ_i64_push_fbias(priorityQ_i64* q, int64_t p, int64_t v) {
    // push with performance bias to inserting near front of queue
    int64_t priority, value;
    deque_i64_node* priority_n = q->priorities->start;
    deque_i64_node* value_n = q->values->start;
    assert(q->priorities != NULL);
    assert(q->values != NULL);
    assert(q->values->size == q->priorities->size);
    
    do {
        if (priority_n == NULL || value_n == NULL) {
            deque_i64_push_back(q->priorities, p);
            deque_i64_push_back(q->values, v);
            return;
        } else if (priority_n->data >= p) {
            deque_i64_insert_before(q->priorities, priority_n, p);
            deque_i64_insert_before(q->values, value_n, v);
            return;
        }
    } while(deque_i64_next(&priority_n, &priority) && deque_i64_next(&value_n, &value));
}

static void priorityQ_i64_push_bbias(priorityQ_i64* q, int64_t p, int64_t v) {
    // push with performance bias to inserting near back of queue
    int64_t priority, value;
    deque_i64_node* priority_n = q->priorities->end;
    deque_i64_node* value_n = q->values->end;
    assert(q->priorities != NULL);
    assert(q->values != NULL);
    assert(q->values->size == q->priorities->size);
    
    do {
        if (priority_n == NULL || value_n == NULL) {
            deque_i64_push_front(q->priorities, p);
            deque_i64_push_front(q->values, v);
            return;
        } else if (priority_n->data <= p) {
            deque_i64_insert_after(q->priorities, priority_n, p);
            deque_i64_insert_after(q->values, value_n, v);
            return;
        }
    } while(deque_i64_prev(&priority_n, &priority) && deque_i64_prev(&value_n, &value));
}

static int64_t priorityQ_i64_pop(priorityQ_i64* q) {
    deque_i64_pop_front(q->priorities);
    return deque_i64_pop_front(q->values);
}
