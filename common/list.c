#include "list.h"

list_i64* list_i64_init (uint64_t initial_capacity) {
    list_i64* list = calloc(1, sizeof(list_i64));
    list->size = 0;
    assert(initial_capacity > 0);
    list->capacity = initial_capacity;
    list->array = calloc(initial_capacity, sizeof(int64_t));
    return list;
}

void list_i64_free(list_i64* list) {
    free(list->array);
    free(list);
}

static void list_i64_resize(list_i64* list) {
    uint64_t new_capacity = list->capacity * 2;
    list->array = realloc(list->array, new_capacity * sizeof(int64_t));
    assert(list->array != NULL);
    list->capacity = new_capacity;
}

void list_i64_push_back(list_i64* list, int64_t item) {
    if (list->size + 1 > list->capacity) {
        list_i64_resize(list);
    }
    list->array[list->size] = item;
    list->size++;
}

void list_i64_push_front(list_i64* list, int64_t item) {
    if (list->size + 1 > list->capacity) {
        list_i64_resize(list);
    }
    for (uint64_t i=list->size; i>0; --i) {
        list->array[i] = list->array[i-1];
    }
    list->array[0] = item;
    list->size++;
}

void list_i64_remove(list_i64* list, uint64_t index) {
    assert(list->size > 0);
    assert(index < list->size);
    for (uint64_t i=index; i<list->size; ++i) {
        list->array[i] = list->array[i+1];
    }
    list->size--;
}

int64_t list_i64_pop_back(list_i64* list) {
    assert(list->size > 0);
    int64_t result = list->array[list->size - 1];
    list->size--;
    return result;
}

int64_t list_i64_pop_front(list_i64* list) {
    assert(list->size > 0);
    int64_t result = list_i64_peek_front(list);
    list_i64_remove(list, 0);
    return result;
}

int64_t list_i64_contains(list_i64* list, int64_t n) {
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] == n) {
            return 1;
        }
    }
    return 0;
}

int64_t list_i64_indexof(list_i64* list, int64_t n) {
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] == n) {
            return i;
        }
    }
    return -1;
}

int64_t list_i64_min(list_i64* list) {
    int64_t m = INT64_MAX;
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] < m) {
            m = list->array[i];
        }
    }
    return m;
}

int64_t list_i64_max(list_i64* list) {
    int64_t m = INT64_MIN;
    for (uint64_t i=0; i<list->size; ++i) {
        if (list->array[i] > m) {
            m = list->array[i];
        }
    }
    return m;
}

int64_t* list_i64_as_array(list_i64* list, uint64_t* array_size) {
    assert(list->size > 0);
    int64_t* result = calloc(list->size, sizeof(int64_t));
    for (uint64_t i=0; i<list->size; ++i) {
        result[i] = list->array[i];
    }
    *array_size = list->size;
    return result;
}

list_i64* list_i64_merge(list_i64* list1, list_i64* list2) {
    if (list1->size > list2->size) {
        for (uint64_t i=0; i<list2->size; ++i) {
            list_i64_push_back(list1, list2->array[i]);
        }
        list_i64_free(list2);
        return list1;
    } else {
        for (uint64_t i=0; i<list1->size; ++i) {
            list_i64_push_back(list2, list1->array[i]);
        }
        list_i64_free(list1);
        return list2;
    }
}
