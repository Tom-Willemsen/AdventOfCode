#include "day07_impl.h"

int64_t map_key(list_i64* list, uint64_t* used_keys, list_i64** map_keys) {
    for (uint64_t i=0; i<*used_keys; ++i) {
        if (list_i64_equals(list, map_keys[i])) {
            return i;
        }
    }
    
    map_keys[*used_keys] = list_i64_copy(list);
    (*used_keys)++;
    return (*used_keys) - 1;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t size, key, value;
    counter_i64* counter = counter_i64_init(10);
    
    uint64_t used_keys = 0;
    list_i64** map_keys = calloc(data_size, sizeof(list_i64*));
    
    list_i64* path = list_i64_init(50);
    list_i64_push_back(path, '/');
    
    int64_t root_map_key = map_key(path, &used_keys, map_keys);
    
    for (uint64_t i = 0; i < data_size; ++i) {
        
        if (strlen(data[i]) > 0) {
            if (strncmp(data[i], "$ cd ..", 7) == 0) {
                for (int64_t i=list_i64_size(path)-2; i>=0; --i) {
                    if (list_i64_get(path, i) == '/') {
                        list_i64_inplace_slice(path, 0, i+1);
                        break;
                    }
                }
            } else if (strncmp(data[i], "$ cd /", 6) == 0) {
                list_i64_clear(path);
                list_i64_push_back(path, '/');
            } else if (strncmp(data[i], "$ ls", 4) == 0) {
                // ignore
            } else if (strncmp(data[i], "$ cd ", 5) == 0) {
                for (uint64_t j=5; j<strlen(data[i])-1; ++j) {
                    list_i64_push_back(path, data[i][j]);
                }
                list_i64_push_back(path, '/');
            } else if (strncmp(data[i], "dir ", 4) == 0) {
                // ignore
            } else {
                sscanf(data[i], "%"SCNd64" %*s", &size);
                
                for (int64_t i=0; i<list_i64_size(path); ++i) {
                    if (list_i64_get(path, i) == '/') {
                        list_i64* temp = list_i64_copy_slice(path, 0, i+1);
                        counter_i64_incrementby(counter, map_key(temp, &used_keys, map_keys), size);
                        list_i64_free(temp);
                    }
                }
            }
        }
    }
    
    list_i64_free(path);
    
    counter_i64_iterator* iter = counter_i64_iter(counter);
    *part2 = INT64_MAX;
    while (counter_i64_next(iter, &key, &value)) {
        if (value < 100000) {
            (*part1) += value;
        }
        if (value > counter_i64_get(counter, root_map_key) - 40000000) {
            (*part2) = min(*part2, value);
        }
    }
    counter_i64_iter_free(iter);
    counter_i64_free(counter);
    
    for (uint64_t i=0; i<used_keys; ++i) {
        list_i64_free(map_keys[i]);
    }
    free(map_keys);
}
