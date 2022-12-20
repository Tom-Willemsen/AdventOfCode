#include "day20_impl.h"


static int64_t score(list_tuple_i64* data) {
    int64_t zero_index = INT64_MIN;
    int64_t result = 0;
    
    for (uint64_t j=0; j<list_tuple_i64_size(data); ++j) {
        int64_t x, y;
        list_tuple_i64_get(data, j, &x, &y);
        if (y == 0) {
            zero_index = j;
            break;
        }
    }
    
    for(uint64_t j=1000; j<=3000; j+=1000) {
        int64_t x, y;
        list_tuple_i64_get(data, (zero_index + j) % list_tuple_i64_size(data), &x, &y);
        result += y;
    }
    return result;
}


static void shuffle(list_tuple_i64* data, uint64_t rounds) {
    for (uint64_t r=0; r<rounds; ++r) {
        for (uint64_t i=0; i<list_tuple_i64_size(data); ++i) {
            int64_t current_index, dist, index, value;
            for (uint64_t j=0; j<list_tuple_i64_size(data); ++j) {
                list_tuple_i64_get(data, j, &current_index, &dist);
                if (current_index == i) {
                    current_index = j;
                    break;
                }
            }
            
            int64_t new_index = i64modulo_positive(current_index + dist, list_tuple_i64_size(data) - 1);
            
            list_tuple_i64_get(data, current_index, &index, &value);
            list_tuple_i64_remove(data, current_index);
            list_tuple_i64_insert(data, new_index, index, value);
        }
    }
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {

    *part1 = 0;
    *part2 = 1;
    
    list_tuple_i64* part1_list = list_tuple_i64_init(data_size);
    list_tuple_i64* part2_list = list_tuple_i64_init(data_size);
    
    for (uint64_t i=0; i<data_size; ++i) {
        int64_t n = strtol(data[i], NULL, 10);
        list_tuple_i64_push_back(part1_list, i, n);
        list_tuple_i64_push_back(part2_list, i, n * 811589153);
    }
    
    shuffle(part1_list, 1);
    shuffle(part2_list, 10);
    
    *part1 = score(part1_list);
    *part2 = score(part2_list);
    
    list_tuple_i64_free(part1_list);
    list_tuple_i64_free(part2_list);
}
