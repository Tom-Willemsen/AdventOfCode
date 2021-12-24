#include "day24_impl.h"
#include <omp.h>


static inline void parse_numbers(int64_t* mem, char* line, int64_t* n1, int64_t* n2) {
    char* n1_start = &line[4];
    char* n2_start;
    if (*n1_start >= 'w' && *n1_start <= 'z') {
        *n1 = mem[*n1_start - 'w'];
        n2_start = &line[6];
    } else {
        *n1 = strtol(n1_start, &n2_start, 10);
    }
    
    if (*n2_start >= 'w' && *n2_start <= 'z') {
        *n2 = mem[*n2_start - 'w'];
    } else {
        *n2 = strtol(n2_start, NULL, 10);
    }
}


static int64_t execute_prog(char** program, uint64_t start, uint64_t stop, int64_t input, int64_t z) {
    int64_t mem[4] = {0, 0, 0, z};
    int64_t n1, n2;
    char* cmd;
    
    for (uint64_t i=start; i<stop; ++i) {
        cmd = program[i];
        if (strncmp(cmd, "inp", 3) == 0) {
            assert(cmd[4] == 'w');
            mem[0] = input;
        } else if (strncmp(cmd, "add", 3) == 0) {
            assert(cmd[4] >= 'w' && cmd[4] <= 'z');
            parse_numbers(mem, cmd, &n1, &n2);
            mem[cmd[4]-'w'] = n1 + n2;
            
        } else if (strncmp(cmd, "mul", 3) == 0) {
            assert(cmd[4] >= 'w' && cmd[4] <= 'z');
            parse_numbers(mem, cmd, &n1, &n2);
            mem[cmd[4]-'w'] = n1 * n2;
            
        } else if (strncmp(cmd, "div", 3) == 0) {
            assert(cmd[4] >= 'w' && cmd[4] <= 'z');
            parse_numbers(mem, cmd, &n1, &n2);
            if (n2 == 0) {
                return INT64_MAX;
            }
            mem[cmd[4]-'w'] = n1 / n2;
            
        } else if (strncmp(cmd, "mod", 3) == 0) {
            assert(cmd[4] >= 'w' && cmd[4] <= 'z');
            parse_numbers(mem, cmd, &n1, &n2);
            if (n1 < 0 || n2 <= 0) {
                return INT64_MAX;
            }
            mem[cmd[4]-'w'] = n1 % n2;
            
        } else {
            assert(strncmp(cmd, "eql", 3) == 0);
            assert(cmd[4] >= 'w' && cmd[4] <= 'z');
            parse_numbers(mem, cmd, &n1, &n2);
            mem[cmd[4]-'w'] = n1 == n2 ? 1 : 0;
            
        }
    }
    return mem[3];
}

static int64_t execute_prog_memo(char** program, map_i64* cache, uint64_t start, uint64_t stop, int64_t input, int64_t z) {
    int64_t id = (start << 48) + (stop << 32) + (input << 24) + z;
    int64_t result = map_i64_get(cache, id, INT64_MIN);
    if (result == INT64_MIN) {
        result = execute_prog(program, start, stop, input, z);
        map_i64_set(cache, id, result);
        return result;
    } else {
        return result;
    }
}

static void dfs(char** program, map_i64* cache, list_i64* indices, list_i64* inputs, list_i64* max_z, int64_t z, int64_t* solution, int64_t is_part2) {
    int64_t iz;
    assert(list_i64_size(inputs) <= 14);
    
    if (list_i64_size(inputs) == 0) {
        iz = 0;
    } else {
        iz = execute_prog_memo(
                 program, 
                 cache,
                 list_i64_get(indices, list_i64_size(inputs)-1), 
                 list_i64_get(indices, list_i64_size(inputs)), 
                 list_i64_peek_back(inputs), 
                 z);
    }
    
    if (list_i64_size(inputs) == 14) {
        if (iz == 0) {
            *solution = 0;
            for (uint64_t i=0; i<14; ++i) {
                (*solution) *= 10;
                (*solution) += list_i64_get(inputs, i);
            }
        }
        return;
    }
    
    if (iz > list_i64_get(max_z, list_i64_size(inputs))) {
        return;
    }
    
    if (!is_part2) {
        for (int64_t new=9; new>=1; --new) {
            list_i64_push_back(inputs, new);
            dfs(program, cache, indices, inputs, max_z, iz, solution, is_part2);
            list_i64_pop_back(inputs);
            if (*solution != -1) {
                return;
            }
        }
    } else {
        for (int64_t new=1; new<=9; ++new) {
            list_i64_push_back(inputs, new);
            dfs(program, cache, indices, inputs, max_z, iz, solution, is_part2);
            list_i64_pop_back(inputs);
            if (*solution != -1) {
                return;
            }
        }
    }
}

void calculate(char** program, uint64_t data_size, int64_t* part1, int64_t* part2) {
    list_i64* indices = list_i64_init(15);
    list_i64* max_z = list_i64_init(15);
    
    for (uint64_t i=0; i<data_size; ++i) {
        if (strncmp(program[i], "inp", 3) == 0) {
            list_i64_push_back(indices, i);
        }
    }
    list_i64_push_back(indices, data_size);
    assert(list_i64_size(indices) == 15);
    
    // this is a bit of a trick - we can exit quite early if we can tell that z can't possibly grow/shrink enough
    // by the end of the program to allow it to be zerod. We precompute the max sizes here - any block that has
    // a "div z 26" instruction will shrink z by a factor of about 26, otherwise z will grow by a factor of about 26.
    int64_t max_allowed = 1;
    for (int64_t i=list_i64_size(indices)-2; i>=0; --i) {
        int64_t s = list_i64_get(indices, i);
        int64_t e = list_i64_get(indices, i+1);
        int64_t contains_div = 0;
        for (uint64_t j=s; j<e; ++j) {
            if (strncmp(program[j], "div z 26", 8) == 0) {
                contains_div = 1;
                break;
            }
        }
        if (contains_div) {
            max_allowed *= 26;
        } else {
            max_allowed /= 26;
        }
        list_i64_push_front(max_z, max_allowed);
    }

    *part1 = -1;
    *part2 = -1;
    
    #pragma omp parallel num_threads(2)
    {
        list_i64* inputs = list_i64_init(10);
        map_i64* cache = map_i64_init(100000);

        #pragma omp sections
        {
            #pragma omp section
            dfs(program, cache, indices, inputs, max_z, 0, part1, 0);
            
            #pragma omp section
            dfs(program, cache, indices, inputs, max_z, 0, part2, 1);
        }

        list_i64_free(inputs);
        map_i64_free(cache);
    }
    
    list_i64_free(indices);
    list_i64_free(max_z);
}
