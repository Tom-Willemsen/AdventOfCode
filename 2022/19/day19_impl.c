#include "day19_impl.h"


struct robot_costs {
    int64_t orerobot_orecost;
    int64_t clayrobot_orecost;
    int64_t obsidianrobot_orecost;
    int64_t obsidianrobot_claycost;
    int64_t geoderobot_orecost;
    int64_t geoderobot_obsidiancost;
};

struct resource_counts {
    int64_t ore;
    int64_t clay;
    int64_t obsidian;
    int64_t geodes;
};


static inline int64_t geo_sum_1_to(int64_t n) {
    return (n * (n+1))/2;
}


static void dfs(int64_t max_mins, int64_t mins, struct resource_counts* resources, struct resource_counts* robots, struct robot_costs* robot_costs, int64_t* best_score) {
    if (max_mins == mins) {
        *best_score = max(*best_score, resources->geodes);
        return;
    }
    
    int64_t remaining_mins = max_mins - mins;
    
    int64_t ideal_remaining_ore = resources->ore 
        + robots->ore * remaining_mins 
        + geo_sum_1_to(max(remaining_mins-1, 0));  // We know there's no point building ore robots on last turn
    
    int64_t ideal_remaining_clay = resources->clay 
        + robots->clay * remaining_mins 
        + geo_sum_1_to(min(max(remaining_mins-1, 0), ideal_remaining_ore / robot_costs->clayrobot_orecost));
    
    int64_t ideal_remaining_obsidian = resources->obsidian 
        + robots->obsidian * remaining_mins 
        + geo_sum_1_to(min(max(remaining_mins-1, 0), min(ideal_remaining_clay / robot_costs->obsidianrobot_claycost, ideal_remaining_ore / robot_costs->obsidianrobot_orecost)));
    
    int64_t ideal_remaining_geodes = resources->geodes 
        + robots->geodes * remaining_mins 
        + geo_sum_1_to(min(remaining_mins, min(ideal_remaining_obsidian / robot_costs->geoderobot_obsidiancost, ideal_remaining_ore / robot_costs->geoderobot_orecost)));
    
    if (*best_score >= ideal_remaining_geodes) {
        return;
    }
    
    uint8_t can_build_geode_robot = resources->ore >= robot_costs->geoderobot_orecost 
        && resources->obsidian >= robot_costs->geoderobot_obsidiancost;
    
    uint8_t can_build_obsidian_robot = resources->ore >= robot_costs->obsidianrobot_orecost
        && resources->clay >= robot_costs->obsidianrobot_claycost
        && mins < max_mins - 1
        && robots->obsidian < robot_costs->geoderobot_obsidiancost;
        
    uint8_t can_build_clay_robot = resources->ore >= robot_costs->clayrobot_orecost 
        && mins < max_mins - 1
        && robots->clay < robot_costs->obsidianrobot_claycost;
    
    uint8_t can_build_ore_robot = resources->ore >= robot_costs->orerobot_orecost 
        && mins < max_mins - 1
        && robots->ore < max(max(robot_costs->orerobot_orecost, robot_costs->clayrobot_orecost), 
                             max(robot_costs->obsidianrobot_orecost, robot_costs->geoderobot_orecost));
    
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
        
        dfs(24, 0, &resources, &robots, &robot_costs, &quality);
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
}
