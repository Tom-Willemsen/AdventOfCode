#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_loading.h"
#include "list_tuple3.h"
#include "set_tuple3.h"


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

void dfs(int64_t max_mins, int64_t mins, struct resource_counts* resources, struct resource_counts* robots, struct robot_costs* robot_costs, int64_t* best_score);

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2);
