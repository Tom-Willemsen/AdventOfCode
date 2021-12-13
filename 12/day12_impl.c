#include "day12_impl.h"

static const int64_t START_ID = 2;
static const int64_t END_ID = 3;

static int64_t name_to_id(const char* const name) {
    if (strncmp(name, "start", 6) == 0) {
        return START_ID;
    } else if (strncmp(name, "end", 4) == 0) {
        return END_ID;
    } else {
        if (strnlen(name, 2) == 1) {
            return name[0];
        } else {
            assert(name[0] > 96 == name[1] > 96);
            return (name[0] * 256) + name[1];
        }
    }
}

static inline int64_t is_small(const int64_t id) {
    return (id & 0xFF) > 96;
}

static inline int64_t is_big(const int64_t id) {
    return id != END_ID && id != START_ID && !is_small(id);
}

static list_tuple_i64* compact_connection_graph(list_tuple_i64* in) {
    int64_t id1, id2, id3, id4;
    list_tuple_i64* out = list_tuple_i64_init(list_tuple_i64_size(in) * 2);
    for (uint64_t i=0; i<list_tuple_i64_size(in); ++i) {
        list_tuple_i64_get(in, i, &id1, &id2);

        if (is_big(id2)) {
            // Graph compaction: big caves can always be travelled through. This replaces:
            // [cave 1] -> [big cave] -> [cave 2]
            // with:
            // [cave 1] -> [cave 2]
            // eliminating [big cave] from the graph entirely.
            for (uint64_t j=0; j<list_tuple_i64_size(in); ++j) {
                list_tuple_i64_get(in, j, &id3, &id4);
                if (id2 == id3 && id4 != START_ID && id1 != END_ID) {
                    list_tuple_i64_push_back(out, id1, id4);
                }
            }

            // We (should) never have two big caves next to each other. Assert this in debug mode.
            assert(!is_big(id1));

        } else if (id2 != START_ID && id1 != END_ID && !is_big(id1)) {
            // We can never be travelling to START_ID or from END_ID, prune these vertices.
            // Cave 1 also can't be a big cave as we compacted all big caves above.
            list_tuple_i64_push_back(out, id1, id2);
        }
    }
    list_tuple_i64_free(in);
    return out;
}

static list_tuple_i64* parse_connections(char** data, uint64_t data_size) {
    char b1[10], b2[10];
    int64_t id1, id2;
    list_tuple_i64* conns = list_tuple_i64_init(data_size * 2);
    for (uint64_t i=0; i<data_size; ++i) {
        sscanf(data[i], "%10[^-]-%10[^\n]" SCNd64, b1, b2);
        id1 = name_to_id(b1);
        id2 = name_to_id(b2);
        list_tuple_i64_push_back(conns, id1, id2);
        list_tuple_i64_push_back(conns, id2, id1);
    }
    return conns;
}

static void extend_path(set_i64* path, int64_t node, list_tuple_i64* conns, int64_t* n_paths, int64_t vsc2) {
    int64_t nodefrom, nodeto, already_visited;
    for (uint64_t i=0; i<list_tuple_i64_size(conns); ++i) {
        list_tuple_i64_get(conns, i, &nodefrom, &nodeto);
        if (nodefrom == node) {
            if (nodeto == END_ID) {
                (*n_paths)++;
            } else {
                already_visited = set_i64_contains(path, nodeto);
                if (!(vsc2 && already_visited)) {
                    set_i64_add(path, nodeto);
                    extend_path(path, nodeto, conns, n_paths, vsc2 || already_visited);
                    if (!already_visited) {
                        set_i64_remove(path, nodeto);
                    }
                }
            }
        }
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    list_tuple_i64* conns = parse_connections(data, data_size);
    set_i64* path = set_i64_init(32);

    *part1 = 0;
    *part2 = 0;

    conns = compact_connection_graph(conns);

    extend_path(path, START_ID, conns, part1, 1);
    extend_path(path, START_ID, conns, part2, 0);

    set_i64_free(path);
    list_tuple_i64_free(conns);
}
