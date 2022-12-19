#include "day16_impl.h"

typedef struct valve {
    uint64_t id;
    int64_t rate;
    list_tuple_i64* connections_by_name;  // tuple is the two characters of the valve name.
    int64_t name1;
    int64_t name2;
} valve;


static inline uint64_t movement_cost_key(uint64_t num_valves, uint64_t id1, uint64_t id2) {
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


static int64_t calc_score2(uint64_t num_valves, valve* valves, list_tuple_i64* route1, list_tuple_i64* route2) {
    int64_t score = 0;
    for (uint64_t r=0; r<list_tuple_i64_size(route1); ++r) {
        int64_t id, cost;
        list_tuple_i64_get(route1, r, &id, &cost);
        score += (26-cost) * valves[id].rate;
    }
    for (uint64_t r=0; r<list_tuple_i64_size(route2); ++r) {
        int64_t id, cost;
        list_tuple_i64_get(route2, r, &id, &cost);
        score += (26-cost) * valves[id].rate;
    }
    return score;
}


static void dfs(uint64_t num_valves, valve* valves, list_tuple_i64* route, list_i64* unopened_valve_ids, int64_t* movement_costs, int64_t* best_score) {
    int64_t ideal_remaining = 0;
    int64_t end_id, end_cost;
    
    if (list_i64_size(unopened_valve_ids) == 0) {
        *best_score = max(calc_score(num_valves, valves, route), *best_score);
        return;
    }
    
    list_tuple_i64_peek_back(route, &end_id, &end_cost);
    
    for (uint64_t i=0; i<list_i64_size(unopened_valve_ids); ++i) {
        int64_t gv_id = list_i64_get(unopened_valve_ids, i);
        int64_t gv_cost = movement_costs[movement_cost_key(num_valves, end_id, gv_id)];
        ideal_remaining += max(valves[list_i64_get(unopened_valve_ids, i)].rate * (30 - end_cost - gv_cost - 1), 0);
    }
    
    int64_t score = calc_score(num_valves, valves, route);
    *best_score = max(*best_score, score);
    if (score + ideal_remaining <= *best_score) {
        return;
    }
    
    for (uint64_t i=0; i<list_i64_size(unopened_valve_ids); ++i) {
        int64_t next = list_i64_get(unopened_valve_ids, i);
        int64_t cost = movement_costs[movement_cost_key(num_valves, end_id, next)];
        
        if (end_cost + cost < 30) {
            list_tuple_i64_push_back(route, next, end_cost + cost + 1);
            list_i64_remove(unopened_valve_ids, i);
            
            dfs(num_valves, valves, route, unopened_valve_ids, movement_costs, best_score);
            
            list_i64_insert(unopened_valve_ids, i, next);
            list_tuple_i64_remove(route, list_tuple_i64_size(route) - 1);
        }
    }
}


static void dfs2(uint64_t num_valves, valve* valves, list_tuple_i64* route1, list_tuple_i64* route2, list_i64* unopened_valve_ids, int64_t* movement_costs, int64_t* best_score) {
    int64_t ideal_remaining = 0;
    int64_t end1_id, end1_cost, end2_id, end2_cost;
    
    if (list_i64_size(unopened_valve_ids) == 0) {
        *best_score = max(calc_score2(num_valves, valves, route1, route2), *best_score);
        return;
    }
    
    list_tuple_i64_peek_back(route1, &end1_id, &end1_cost);
    list_tuple_i64_peek_back(route2, &end2_id, &end2_cost);
    
    for (uint64_t i=0; i<list_i64_size(unopened_valve_ids); ++i) {
        int64_t gv_id = list_i64_get(unopened_valve_ids, i);
        int64_t ideal_score = max(max(
            valves[gv_id].rate * (26 - end1_cost - movement_costs[movement_cost_key(num_valves, end1_id, gv_id)] - 1), 
            valves[gv_id].rate * (26 - end2_cost - movement_costs[movement_cost_key(num_valves, end2_id, gv_id)] - 1)
        ), 0);
        ideal_remaining += ideal_score;
    }
    
    int64_t score = calc_score2(num_valves, valves, route1, route2);
    *best_score = max(*best_score, score);
    if (score + ideal_remaining <= *best_score) {
        return;
    }
    
    for (int64_t i=list_i64_size(unopened_valve_ids)-1; i>=0; --i) {
        int64_t next = list_i64_get(unopened_valve_ids, i);
        
        int64_t cost1 = movement_costs[movement_cost_key(num_valves, end1_id, next)] + end1_cost + 1;

        if (cost1 < 26) {
            list_tuple_i64_push_back(route1, next, cost1);
            list_i64_remove(unopened_valve_ids, i);
            
            dfs2(num_valves, valves, route1, route2, unopened_valve_ids, movement_costs, best_score);
            
            list_i64_insert(unopened_valve_ids, i, next);
            list_tuple_i64_remove(route1, list_tuple_i64_size(route1) - 1);
        }
    }
    
    // Extra condition checking list size > 1 - both routes start at the 'AA' node, it's useless to check an
    // exact transposition. So exclude the case where we're looking at 'AA' only.
    if (!(list_tuple_i64_size(route2) == 1 && list_tuple_i64_size(route1) == 1)) {
        for (int64_t i=list_i64_size(unopened_valve_ids)-1; i>=0; --i) {
            int64_t next = list_i64_get(unopened_valve_ids, i);
            int64_t cost2 = movement_costs[movement_cost_key(num_valves, end2_id, next)] + end2_cost + 1;

            if (cost2 < 26) {
                list_tuple_i64_push_back(route2, next, cost2);
                list_i64_remove(unopened_valve_ids, i);
                
                dfs2(num_valves, valves, route1, route2, unopened_valve_ids, movement_costs, best_score);
                
                list_i64_insert(unopened_valve_ids, i, next);
                list_tuple_i64_remove(route2, list_tuple_i64_size(route2) - 1);
            }
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
    
    int64_t* movement_costs = calloc(movement_cost_key(data_size, data_size-1, data_size-1)+1, sizeof(int64_t));
    
    // Build up a map of movement costs from any arbitrary node to any other arbitrary node.
    // The paths are direct.
    for (uint64_t id1=0; id1<data_size; ++id1) {
        for (uint64_t id2=id1; id2<data_size; ++id2) {
            if (id1 == id2) {
                movement_costs[movement_cost_key(data_size, id1, id2)] = 0;
                movement_costs[movement_cost_key(data_size, id2, id1)] = 0;
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
                        movement_costs[movement_cost_key(data_size, id1, id2)] = depth;
                        movement_costs[movement_cost_key(data_size, id2, id1)] = depth;
                        
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
    
    // These are the only valve IDs we will consider for 
    // next moves during the DFS.
    list_i64* unopened_valve_ids = list_i64_init(32);
    for (uint64_t i=0; i<data_size; ++i) {
        if (valves[i].rate > 0) {
            list_i64_push_back(unopened_valve_ids, valves[i].id);
        }
    }
    
    
    // part 1
    list_tuple_i64* route = list_tuple_i64_init(32);
    list_tuple_i64_push_back(route, start_valve_id, 0);  // start at AA with cost 0
    dfs(data_size, valves, route, unopened_valve_ids, movement_costs, part1);
    list_tuple_i64_free(route);
    
    #ifndef DISABLE_2022_16_P2
    // part 2
    list_tuple_i64* route1 = list_tuple_i64_init(32);
    list_tuple_i64* route2 = list_tuple_i64_init(32);
    list_tuple_i64_push_back(route1, start_valve_id, 0);  // start at AA with cost 0
    list_tuple_i64_push_back(route2, start_valve_id, 0);  // start at AA with cost 0
    dfs2(data_size, valves, route1, route2, unopened_valve_ids, movement_costs, part2);
    list_tuple_i64_free(route1);
    list_tuple_i64_free(route2);
    #endif
    
    for (uint64_t i=0; i<data_size; ++i) {
        list_tuple_i64_free(valves[i].connections_by_name);
        valves[i].connections_by_name = NULL;
    }
    list_i64_free(unopened_valve_ids);
    free(movement_costs);
    free(valves);
}
