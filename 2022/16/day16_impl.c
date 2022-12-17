#include "day16_impl.h"


static const int64_t VALVE_NOT_OPEN = INT64_MAX;

typedef struct valve {
    uint64_t id;
    int64_t rate;
    int64_t opened_at;
    list_tuple_i64* connections_by_name;  // tuple is the two characters of the valve name.
    int64_t name1;
    int64_t name2;
} valve;


static uint64_t movement_cost_key(uint64_t num_valves, uint64_t id1, uint64_t id2) {
    return id1*num_valves + id2;
}


static int64_t calc_score(uint64_t num_valves, valve* valves, list_tuple_i64* route) {
    int64_t score = 0;
    for (uint64_t r=0; r<list_tuple_i64_size(route); ++r) {
        int64_t id, cost;
        list_tuple_i64_get(route, r, &id, &cost);
        score += (30-cost) * valves[id].rate;
    }
    return score;
}


static inline int64_t valve_in_route(int64_t id, list_tuple_i64* route) {
    for (int64_t r=0; r<list_tuple_i64_size(route); ++r) {
        int64_t route_id, route_cost;
        list_tuple_i64_get(route, r, &route_id, &route_cost);
        if (route_id == id) {
            return 1;
        }
    }
    return 0;
}


static void dfs(uint64_t num_valves, valve* valves, list_tuple_i64* route, list_i64* good_valve_ids, map_i64* movement_costs, int64_t* best_score) {
    int64_t ideal_remaining = 0;
    
    int64_t end_id, end_cost;
    list_tuple_i64_peek_back(route, &end_id, &end_cost);
    
    if (end_cost == 30) {
        *best_score = max(calc_score(num_valves, valves, route), *best_score);
        return;
    }
    
    uint64_t all_open = 1;
    
    for (uint64_t i=0; i<list_i64_size(good_valve_ids); ++i) {
        int64_t valve_id = list_i64_get(good_valve_ids, i);
        if (!valve_in_route(valve_id, route)) {
            all_open = 0;
            break;
        }
    }
    
    if (all_open) {
        *best_score = max(calc_score(num_valves, valves, route), *best_score);
        return;
    }
    
    for (uint64_t i=0; i<num_valves; ++i) {
        ideal_remaining += valves[i].rate * (30 - end_cost);
    }
    
    int64_t score = calc_score(num_valves, valves, route);
    if (score + ideal_remaining < *best_score) {
        return;
    }
    
    for (uint64_t i=0; i<list_i64_size(good_valve_ids); ++i) {
        int64_t next = list_i64_get(good_valve_ids, i);
        if (next == end_id || valves[next].rate == 0 || valve_in_route(next, route)) {
            continue;
        }
        
        int64_t cost = map_i64_get(movement_costs, movement_cost_key(num_valves, end_id, next), INT64_MAX);
        if (cost == INT64_MAX) {
            assert(0);
        }
        if (end_cost + cost < 30) {
            list_tuple_i64_push_back(route, next, end_cost + cost + 1);
            dfs(num_valves, valves, route, good_valve_ids, movement_costs, best_score);
            int64_t ig1, ig2;
            list_tuple_i64_pop_back(route, &ig1, &ig2);
        }
    }
}


static uint64_t valve_id_from_names(uint64_t data_size, valve* valves, int64_t name1, int64_t name2) {
    for (uint64_t i=0; i<data_size; ++i) {
        if (valves[i].name1 == name1 && valves[i].name2 == name2) {
            return i;
        }
    }
    printf("Can't find valve with name %c%c\n", (char) name1, (char) name2);
    assert(0);
    return 0;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t start_valve_id = 0;
    valve* valves = calloc(data_size, sizeof(valve));
    
    for (uint64_t i=0; i<data_size; ++i) {
        int64_t rate;
        char name1, name2;
        char buff[100] = {0};
        sscanf(data[i], "Valve %c%c has flow rate=%ld; %*s %*s to %*s %99[^\n]", &name1, &name2, &rate, buff);
        valves[i].id = i;
        valves[i].connections_by_name = list_tuple_i64_init(8);
        valves[i].opened_at = VALVE_NOT_OPEN;
        valves[i].rate = rate;
        valves[i].name1 = name1;
        valves[i].name2 = name2;
        
        if (name1 == 'A' && name2 == 'A') {
            start_valve_id = i;
        }
        
        uint64_t pos = 0;
        while (pos <= strnlen(buff, 100)) {
            list_tuple_i64_push_back(valves[i].connections_by_name, buff[pos], buff[pos+1]);
            pos += 4;
        }
    }
    
    map_i64* movement_costs = map_i64_init(256);
    
    for (uint64_t id1=0; id1<data_size; ++id1) {
        for (uint64_t id2=id1; id2<data_size; ++id2) {
            if (id1 == id2) {
                map_i64_set(movement_costs, movement_cost_key(data_size, id1, id2), 0);
                map_i64_set(movement_costs, movement_cost_key(data_size, id2, id1), 0);
            } else {
                set_i64* visible = set_i64_init(data_size);
                
                set_i64_add(visible, id1);
                
                for (uint64_t depth = 1; depth <= data_size; ++depth) {
                    int64_t id;
                    set_i64* new_connections = set_i64_init(data_size);
                    set_i64_iterator* iter = set_i64_iter(visible);
                    while (set_i64_next(iter, &id)) {
                        for (uint64_t i=0; i<list_tuple_i64_size(valves[id].connections_by_name); ++i) {
                            int64_t n1, n2;
                            list_tuple_i64_get(valves[id].connections_by_name, i, &n1, &n2);
                            set_i64_add(new_connections, valve_id_from_names(data_size, valves, n1, n2));
                        }
                    }
                    set_i64_iter_free(iter);
                    
                    if (set_i64_contains(new_connections, id2)) {
                        map_i64_set(movement_costs, movement_cost_key(data_size, id1, id2), depth);
                        map_i64_set(movement_costs, movement_cost_key(data_size, id2, id1), depth);
                        
                        set_i64_free(new_connections);
                        break;
                    }
                    
                    iter = set_i64_iter(new_connections);
                    while (set_i64_next(iter, &id)) {
                        set_i64_add(visible, id);
                    }
                    set_i64_iter_free(iter);
                    set_i64_free(new_connections);
                }
                
                set_i64_free(visible);
            }
        }
    }
    
    list_i64* good_valve_ids = list_i64_init(data_size);
    list_i64_push_back(good_valve_ids, start_valve_id);
    for (uint64_t i=0; i<data_size; ++i) {
        if (valves[i].rate > 0) {
            list_i64_push_back(good_valve_ids, valves[i].id);
        }
    }
    
    list_tuple_i64* route = list_tuple_i64_init(32);
    list_tuple_i64_push_back(route, start_valve_id, 0);
    
    dfs(data_size, valves, route, good_valve_ids, movement_costs, part1);
    
    for (uint64_t i=0; i<data_size; ++i) {
        list_tuple_i64_free(valves[i].connections_by_name);
        valves[i].connections_by_name = NULL;
    }
    list_tuple_i64_free(route);
    list_i64_free(good_valve_ids);
    map_i64_free(movement_costs);
    free(valves);
}
