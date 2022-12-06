#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_i64 {
    uint64_t size;
    uint64_t capacity;
    int64_t* array;
} list_i64;

static list_i64* list_i64_init (uint64_t initial_capacity) {
    list_i64* list = calloc(1, sizeof(list_i64));
    list->size = 0;
    assert(initial_capacity > 0);
    list->capacity = initial_capacity;
    list->array = calloc(initial_capacity, sizeof(int64_t));
    return list;
}

static void list_i64_free(list_i64* list) {
    free(list->array);
    free(list);
}

static inline uint64_t list_i64_size(list_i64* list) {
    return list->size;
}

static void list_i64_resize(list_i64* list) {
    uint64_t new_capacity = list->capacity * 2;
    list->array = realloc(list->array, new_capacity * sizeof(int64_t));
    assert(list->array != NULL);
    list->capacity = new_capacity;
}

static void list_i64_push_back(list_i64* list, int64_t item) {
    if (list->size + 1 > list->capacity) {
        list_i64_resize(list);
    }
    list->array[list->size] = item;
    list->size++;
}

static void list_i64_push_front(list_i64* list, int64_t item) {
    if (list->size + 1 > list->capacity) {
        list_i64_resize(list);
    }
    for (uint64_t i=list->size; i>0; --i) {
        list->array[i] = list->array[i-1];
    }
    list->array[0] = item;
    list->size++;
}

static void list_i64_remove(list_i64* list, uint64_t index) {
    assert(list->size > 0);
    assert(index < list->size);
    for (uint64_t i=index; i<list->size-1; ++i) {
        list->array[i] = list->array[i+1];
    }
    list->size--;
}

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

static inline void list_i64_set(list_i64* list, uint64_t index, int64_t value) {
    assert(list->size > index);
    list->array[index] = value;
}

static int64_t list_i64_pop_back(list_i64* list) {
    assert(list->size > 0);
    int64_t result = list->array[list->size - 1];
    list->size--;
    return result;
}

static int64_t list_i64_pop_front(list_i64* list) {
    assert(list->size > 0);
    int64_t result = list_i64_peek_front(list);
    list_i64_remove(list, 0);
    return result;
}

static int64_t list_i64_contains(list_i64* list, int64_t n) {
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] == n) {
            return 1;
        }
    }
    return 0;
}

static int64_t list_i64_count(list_i64* list, int64_t n) {
    int64_t count = 0;
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] == n) {
            count++;
        }
    }
    return count;
}

static int64_t list_i64_indexof(list_i64* list, int64_t n) {
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] == n) {
            return i;
        }
    }
    return -1;
}

static int64_t list_i64_min(list_i64* list) {
    int64_t m = INT64_MAX;
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] < m) {
            m = list->array[i];
        }
    }
    return m;
}

static int64_t list_i64_max(list_i64* list) {
    int64_t m = INT64_MIN;
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] > m) {
            m = list->array[i];
        }
    }
    return m;
}

static int64_t* list_i64_as_array(list_i64* list, uint64_t* array_size) {
    assert(list->size > 0);
    int64_t* result = calloc(list->size, sizeof(int64_t));
    for (uint64_t i=0; i<list->size; ++i) {
        result[i] = list->array[i];
    }
    *array_size = list->size;
    return result;
}

static list_i64* list_i64_merge(list_i64* list1, list_i64* list2) {
    uint64_t needed_capacity = list1->size + list2->size;
    if (list1->capacity < needed_capacity) {
        list1->array = realloc(list1->array, needed_capacity * sizeof(int64_t));
        list1->capacity = needed_capacity;
    }
    
    memcpy(list1->array + list1->size, list2->array, list2->size * sizeof(int64_t));
    list1->size += list2->size;
    
    list_i64_free(list2);
    return list1;
}

static inline int compare_elements(const void * a, const void * b) {
    if (*(const int64_t*)a > *(const int64_t*)b) {
        return 1;
    } else if (*(const int64_t*)a < *(const int64_t*)b) {
        return -1;
    } else {
        return 0;
    }
}

static void list_i64_sort_inplace(list_i64* list) {
    qsort(list->array, list->size, sizeof(int64_t), compare_elements);
}
