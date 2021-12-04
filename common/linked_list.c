#include "linked_list.h"

ll_i64* ll_i64_init () {
    ll_i64* ll = calloc(1, sizeof(ll_i64));
    ll->size = 0;
    ll->start = NULL;
    ll->end = NULL;
    return ll;
}

void ll_i64_free(ll_i64* ll) {
    ll_i64_node* node = ll->start;
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

void ll_i64_push_back(ll_i64* ll, int64_t item) {
    ll_i64_node* node = calloc(1, sizeof(ll_i64_node));
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

void ll_i64_push_front(ll_i64* ll, int64_t item) {
    ll_i64_node* node = calloc(1, sizeof(ll_i64_node));
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

ll_i64_node* ll_i64_node_at(ll_i64* ll, uint64_t index) {
    assert(index >= 0);
    assert(index < ll->size);
    uint64_t i;
    ll_i64_node* node;
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

void ll_i64_remove(ll_i64* ll, uint64_t index) {
    assert(ll->size > 0);
    assert(ll->size > index);
    
    ll_i64_node* node = ll_i64_node_at(ll, index);
    
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

int64_t ll_i64_peek_back(ll_i64* ll) {
    assert(ll->size > 0);
    return ll->end->data;
}

int64_t ll_i64_peek_front(ll_i64* ll) {
    assert(ll->size > 0);
    return ll->start->data;
}

int64_t ll_i64_get(ll_i64* ll, uint64_t index) {
    ll_i64_node* node = ll_i64_node_at(ll, index);
    return node->data;
}

int64_t ll_i64_pop_back(ll_i64* ll) {
    int64_t result = ll_i64_peek_back(ll);
    ll_i64_remove(ll, ll->size - 1);
    return result;
}

int64_t ll_i64_pop_front(ll_i64* ll) {
    int64_t result = ll_i64_peek_front(ll);
    ll_i64_remove(ll, 0);
    return result;
}

int64_t ll_i64_contains(ll_i64* ll, int64_t n) {
    int64_t index = 0;
    ll_i64_node* node = ll->start;
    if (ll->size > 0) {
        if (node->data == n) return 1;
        while ((node = node->next) != NULL) {
            index++;
            assert(index < ll->size);
            if (node->data == n) {
                return 1;
            }
        };
    }
    return 0;
}

int64_t ll_i64_indexof(ll_i64* ll, int64_t n) {
    int64_t index = 0;
    ll_i64_node* node = ll->start;
    if (ll->size > 0) {
        if (node->data == n) return 0;
        while ((node = node->next) != NULL) {
            index++;
            assert(index < ll->size);
            if (node->data == n) {
                return index;
            }
        }
    }
    return -1;
}

int64_t* ll_i64_as_array(ll_i64* ll, uint64_t* array_size) {
    *array_size = ll->size;
    if (ll->size == 0) {
        return NULL;
    }
    int64_t* arr = calloc(ll->size, sizeof(int64_t));
    assert(arr != NULL);
    ll_i64_node* node = ll->start;
    
    arr[0] = node->data;
    uint64_t arr_index = 0;
    while (node->next != NULL) {
        arr_index++;
        node = node->next;
        assert(arr_index < ll->size);
        arr[arr_index] = node->data;
    }
    assert(node->next == NULL);
    return arr;
}

ll_i64* ll_i64_merge(ll_i64* ll1, ll_i64* ll2) {
    // merge lists in-place
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

ll_i64_node* ll_i64_it(ll_i64* ll) {
    return ll->start;
}

int64_t ll_i64_next(ll_i64_node** node, int64_t* value) {
    if (*node == NULL) {
        return 0;
    }
    *value = (*node)->data;
    *node = (*node)->next;
    return 1;
}
