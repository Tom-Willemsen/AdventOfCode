#include "day14_impl.h"

static inline int64_t char_pair_to_id(int64_t p1, int64_t p2) {
    return (p1 << 8) + p2;
}

static list_tuple_i64* parse_rules(char** data, uint64_t data_size) {
    char c1, c2, created;
    list_tuple_i64* ret = list_tuple_i64_init(data_size - 2);
    assert(data_size >= 3);
    for (uint64_t i=2; i<data_size; ++i) {
        sscanf(data[i], "%c%c -> %c", &c1, &c2, &created);
        if (c1 != '\n' && c2 != '\n' && created != '\n') {
            list_tuple_i64_push_back(ret, char_pair_to_id(c1, c2), created);
        }
    }
    return ret;
}

int64_t solve(char* start, list_tuple_i64* rules, int64_t iterations) {
    uint64_t i, j, k;
    int64_t rule_id, added, diff, key, value;
    counter_i64* pair_count = counter_i64_init(20);
    counter_i64* char_count = counter_i64_init(20);
    list_tuple_i64* incs = list_tuple_i64_init(20);
    
    assert(strlen(start) > 3);
    for (i=0; i<strlen(start)-2; ++i) {
        counter_i64_increment(pair_count, char_pair_to_id(start[i], start[i+1]));
    }
    
    for (i=0; i<iterations; ++i) {
        for (j=0; j<counter_i64_size(pair_count); ++j) {
            counter_i64_get_by_index(pair_count, j, &key, &value);
            for (k=0; k<list_tuple_i64_size(rules); ++k) {
                list_tuple_i64_get(rules, k, &rule_id, &added);
                if (rule_id == key) {
                    list_tuple_i64_push_back(incs, rule_id, -value);
                    list_tuple_i64_push_back(incs, char_pair_to_id(rule_id >> 8, added), value);
                    list_tuple_i64_push_back(incs, char_pair_to_id(added, rule_id & 0xff), value);
                    break;
                }
            }
        }
        while (list_tuple_i64_size(incs) > 0) {
            list_tuple_i64_pop_back(incs, &key, &value);
            counter_i64_incrementby(pair_count, key, value);
        }
    }
    
    counter_i64_increment(char_count, start[0]);
    
    for (i=0; i<counter_i64_size(pair_count); ++i) {
        counter_i64_get_by_index(pair_count, i, &key, &value);
        counter_i64_incrementby(char_count, key & 0xff, value);
    }
    
    diff = counter_i64_max(char_count) - counter_i64_min(char_count);
    
    list_tuple_i64_free(incs);
    counter_i64_free(pair_count);
    counter_i64_free(char_count);
    return diff;
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    list_tuple_i64* rules = parse_rules(data, data_size);
    
    *part1 = solve(data[0], rules, 10);
    *part2 = solve(data[0], rules, 40);
    
    list_tuple_i64_free(rules);
}
