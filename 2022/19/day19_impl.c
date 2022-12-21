#include "day19_impl.h"


static inline int64_t range_in_tablebase(FILE* tablebase, struct robot_costs* costs) {
    rewind(tablebase);
    
    size_t tb_size;
    int64_t sizes[12];
    
    fread(&tb_size, sizeof(size_t), 1, tablebase);
    fread(sizes, sizeof(int64_t), 12, tablebase);
    
    if (costs->orerobot_orecost >= sizes[0] && costs->orerobot_orecost <= sizes[6]
        && costs->clayrobot_orecost >= sizes[1] && costs->clayrobot_orecost <= sizes[7]
        && costs->obsidianrobot_orecost >= sizes[2] && costs->obsidianrobot_orecost <= sizes[8]
        && costs->obsidianrobot_claycost >= sizes[3] && costs->obsidianrobot_claycost <= sizes[9]
        && costs->geoderobot_orecost >= sizes[4] && costs->geoderobot_orecost <= sizes[10]
        && costs->geoderobot_orecost >= sizes[5] && costs->geoderobot_orecost <= sizes[11]
    ) {
        return 1;
    }
    return 0;
}

static inline int64_t tablebase_get(FILE* tablebase, struct robot_costs* costs) {
    rewind(tablebase);
    
    size_t tb_size;
    int64_t sizes[12];
    
    fread(&tb_size, sizeof(size_t), 1, tablebase);
    fread(sizes, sizeof(int64_t), 12, tablebase);
    
    int64_t* tablebase_data = calloc(tb_size, sizeof(int64_t));
    
    fread(tablebase_data, sizeof(int64_t), tb_size, tablebase);
    
    size_t index = (costs->orerobot_orecost - sizes[0])
        * (sizes[6] - sizes[1] + 1)
        * (sizes[7] - sizes[2] + 1)
        * (sizes[8] - sizes[3] + 1)
        * (sizes[9] - sizes[4] + 1)
        * (sizes[10] - sizes[5] + 1);
        
    index += (costs->clayrobot_orecost - sizes[1])
        * (sizes[7] - sizes[2] + 1)
        * (sizes[8] - sizes[3] + 1)
        * (sizes[9] - sizes[4] + 1)
        * (sizes[10] - sizes[5] + 1);
        
    index += (costs->obsidianrobot_orecost - sizes[2])
        * (sizes[8] - sizes[3] + 1)
        * (sizes[9] - sizes[4] + 1)
        * (sizes[10] - sizes[5] + 1);
        
    index += (costs->obsidianrobot_claycost - sizes[3])
        * (sizes[9] - sizes[4] + 1)
        * (sizes[10] - sizes[5] + 1);
        
    index += (costs->geoderobot_orecost - sizes[4])
        * (sizes[10] - sizes[5] + 1);
        
    index += (costs->geoderobot_obsidiancost - sizes[5]);
    
    int64_t result = tablebase_data[index];
    free(tablebase_data);
    return result;
}


static inline int64_t geo_sum_1_to(int64_t n) {
    return (n * (n+1))/2;
}


void dfs(int64_t max_mins, int64_t mins, struct resource_counts* resources, struct resource_counts* robots, struct robot_costs* robot_costs, int64_t* best_score) {
    if (mins == max_mins - 1) {
        *best_score = max(*best_score, resources->geodes + robots->geodes);
        return;
    }
    
    int64_t remaining_mins = max_mins - mins;
    
    int64_t ideal_remaining_ore = resources->ore 
        + robots->ore * remaining_mins 
        + geo_sum_1_to(max(remaining_mins-1, 0));  // We know there's no point building ore robots on last turn
    
    int64_t ideal_remaining_clay = resources->clay 
        + robots->clay * remaining_mins 
        + geo_sum_1_to(min(max(remaining_mins-2, 0), ideal_remaining_ore / robot_costs->clayrobot_orecost));  // For clay robots, no point building after *second* last turn.
    
    int64_t ideal_remaining_obsidian = resources->obsidian 
        + robots->obsidian * remaining_mins 
        + geo_sum_1_to(min(max(remaining_mins-1, 0), min(ideal_remaining_clay / robot_costs->obsidianrobot_claycost, ideal_remaining_ore / robot_costs->obsidianrobot_orecost)));
    
    int64_t ideal_remaining_geodes = resources->geodes 
        + robots->geodes * remaining_mins 
        + geo_sum_1_to(min(remaining_mins, min(ideal_remaining_obsidian / robot_costs->geoderobot_obsidiancost, ideal_remaining_ore / robot_costs->geoderobot_orecost)));
    
    if (*best_score >= ideal_remaining_geodes) {
        return;
    }
    
    int64_t max_ore_cost_any_robot = max(max(robot_costs->orerobot_orecost, robot_costs->clayrobot_orecost), 
                             max(robot_costs->obsidianrobot_orecost, robot_costs->geoderobot_orecost));
    
    uint8_t can_build_geode_robot = resources->ore >= robot_costs->geoderobot_orecost 
        && resources->obsidian >= robot_costs->geoderobot_obsidiancost;
    
    uint8_t can_build_obsidian_robot = resources->ore >= robot_costs->obsidianrobot_orecost
        && resources->clay >= robot_costs->obsidianrobot_claycost
        && mins < max_mins - 2  // obs can only be useful if we have at least one more turn afterwards to use it to form a geode robot.
        && robots->obsidian < robot_costs->geoderobot_obsidiancost
        && resources->obsidian + (robots->obsidian - robot_costs->geoderobot_obsidiancost) * remaining_mins < 0;
        
    uint8_t can_build_clay_robot = resources->ore >= robot_costs->clayrobot_orecost 
        && mins < max_mins - 3  // clay can only be useful if we have at least *two* more turns afterwards to use it to form obs robot -> geode robot.
        && robots->clay < robot_costs->obsidianrobot_claycost
        && resources->clay + (robots->clay - robot_costs->obsidianrobot_claycost) * remaining_mins < 0;
    
    uint8_t can_build_ore_robot = resources->ore >= robot_costs->orerobot_orecost 
        && mins < max_mins - 2  // ore can only be useful if we have at least one more turn afterwards to use it to form a geode robot.
        && robots->ore < max_ore_cost_any_robot
        && resources->ore + (robots->ore - max_ore_cost_any_robot) * remaining_mins < 0;
    
    resources->ore += robots->ore;
    resources->clay += robots->clay;
    resources->obsidian += robots->obsidian;
    resources->geodes += robots->geodes;
    
    if (can_build_geode_robot) {
        robots->geodes++;
        resources->ore -= robot_costs->geoderobot_orecost;
        resources->obsidian -= robot_costs->geoderobot_obsidiancost;
        dfs(max_mins, mins+1, resources, robots, robot_costs, best_score);
        robots->geodes--;
        resources->ore += robot_costs->geoderobot_orecost;
        resources->obsidian += robot_costs->geoderobot_obsidiancost;
    } else {
        if (can_build_obsidian_robot) {
            robots->obsidian++;
            resources->ore -= robot_costs->obsidianrobot_orecost;
            resources->clay -= robot_costs->obsidianrobot_claycost;
            dfs(max_mins, mins+1, resources, robots, robot_costs, best_score);
            robots->obsidian--;
            resources->ore += robot_costs->obsidianrobot_orecost;
            resources->clay += robot_costs->obsidianrobot_claycost;
        }
        
        if (can_build_clay_robot) {
            robots->clay++;
            resources->ore -= robot_costs->clayrobot_orecost;
            dfs(max_mins, mins+1, resources, robots, robot_costs, best_score);
            robots->clay--;
            resources->ore += robot_costs->clayrobot_orecost;
        }
        
        if (can_build_ore_robot) {
            robots->ore++;
            resources->ore -= robot_costs->orerobot_orecost;
            dfs(max_mins, mins+1, resources, robots, robot_costs, best_score);
            robots->ore--;
            resources->ore += robot_costs->orerobot_orecost;
        }
        
        dfs(max_mins, mins+1, resources, robots, robot_costs, best_score);
    }
    resources->ore -= robots->ore;
    resources->clay -= robots->clay;
    resources->obsidian -= robots->obsidian;
    resources->geodes -= robots->geodes;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {

    *part1 = 0;
    *part2 = 1;
    
    FILE* tablebase24 = fopen("tablebase24.bin", "r");
    FILE* tablebase32 = fopen("tablebase32.bin", "r");
    
    for (uint64_t i=0; i<data_size; ++i) {
        int64_t id;
        int64_t quality = 0;
        struct robot_costs robot_costs;
        struct resource_counts resources;
        struct resource_counts robots;
        sscanf(data[i], 
               "Blueprint %"SCNd64": "
               "Each ore robot costs %"SCNd64" ore. "
               "Each clay robot costs %"SCNd64" ore. "
               "Each obsidian robot costs %"SCNd64" ore and %"SCNd64" clay. "
               "Each geode robot costs %"SCNd64" ore and %"SCNd64" obsidian.", 
               &id, 
               &robot_costs.orerobot_orecost, 
               &robot_costs.clayrobot_orecost, 
               &robot_costs.obsidianrobot_orecost, 
               &robot_costs.obsidianrobot_claycost, 
               &robot_costs.geoderobot_orecost, 
               &robot_costs.geoderobot_obsidiancost 
        );
        
        resources.ore = 0;
        resources.clay = 0;
        resources.obsidian = 0;
        resources.geodes = 0;
        
        robots.ore = 1;
        robots.clay = 0;
        robots.obsidian = 0;
        robots.geodes = 0;
        
        if (tablebase24 != NULL) {
            if (range_in_tablebase(tablebase24, &robot_costs)) {
                quality = tablebase_get(tablebase24, &robot_costs);
            } else {
                printf("not using 24-move tablebase: not in tablebase range\n");
            }
        } else {
            printf("not using 24-move tablebase: doesn't exist\n");
            dfs(24, 0, &resources, &robots, &robot_costs, &quality);
        }
        
        *part1 += id * quality;
        
        if (id <= 3) {
            resources.ore = 0;
            resources.clay = 0;
            resources.obsidian = 0;
            resources.geodes = 0;
            
            robots.ore = 1;
            robots.clay = 0;
            robots.obsidian = 0;
            robots.geodes = 0;
            
            dfs(32, 0, &resources, &robots, &robot_costs, &quality);
            
            *part2 *= quality;
        }
    }
    
    if (tablebase24 != NULL) {
        fclose(tablebase24);
    }
    
    if (tablebase32 != NULL) {
        fclose(tablebase32);
    }
}
