#pragma once
#include "tablebase24.h"
#include "tablebase32.h"

static size_t tablebase24_index(struct robot_costs* costs) {
    size_t result = (costs->orerobot_orecost - tablebase24_orerobot_orecost_min)
        * (tablebase24_clayrobot_orecost_max - tablebase24_clayrobot_orecost_min + 1)
        * (tablebase24_obsidianrobot_orecost_max - tablebase24_obsidianrobot_orecost_min + 1)
        * (tablebase24_obsidianrobot_claycost_max - tablebase24_obsidianrobot_claycost_min + 1)
        * (tablebase24_geoderobot_orecost_max - tablebase24_geoderobot_orecost_min + 1)
        * (tablebase24_geoderobot_obsidiancost_max - tablebase24_geoderobot_obsidiancost_min + 1);
        
    result += (costs->clayrobot_orecost - tablebase24_clayrobot_orecost_min)
        * (tablebase24_obsidianrobot_orecost_max - tablebase24_obsidianrobot_orecost_min + 1)
        * (tablebase24_obsidianrobot_claycost_max - tablebase24_obsidianrobot_claycost_min + 1)
        * (tablebase24_geoderobot_orecost_max - tablebase24_geoderobot_orecost_min + 1)
        * (tablebase24_geoderobot_obsidiancost_max - tablebase24_geoderobot_obsidiancost_min + 1);
        
    result += (costs->obsidianrobot_orecost - tablebase24_obsidianrobot_orecost_min)
        * (tablebase24_obsidianrobot_claycost_max - tablebase24_obsidianrobot_claycost_min + 1)
        * (tablebase24_geoderobot_orecost_max - tablebase24_geoderobot_orecost_min + 1)
        * (tablebase24_geoderobot_obsidiancost_max - tablebase24_geoderobot_obsidiancost_min + 1);
        
    result += (costs->obsidianrobot_claycost - tablebase24_obsidianrobot_claycost_min)
        * (tablebase24_geoderobot_orecost_max - tablebase24_geoderobot_orecost_min + 1)
        * (tablebase24_geoderobot_obsidiancost_max - tablebase24_geoderobot_obsidiancost_min + 1);
        
    result += (costs->geoderobot_orecost - tablebase24_geoderobot_orecost_min)
        * (tablebase24_geoderobot_obsidiancost_max - tablebase24_geoderobot_obsidiancost_min + 1);
        
    result += (costs->geoderobot_obsidiancost - tablebase24_geoderobot_obsidiancost_min);
    
    return result;
} 

static int64_t tablebase24_in_range(struct robot_costs* costs) {
    return costs->orerobot_orecost >= tablebase24_orerobot_orecost_min 
        && costs->orerobot_orecost <= tablebase24_orerobot_orecost_max
        && costs->clayrobot_orecost >= tablebase24_clayrobot_orecost_min
        && costs->clayrobot_orecost <= tablebase24_clayrobot_orecost_max
        && costs->obsidianrobot_orecost >= tablebase24_obsidianrobot_orecost_min
        && costs->obsidianrobot_orecost <= tablebase24_obsidianrobot_orecost_max
        && costs->geoderobot_orecost >= tablebase24_geoderobot_orecost_min
        && costs->geoderobot_orecost <= tablebase24_geoderobot_orecost_max
        && costs->obsidianrobot_claycost >= tablebase24_obsidianrobot_claycost_min
        && costs->obsidianrobot_claycost <= tablebase24_obsidianrobot_claycost_max
        && costs->geoderobot_obsidiancost >= tablebase24_geoderobot_obsidiancost_min
        && costs->geoderobot_obsidiancost <= tablebase24_geoderobot_obsidiancost_max;
}

static size_t tablebase32_index(struct robot_costs* costs) {
    size_t result = (costs->orerobot_orecost - tablebase32_orerobot_orecost_min)
        * (tablebase32_clayrobot_orecost_max - tablebase32_clayrobot_orecost_min + 1)
        * (tablebase32_obsidianrobot_orecost_max - tablebase32_obsidianrobot_orecost_min + 1)
        * (tablebase32_obsidianrobot_claycost_max - tablebase32_obsidianrobot_claycost_min + 1)
        * (tablebase32_geoderobot_orecost_max - tablebase32_geoderobot_orecost_min + 1)
        * (tablebase32_geoderobot_obsidiancost_max - tablebase32_geoderobot_obsidiancost_min + 1);
        
    result += (costs->clayrobot_orecost - tablebase32_clayrobot_orecost_min)
        * (tablebase32_obsidianrobot_orecost_max - tablebase32_obsidianrobot_orecost_min + 1)
        * (tablebase32_obsidianrobot_claycost_max - tablebase32_obsidianrobot_claycost_min + 1)
        * (tablebase32_geoderobot_orecost_max - tablebase32_geoderobot_orecost_min + 1)
        * (tablebase32_geoderobot_obsidiancost_max - tablebase32_geoderobot_obsidiancost_min + 1);
        
    result += (costs->obsidianrobot_orecost - tablebase32_obsidianrobot_orecost_min)
        * (tablebase32_obsidianrobot_claycost_max - tablebase32_obsidianrobot_claycost_min + 1)
        * (tablebase32_geoderobot_orecost_max - tablebase32_geoderobot_orecost_min + 1)
        * (tablebase32_geoderobot_obsidiancost_max - tablebase32_geoderobot_obsidiancost_min + 1);
        
    result += (costs->obsidianrobot_claycost - tablebase32_obsidianrobot_claycost_min)
        * (tablebase32_geoderobot_orecost_max - tablebase32_geoderobot_orecost_min + 1)
        * (tablebase32_geoderobot_obsidiancost_max - tablebase32_geoderobot_obsidiancost_min + 1);
        
    result += (costs->geoderobot_orecost - tablebase32_geoderobot_orecost_min)
        * (tablebase32_geoderobot_obsidiancost_max - tablebase32_geoderobot_obsidiancost_min + 1);
        
    result += (costs->geoderobot_obsidiancost - tablebase32_geoderobot_obsidiancost_min);
    
    return result;
} 

static int64_t tablebase32_in_range(struct robot_costs* costs) {
    return costs->orerobot_orecost >= tablebase32_orerobot_orecost_min 
        && costs->orerobot_orecost <= tablebase32_orerobot_orecost_max
        && costs->clayrobot_orecost >= tablebase32_clayrobot_orecost_min
        && costs->clayrobot_orecost <= tablebase32_clayrobot_orecost_max
        && costs->obsidianrobot_orecost >= tablebase32_obsidianrobot_orecost_min
        && costs->obsidianrobot_orecost <= tablebase32_obsidianrobot_orecost_max
        && costs->geoderobot_orecost >= tablebase32_geoderobot_orecost_min
        && costs->geoderobot_orecost <= tablebase32_geoderobot_orecost_max
        && costs->obsidianrobot_claycost >= tablebase32_obsidianrobot_claycost_min
        && costs->obsidianrobot_claycost <= tablebase32_obsidianrobot_claycost_max
        && costs->geoderobot_obsidiancost >= tablebase32_geoderobot_obsidiancost_min
        && costs->geoderobot_obsidiancost <= tablebase32_geoderobot_obsidiancost_max;
}
