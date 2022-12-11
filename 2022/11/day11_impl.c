#include "day11_impl.h"

static const int64_t OLD_ITEM = INT64_MIN;

static int64_t simulate(
    uint64_t n_monkeys, 
    list_i64** monkey_items, 
    const char* const operations, 
    const int64_t* const numbers, 
    const int64_t* const tests, 
    const int64_t* const true_throws, 
    const int64_t* const false_throws, 
    uint8_t part
) 
{
    int64_t divisor = 1;
    int64_t* inspected = calloc(n_monkeys, sizeof(int64_t));
    
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        divisor *= tests[m];
    }
    
    int64_t rounds = (part == 2) ? 10000 : 20;
    
    for (int64_t round=0; round<rounds; ++round) {
        for (uint64_t m=0; m<n_monkeys; ++m) {
            inspected[m] += list_i64_size(monkey_items[m]);
            while(list_i64_size(monkey_items[m]) > 0) {
                int64_t item = list_i64_pop_back(monkey_items[m]);
                int64_t num = numbers[m];
                
                if (operations[m] == '+') {
                    item += (num == OLD_ITEM) ? item : num;
                } else {
                    item *= (num == OLD_ITEM) ? item : num;
                }
                
                if (part == 1) {
                    item /= 3;
                }
                
                item %= divisor;
                
                if (item % tests[m] == 0) {
                    list_i64_push_back(monkey_items[true_throws[m]], item);
                } else {
                    list_i64_push_back(monkey_items[false_throws[m]], item);
                }
            }
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

static void parse(char** data, uint64_t data_size, uint64_t n_monkeys, list_i64** monkey_items, char* operations, int64_t* numbers, int64_t* tests, int64_t* true_throws, int64_t* false_throws) {
    int64_t monkey = 0;
    for (uint64_t i = 0; i < data_size; ++i) {
        if (strncmp(data[i], "Monkey ", strlen("Monkey ")) == 0) {
            monkey = strtol(data[i] + strlen("Monkey "), NULL, 10);
            assert(monkey < n_monkeys);
        } else if (strncmp(data[i], "  Starting items: ", strlen("  Starting items: ")) == 0) {
            
            char* next = data[i] + strlen("  Starting items: ");
            while (next < data[i] + strlen(data[i])) {
                list_i64_push_back(monkey_items[monkey], strtol(next, &next, 10));
                next += strlen(", ");
            }
        } else if (strncmp(data[i], "  Operation: new = old ", strlen("  Operation: new = old ")) == 0) {
            char op = data[i][strlen("  Operation: new = old ")];
            assert(op == '+' || op == '*');
            operations[monkey] = op;
            
            if (data[i][strlen("  Operation: new = old * ")] == 'o') {
                numbers[monkey] = OLD_ITEM;
            } else {
                numbers[monkey] = strtol(data[i] + strlen("  Operation: new = old * "), NULL, 10);
            }
        } else if (strncmp(data[i], "  Test: divisible by ", strlen("  Test: divisible by ")) == 0) {
            int64_t t = strtol(data[i] + strlen("  Test: divisible by "), NULL, 10);
            assert(t > 0);
            tests[monkey] = t;
        } else if (strncmp(data[i], "    If true: throw to monkey ", strlen("    If true: throw to monkey ")) == 0) {
            int64_t to_monkey = strtol(data[i] + strlen("    If true: throw to monkey "), NULL, 10);
            assert(to_monkey < n_monkeys);
            true_throws[monkey] = to_monkey;
        } else if (strncmp(data[i], "    If false: throw to monkey ", strlen("    If false: throw to monkey ")) == 0) {
            int64_t to_monkey = strtol(data[i] + strlen("    If false: throw to monkey "), NULL, 10);
            assert(to_monkey < n_monkeys);
            false_throws[monkey] = to_monkey;
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
    printf("n_monkeys: %lu\n", n_monkeys);
    
    list_i64** monkey_items_p1 = calloc(n_monkeys, sizeof(list_i64*));
    list_i64** monkey_items_p2 = calloc(n_monkeys, sizeof(list_i64*));
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        monkey_items_p1[m] = list_i64_init(1);
    }
    char* operations = calloc(n_monkeys, sizeof(uint8_t));
    int64_t* numbers = calloc(n_monkeys, sizeof(int64_t));
    int64_t* tests = calloc(n_monkeys, sizeof(int64_t));
    int64_t* true_throws = calloc(n_monkeys, sizeof(int64_t));
    int64_t* false_throws = calloc(n_monkeys, sizeof(int64_t));
    
    parse(data, data_size, n_monkeys, monkey_items_p1, operations, numbers, tests, true_throws, false_throws);
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        monkey_items_p2[m] = list_i64_copy(monkey_items_p1[m]);
    }
    
    *part1 = simulate(n_monkeys, monkey_items_p1, operations, numbers, tests, true_throws, false_throws, 1);
    *part2 = simulate(n_monkeys, monkey_items_p2, operations, numbers, tests, true_throws, false_throws, 2);

    free(false_throws);
    free(true_throws);
    free(tests);
    free(numbers);
    free(operations);
    for (uint64_t m = 0; m < n_monkeys; ++m) {
        list_i64_free(monkey_items_p1[m]);
        list_i64_free(monkey_items_p2[m]);
    }
    free(monkey_items_p2);
    free(monkey_items_p1);
}
