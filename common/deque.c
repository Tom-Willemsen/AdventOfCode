#include "deque.h"

deque_i64* deque_i64_init () {
    deque_i64* ll = calloc(1, sizeof(deque_i64));
    ll->size = 0;
    ll->start = NULL;
    ll->end = NULL;
    return ll;
}

void deque_i64_free(deque_i64* ll) {
    deque_i64_node* node = ll->start;
    if (ll->size > 0) {
        assert (node->prev == NULL);
        assert (node != NULL);
        while (node->next != NULL) {
            node = node->next;
            free(node->prev);
        }
        assert(node == ll->end);
        free(node);
    }
    free(ll);
}

void deque_i64_push_back(deque_i64* ll, int64_t item) {
    deque_i64_node* node = calloc(1, sizeof(deque_i64_node));
    assert(node != NULL);
    
    node->data = item;
    node->prev = ll->end;
    node->next = NULL;
    
    if (ll->size == 0) {
        assert(ll->start == NULL);
        ll->start = node;
    } else {
        assert(ll->end != NULL);
        ll->end->next = node;
    }
    ll->end = node;
    ll->size++;
}

void deque_i64_push_front(deque_i64* ll, int64_t item) {
    deque_i64_node* node = calloc(1, sizeof(deque_i64_node));
    assert(node != NULL);
    
    node->data = item;
    node->prev = NULL;
    node->next = ll->start;
    
    if (ll->size == 0) {
        assert(ll->end == NULL);
        ll->end = node;
    } else {
        assert(ll->end != NULL);
        ll->start->prev = node;
    }
    ll->start = node;
    ll->size++;
}

void deque_i64_insert_before(deque_i64* ll, deque_i64_node* node, int64_t item) {
    assert(node != NULL);
    if (ll->size == 0 || ll->start == node) {
        deque_i64_push_front(ll, item);
        return;
    }
    deque_i64_node* new_node = calloc(1, sizeof(deque_i64_node));
    new_node->data = item;
    new_node->next = node;
    new_node->prev = node->prev;
    
    assert(node->prev != NULL);
    node->prev->next = new_node;
    node->prev = new_node;
    ll->size++;
}

void deque_i64_insert_after(deque_i64* ll, deque_i64_node* node, int64_t item) {
    assert(node != NULL);
    if (ll->size == 0 || ll->end == node) {
        deque_i64_push_back(ll, item);
        return;
    }
    deque_i64_node* new_node = calloc(1, sizeof(deque_i64_node));
    new_node->data = item;
    new_node->prev = node;
    new_node->next = node->next;
    
    assert(node->next != NULL);
    node->next->prev = new_node;
    node->next = new_node;
    ll->size++;
}

deque_i64_node* deque_i64_node_at(deque_i64* ll, uint64_t index) {
    assert(index >= 0);
    assert(index < ll->size);
    uint64_t i;
    deque_i64_node* node;
    assert(ll->size > 0);
    if (index * 2 > ll->size) {
        // closer to end than beginning
        node = ll->end;
        for (i = ll->size - 1; i>index; --i) {
            node = node->prev;
        } 
    } else {
        node = ll->start;
        for (i = 0; i<index; ++i) {
            node = node->next;
        }
    }
    assert(node != NULL);
    return node;
}

void deque_i64_remove(deque_i64* ll, uint64_t index) {
    assert(ll->size > index);
    
    deque_i64_node* node = deque_i64_node_at(ll, index);
    
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        assert(index == 0);
        ll->start = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        assert(index == ll->size - 1);
        ll->end = node->prev;
    }
    
    ll->size--;
    free(node);
}

int64_t deque_i64_peek_back(deque_i64* ll) {
    assert(ll->size > 0);
    return ll->end->data;
}

int64_t deque_i64_peek_front(deque_i64* ll) {
    assert(ll->size > 0);
    return ll->start->data;
}

int64_t deque_i64_get(deque_i64* ll, uint64_t index) {
    deque_i64_node* node = deque_i64_node_at(ll, index);
    return node->data;
}

int64_t deque_i64_pop_back(deque_i64* ll) {
    int64_t result = deque_i64_peek_back(ll);
    deque_i64_remove(ll, ll->size - 1);
    return result;
}

int64_t deque_i64_pop_front(deque_i64* ll) {
    int64_t result = deque_i64_peek_front(ll);
    deque_i64_remove(ll, 0);
    return result;
}

int64_t deque_i64_contains(deque_i64* ll, int64_t n) {
    deque_i64_node* it = ll->start;
    int64_t value;
    while (deque_i64_next(&it, &value)) {
        if (value == n) {
            return 1;
        }
    }
    return 0;
}

int64_t deque_i64_indexof(deque_i64* ll, int64_t n) {
    int64_t index = 0, value;
    deque_i64_node* it = ll->start;
    while (deque_i64_next(&it, &value)) {
        if (value == n) {
            return index;
        }
        index++;
    }
    return -1;
}

int64_t* deque_i64_as_array(deque_i64* ll, uint64_t* array_size) {
    *array_size = ll->size;
    if (ll->size == 0) {
        return NULL;
    }
    int64_t* arr = calloc(ll->size, sizeof(int64_t));
    assert(arr != NULL);
    
    deque_i64_node* it = ll->start;
    int64_t value, arr_index = 0;
    while (deque_i64_next(&it, &value)) {
        arr[arr_index] =value;
        arr_index++;
    }
    return arr;
}

deque_i64* deque_i64_merge(deque_i64* ll1, deque_i64* ll2) {
    // merge lists in-place, may return either list, other list is freed
    if (ll1->size == 0) {
        free(ll1);
        return ll2;
    }
    if (ll2->size == 0) {
        free(ll2);
        return ll1;
    }
    
    ll1->end->next = ll2->start;
    ll2->start->prev = ll1->end;
    ll1->end = ll2->end;
    ll1->size += ll2->size;
    free(ll2);
    return ll1;
}
