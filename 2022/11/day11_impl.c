#include "day11_impl.h"

static const int64_t OLD_ITEM = INT64_MIN;

typedef struct monkey {
    list_i64* items;
    int64_t number;
    int64_t op;
    int64_t test;
    double test_inverse;
    int64_t to_true;
    int64_t to_false;
} monkey;

static int64_t simulate(uint64_t n_monkeys, monkey* monkeys, uint8_t part) 
{
    int64_t p2_divisor = 1;
    int64_t* inspected = calloc(n_monkeys, sizeof(int64_t));
    int64_t res[4];
    int64_t cond[4];
    
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        p2_divisor *= monkeys[m].test;
    }
    
    int64_t rounds = (part == 2) ? 10000 : 20;
    
    __m256i simd_p2_divisor = _mm256_set1_epi64x(p2_divisor);
    __m256d simd_p2_divisor_inverse = _mm256_set1_pd(((double) 1.0) / ((double) p2_divisor));
    
    // __m256i simd_p1_divisor = _mm256_set1_epi64x(3);
    __m256d simd_p1_divisor_inverse = _mm256_set1_pd(((double) 1.0) / ((double) 3.0));
    
    for (int64_t round=0; round<rounds; ++round) {
        for (uint64_t m=0; m<n_monkeys; ++m) {
            uint64_t list_size = list_i64_size(monkeys[m].items);
            inspected[m] += list_size;
            
            __m256i monkey_test = _mm256_set1_epi64x(monkeys[m].test);
            __m256d monkey_test_inverse = _mm256_set1_pd(monkeys[m].test_inverse);
            
            for (uint64_t i=0; i<list_size; i+=4) {
                __m256i result = { 
                    monkeys[m].items->array[i], 
                    monkeys[m].items->array[i+1],
                    monkeys[m].items->array[i+2],
                    monkeys[m].items->array[i+3],
                };
                __m256i simd_numbers = { 
                    (monkeys[m].number == OLD_ITEM) ? monkeys[m].items->array[i]   : monkeys[m].number, 
                    (monkeys[m].number == OLD_ITEM) ? monkeys[m].items->array[i+1] : monkeys[m].number,
                    (monkeys[m].number == OLD_ITEM) ? monkeys[m].items->array[i+2] : monkeys[m].number,
                    (monkeys[m].number == OLD_ITEM) ? monkeys[m].items->array[i+3] : monkeys[m].number,
                };
                
                if (monkeys[m].op == '+') {
                    result = _mm256_add_epi64(result, simd_numbers);
                } else {
                    result = _mm256_mul_epu32(result, simd_numbers);
                }
                
                
                if (part == 1) {
                    result = simd_double_to_int64_256(_mm256_floor_pd(_mm256_mul_pd(simd_int64_to_double_256(result), simd_p1_divisor_inverse)));
                } else {
                    result = simd_modulo_mulinv(result, simd_p2_divisor, simd_p2_divisor_inverse);
                }
                
                _mm256_storeu_si256((__m256i*) res, result);
                
                __m256i conditions = simd_modulo_mulinv(result, monkey_test, monkey_test_inverse);
                
                _mm256_storeu_si256((__m256i*) cond, conditions);
                            
                for (int64_t j=0; j<4 && (i+j)<list_size; ++j) {
                    if (cond[j] == 0) {
                        list_i64_push_back(monkeys[monkeys[m].to_true].items, res[j]);
                    } else {
                        list_i64_push_back(monkeys[monkeys[m].to_false].items, res[j]);
                    }
                }
            }
            
            list_i64_clear(monkeys[m].items);
        }
    }
    
    int64_t r1=INT64_MIN, r2=INT64_MIN;
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        if (inspected[m] > r1) {
            r2 = r1;
            r1 = inspected[m];
        } else if (inspected[m] > r2) {
            r2 = inspected[m];
        }
    }
    free(inspected);
    return r1*r2;
}

static void parse(char** data, uint64_t data_size, uint64_t n_monkeys, monkey* monkeys) {
    int64_t m = 0;
    for (uint64_t i = 0; i < data_size; ++i) {
        if (strncmp(data[i], "Monkey ", strlen("Monkey ")) == 0) {
            m = strtol(data[i] + strlen("Monkey "), NULL, 10);
            assert(m >= 0);
            assert(m < n_monkeys);
        } else if (strncmp(data[i], "  Starting items: ", strlen("  Starting items: ")) == 0) {
            char* next = data[i] + strlen("  Starting items: ");
            while (next < data[i] + strlen(data[i])) {
                list_i64_push_back(monkeys[m].items, strtol(next, &next, 10));
                next += strlen(", ");
            }
        } else if (strncmp(data[i], "  Operation: new = old ", strlen("  Operation: new = old ")) == 0) {
            char op = data[i][strlen("  Operation: new = old ")];
            assert(op == '+' || op == '*');
            monkeys[m].op = op;
            if (data[i][strlen("  Operation: new = old * ")] == 'o') {
                monkeys[m].number = OLD_ITEM;
            } else {
                monkeys[m].number = strtol(data[i] + strlen("  Operation: new = old * "), NULL, 10);
            }
        } else if (strncmp(data[i], "  Test: divisible by ", strlen("  Test: divisible by ")) == 0) {
            int64_t t = strtol(data[i] + strlen("  Test: divisible by "), NULL, 10);
            assert(t > 0);
            monkeys[m].test = t;
            monkeys[m].test_inverse = 1.0/((double) t);
        } else if (strncmp(data[i], "    If true: throw to monkey ", strlen("    If true: throw to monkey ")) == 0) {
            int64_t to_monkey = strtol(data[i] + strlen("    If true: throw to monkey "), NULL, 10);
            assert(to_monkey >= 0);
            assert(to_monkey < n_monkeys);
            assert(to_monkey != m);  // Ensure monkey not throwing to itself?
            monkeys[m].to_true = to_monkey;
        } else if (strncmp(data[i], "    If false: throw to monkey ", strlen("    If false: throw to monkey ")) == 0) {
            int64_t to_monkey = strtol(data[i] + strlen("    If false: throw to monkey "), NULL, 10);
            assert(to_monkey >= 0);
            assert(to_monkey < n_monkeys);
            assert(to_monkey != m);  // Ensure monkey not throwing to itself?
            monkeys[m].to_false = to_monkey;
        }
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    uint64_t n_monkeys = 0;
    
    for (uint64_t i = 0; i < data_size; ++i) {
        if (strncmp(data[i], "Monkey ", strlen("Monkey ")) == 0) {
            n_monkeys++;
        }
    }
    
    monkey* monkeys = calloc(n_monkeys, sizeof(monkey));
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        monkeys[m].items = list_i64_init(64);
    }
    parse(data, data_size, n_monkeys, monkeys);
    *part1 = simulate(n_monkeys, monkeys, 1);
    
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        list_i64_clear(monkeys[m].items);
    }
    parse(data, data_size, n_monkeys, monkeys);
    *part2 = simulate(n_monkeys, monkeys, 2);

    for (uint64_t m = 0; m < n_monkeys; ++m) {
        list_i64_free(monkeys[m].items);
    }
    free(monkeys);
}
