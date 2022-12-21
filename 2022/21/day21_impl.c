#include "day21_impl.h"


static const char* ROOT = "root";
static const char* HUMN = "humn";


static inline void fill_q(deque_i64* q, map_i64* constants, list_tuple3_i64* operations) {
    for (uint64_t j=0; j<list_tuple3_i64_size(operations); ++j) {
        int64_t left, op, right;
        list_tuple3_i64_get(operations, j, &left, &op, &right);
        if (op == '+' || op == '-' || op == '*' || op == '/') {
            if (!map_i64_contains_key(constants, j) && map_i64_contains_key(constants, left) && map_i64_contains_key(constants, right)) {
                deque_i64_push_back(q, j);
            }
        }
    }
}


static void fold_constants(map_i64* constants, list_tuple3_i64* operations) {
    deque_i64* q = deque_i64_init();
    
    fill_q(q, constants, operations);
    
    while (q->size > 0) {
        while (q->size > 0) {
            int64_t i = deque_i64_pop_front(q);
            
            int64_t left, op, right;
            list_tuple3_i64_get(operations, i, &left, &op, &right);
            
            if (map_i64_contains_key(constants, i) || op == '?') {
                continue;
            }
            
            assert(map_i64_contains_key(constants, left));
            assert(map_i64_contains_key(constants, right));
            
            int64_t n = 0;
            int64_t left_val = map_i64_get(constants, left, INT64_MIN);
            int64_t right_val = map_i64_get(constants, right, INT64_MIN);
            
            if (op == '-') {
                n = left_val - right_val;
                map_i64_set(constants, i, n);
            } else if (op == '+') {
                n = left_val + right_val;
                map_i64_set(constants, i, n);
            } else if (op == '/') {
                n = left_val / right_val;
                map_i64_set(constants, i, n);
            } else if (op == '*') {
                n = left_val * right_val;
                map_i64_set(constants, i, n);
            }
        }
        
        fill_q(q, constants, operations);
    }
    
    deque_i64_free(q);
}


static int64_t calc_p2(map_i64* constants, list_tuple3_i64* operations, int64_t key, int64_t target) {
    int64_t left, op, right;
    
    list_tuple3_i64_get(operations, key, &left, &op, &right);
    
    if (op == '?') {
        return target;
    }
    
    int64_t left_const = map_i64_get(constants, left, INT64_MIN);
    int64_t right_const = map_i64_get(constants, right, INT64_MIN);
    
    if (left_const != INT64_MIN) {
        if (op == '+') {
            return calc_p2(constants, operations, right, target - left_const);
        } else if (op == '-') {
            return calc_p2(constants, operations, right, left_const - target);
        } else if (op == '*') {
            return calc_p2(constants, operations, right, target / left_const);
        } else if (op == '=') {
            return calc_p2(constants, operations, right, left_const);
        } else {
            assert(0);
        }
    } else if (right_const != INT64_MIN) {
        if (op == '+') {
            return calc_p2(constants, operations, left, target - right_const);
        } else if (op == '-') {
            return calc_p2(constants, operations, left, right_const + target);
        } else if (op == '*') {
            return calc_p2(constants, operations, left, target / right_const);
        } else if (op == '/') {
            return calc_p2(constants, operations, left, target * right_const);
        } else if (op == '=') {
            return calc_p2(constants, operations, left, right_const);
        } else {
            assert(0);
        }
    }
    assert(0);
    return -1;
}


static inline int64_t monkey_name_to_id(uint64_t num_monkeys, char** data, const char* const name) {
    for (uint64_t i=0; i<num_monkeys; ++i) {
        
        // Note: significantly faster than strncmp(data[i], name, 4)
        if (data[i][0] == name[0] && 
            data[i][1] == name[1] && 
            data[i][2] == name[2] && 
            data[i][3] == name[3]
        ) {
            return i;
        }
    }
    assert(0);
    return 0;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t root_id = monkey_name_to_id(data_size, data, ROOT);
    int64_t humn_id = monkey_name_to_id(data_size, data, HUMN);
    
    map_i64* part1_constants = map_i64_init(data_size);
    map_i64* part2_constants = map_i64_init(data_size);
    list_tuple3_i64* part1_operations = list_tuple3_i64_init(data_size);
    list_tuple3_i64* part2_operations = list_tuple3_i64_init(data_size);

    for (uint64_t i=0; i<data_size; ++i) {
        assert(strlen(data[i]) >= 7);
        
        if (data[i][6] >= 'a' && data[i][6] <= 'z') {
            char name[4];
            char left[4];
            char right[4];
            char op;
            sscanf(data[i], "%4c: %4c %c %4c", name, left, &op, right);
            
            int64_t left_id = monkey_name_to_id(data_size, data, left);
            int64_t right_id = monkey_name_to_id(data_size, data, right);
            
            if (i == root_id) {
                list_tuple3_i64_push_back(part2_operations, left_id, '=', right_id);
            } else {
                list_tuple3_i64_push_back(part2_operations, left_id, op, right_id);
            }
            
            list_tuple3_i64_push_back(part1_operations, left_id, op, right_id);
        } else {
            int64_t constant;
            char name[4];
            sscanf(data[i], "%4c: %ld", name, &constant);
            
            map_i64_set(part1_constants, i, constant);
            
            if (i == humn_id) {
                list_tuple3_i64_push_back(part2_operations, constant, '?', 0);
            } else {
                map_i64_set(part2_constants, i, constant);
                list_tuple3_i64_push_back(part2_operations, constant, '#', 0);
            }
            
            list_tuple3_i64_push_back(part1_operations, constant, '#', 0);
        }
    }

    fold_constants(part1_constants, part1_operations);
    fold_constants(part2_constants, part2_operations);
    
    *part1 = map_i64_get(part1_constants, root_id, INT64_MIN);
    *part2 = calc_p2(part2_constants, part2_operations, root_id, 1);
    
    map_i64_free(part1_constants);
    map_i64_free(part2_constants);
    
    list_tuple3_i64_free(part1_operations);
    list_tuple3_i64_free(part2_operations);
}
