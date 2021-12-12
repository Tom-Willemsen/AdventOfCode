#include "day12_impl.h"

static const int64_t START_ID = 2;
static const int64_t END_ID = 3;

static int64_t name_to_id(char* name) {
    if (strncmp(name, "start", 6) == 0) {
        return START_ID;
    } else if (strncmp(name, "end", 4) == 0) {
        return END_ID;
    } else {
        assert(strnlen(name, 10) == 2);
        return (name[0] * 256) + name[1];
    }
}

static inline int64_t is_small(int64_t id) {
    return (id % 256) > 96;
}

static list_tuple_i64* parse_connections(char** data, uint64_t data_size) {
    char b1[10], b2[10];
    int64_t id1, id2;
    list_tuple_i64* conns = list_tuple_i64_init(data_size * 2);
    for (uint64_t i=0; i<data_size; ++i) {
        sscanf(data[i], "%10[^-]-%10[^-\n]" SCNd64, b1, b2);
        id1 = name_to_id(b1);
        id2 = name_to_id(b2);
        list_tuple_i64_push_back(conns, id1, id2);
        list_tuple_i64_push_back(conns, id2, id1);
    }
    return conns;
}

static int64_t can_visit_p1(list_i64* path, int64_t node) {
    if (node == START_ID) {
        return 0;
    }
    if (!is_small(node)) {
        return 1;
    }
    return !list_i64_contains(path, node);
}

static int64_t can_visit_p2(list_i64* path, int64_t node) {
    int64_t pn, vc2 = 0;
    if (node == START_ID) {
        return 0;
    }
    if (!is_small(node)) {
        return 1;
    }
    for (uint64_t i=0; i<list_i64_size(path); ++i) {
        pn = list_i64_get(path, i);
        if (is_small(pn) && list_i64_count(path, pn) >= 2) {
            vc2 = 1;
            break;
        }
    }
    if (vc2) {
        return !list_i64_contains(path, node);
    } else {
        return 1;
    }
}

static void extend_path(list_i64* path, int64_t node, list_tuple_i64* conns, int64_t* n_paths, int64_t (*visit_func)(list_i64*, int64_t)) {
    int64_t nodefrom, nodeto;
    for (uint64_t i=0; i<list_tuple_i64_size(conns); ++i) {
        list_tuple_i64_get(conns, i, &nodefrom, &nodeto);
        if (nodefrom == node) {
            if (nodeto == END_ID) {
                (*n_paths)++;
            } else if ((*visit_func)(path, nodeto)) {
                list_i64_push_back(path, nodeto);
                extend_path(path, nodeto, conns, n_paths, visit_func);
                list_i64_pop_back(path);
            }
        }
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    list_tuple_i64* conns = parse_connections(data, data_size);
    list_i64* path = list_i64_init(50);
    list_i64_push_back(path, START_ID);
    
    *part1 = 0;
    *part2 = 0;
    
    extend_path(path, START_ID, conns, part1, can_visit_p1);
    extend_path(path, START_ID, conns, part2, can_visit_p2);
    
    list_i64_free(path);
    list_tuple_i64_free(conns);
}
