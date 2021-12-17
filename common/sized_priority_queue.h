#pragma once 
#include "list.h"


// This struct holds an array of lists
// Each list corresponds to a single (consecutive) priority value
// and the list holds all task values which are at that priority.
// Advantage over priority_queue is that it's more efficient in terms
// of CPU as it does not do linked list O(n) lookups.
// Disadvantage is it can use quite a bit more memory, particularly if
// priorities are sparse.
typedef struct sized_priorityQ_i64 {
    int64_t min_priority;
    int64_t max_priority;
    int64_t min_populated_priority;
    int64_t max_populated_priority;
    uint64_t size;
    list_i64** tasks;
} sized_priorityQ_i64;

static sized_priorityQ_i64* sized_priorityQ_i64_init(int64_t min_priority, int64_t max_priority) {
    sized_priorityQ_i64* q = calloc(1, sizeof(sized_priorityQ_i64));
    
    assert(max_priority > min_priority);
    
    q->tasks = calloc(max_priority - min_priority + 1, sizeof(list_i64*));
    
    for (int64_t i=0; i<=(max_priority-min_priority); ++i) {
        q->tasks[i] = list_i64_init(1);
    }

    q->size = 0;
    q->min_priority = min_priority;
    q->max_priority = max_priority;
    q->min_populated_priority = min_priority;
    q->max_populated_priority = max_priority;
    return q;
}

static void sized_priorityQ_i64_free(sized_priorityQ_i64* q) {
    for (int64_t i=0; i<=(q->max_priority-q->min_priority); ++i) {
        list_i64_free(q->tasks[i]);
    }
    free(q->tasks);
    free(q);
}

static inline uint64_t sized_priorityQ_i64_size(sized_priorityQ_i64* q) {
    return q->size;
}

static void sized_priorityQ_i64_push(sized_priorityQ_i64* q, int64_t p, int64_t v) {
    assert(p >= q->min_priority);
    assert(p <= q->max_priority);
    q->min_populated_priority = min(q->min_populated_priority, p);
    q->max_populated_priority = max(q->max_populated_priority, p);
    list_i64_push_back(q->tasks[q->min_priority + p], v);
    q->size++;
}

static int64_t sized_priorityQ_i64_pop(sized_priorityQ_i64* q) {
    int64_t result_priority, result_value;
    
    assert(sized_priorityQ_i64_size(q) > 0);
    result_priority = q->min_populated_priority;
    
    assert(list_i64_size(q->tasks[q->min_priority + result_priority]) > 0);
    result_value = list_i64_pop_back(q->tasks[q->min_priority + result_priority]);
    
    q->size--;
    
    if (list_i64_size(q->tasks[q->min_priority + result_priority]) == 0) {
        for (int64_t i=result_priority; i<=q->max_populated_priority; ++i) {
            if (list_i64_size(q->tasks[q->min_priority + i]) > 0) {
                q->min_populated_priority = i;
                return result_value;
            }
        }
        q->min_populated_priority = q->max_priority;
        q->max_populated_priority = q->min_priority;
    }

    return result_value;
}
