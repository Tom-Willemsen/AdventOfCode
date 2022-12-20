#include "day20_impl.h"


struct circularlist_node {
    struct circularlist_node* next;
    struct circularlist_node* prev;
    int64_t original_index;
    int64_t value;
};


static int64_t score(uint64_t data_size, struct circularlist_node* first) {
    int64_t result = 0;
    struct circularlist_node* node;
    
    node = first;
    
    while (node->value != 0) {
        node = node->next;
    }
    
    for(uint64_t i=1000; i<=3000; i+=1000) {
        int64_t new_distance = i64modulo_positive(1000, data_size);
            
        for (uint64_t j=0; j<new_distance; ++j) {
            node = node->next;
        }
        printf("result from %ld %ld\n", node->original_index, node->value);
        result += node->value;
    }
    
    return result;
}


static void shuffle(uint64_t data_size, struct circularlist_node* first, uint64_t rounds) {
    struct circularlist_node* node = first;
    struct circularlist_node* moved_node;
    for (uint64_t r=0; r<rounds; ++r) {
        for (uint64_t i=0; i<data_size; ++i) {

            while (node->original_index != i) {
                node = node->next;
            }
            
            int64_t new_distance = i64modulo_positive(node->value, data_size-1);
            printf("new distance: %ld (i: %ld)\n", new_distance, i);
            if (new_distance > 0) {
                moved_node = node;
                
                // Unlink moved node from current neighbours
                moved_node->prev->next = moved_node->next;
                moved_node->next->prev = moved_node->prev;
                
                moved_node->prev = NULL;
                
                for (uint64_t j=0; j<new_distance; ++j) {
                    node = node->next;
                }
                
                moved_node->next = NULL;
                
                node->next->prev = moved_node;
                moved_node->next = node->next;
                node->next = moved_node;
                moved_node->prev = node;
            }
            
            puts("list...");
            for (uint64_t j=0; j<data_size; ++j) {
                printf("List item: original_index %ld value %ld\n", node->original_index, node->value);
                node = node->next;
            }
            puts("< end list >");
        }
    }
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    
    struct circularlist_node* first = NULL;
    struct circularlist_node* prev = NULL;
    struct circularlist_node* node = NULL;
    
    for (uint64_t i=0; i<data_size; ++i) {
        int64_t n = strtol(data[i], NULL, 10);
        
        node = calloc(1, sizeof(struct circularlist_node));
        
        node->original_index = i;
        node->value = n;
        
        
        if (prev != NULL) {
            node->prev = prev;
            prev->next = node;
        } else {
            first = node;
        }
        prev = node;
    }
    
    node->next = first;
    first->prev = node;
    
    shuffle(data_size, first, 1);
    *part1 = score(data_size, first);
    
    node = NULL;
    prev = NULL;
    first = NULL;
    
    for (uint64_t i=0; i<data_size; ++i) {
        int64_t n = strtol(data[i], NULL, 10);
        
        node = calloc(1, sizeof(struct circularlist_node));
        
        node->original_index = i;
        node->value = n * 811589153;
        
        if (prev != NULL) {
            node->prev = prev;
            prev->next = node;
        } else {
            first = node;
        }
        prev = node;
    }
    
    node->next = first;
    first->prev = node;
    
    shuffle(data_size, first, 10);
    *part2 = score(data_size, first);
}
