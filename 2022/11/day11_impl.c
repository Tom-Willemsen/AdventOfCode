#include "day11_impl.h"

static const int64_t OLD_ITEM = INT64_MIN;

typedef struct monkey {
    list_i64* items;
    int64_t number;
    int64_t op;
    int64_t to_true;
    int64_t to_false;
    int64_t test;
    struct libdivide_s64_t fast_divisor;
} monkey;

static int64_t simulate(uint64_t n_monkeys, monkey* monkeys, uint8_t part) 
{
    int64_t divisor = 1;
    int64_t* inspected = calloc(n_monkeys, sizeof(int64_t));
    
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        divisor *= monkeys[m].test;
    }
    
    int64_t rounds = (part == 2) ? 10000 : 20;
    
    struct libdivide_s64_t fast_divisor = libdivide_s64_gen(divisor);
    
    for (int64_t round=0; round<rounds; ++round) {
        for (uint64_t m=0; m<n_monkeys; ++m) {
            uint64_t list_size = list_i64_size(monkeys[m].items);
            inspected[m] += list_size;

            for (uint64_t i=0; i<list_size; ++i) {
                int64_t item = list_i64_get(monkeys[m].items, i);
                
                if (item >= (1ULL<<26)) {
                    item = item - libdivide_s64_do(item, &fast_divisor) * divisor;
                }
                
                if (monkeys[m].op == '+') {
                    item += (monkeys[m].number == OLD_ITEM) ? item : monkeys[m].number;
                } else {
                    item *= (monkeys[m].number == OLD_ITEM) ? item : monkeys[m].number;
                }
                
                if (part == 1) {
                    item /= 3;
                }
                
                if (item - libdivide_s64_do(item, &monkeys[m].fast_divisor) * monkeys[m].test == 0) {
                    list_i64_push_back(monkeys[monkeys[m].to_true].items, item);
                } else {
                    list_i64_push_back(monkeys[monkeys[m].to_false].items, item);
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
            monkeys[m].fast_divisor = libdivide_s64_gen(t);
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
