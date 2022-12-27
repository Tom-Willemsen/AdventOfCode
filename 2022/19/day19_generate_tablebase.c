#include "day19_impl.h"


static size_t tablebase_index(struct robot_costs* min_costs, struct robot_costs* max_costs, struct robot_costs* costs) {
    size_t result = (costs->orerobot_orecost - min_costs->orerobot_orecost)
        * (max_costs->clayrobot_orecost - min_costs->clayrobot_orecost + 1)
        * (max_costs->obsidianrobot_orecost - min_costs->obsidianrobot_orecost + 1)
        * (max_costs->obsidianrobot_claycost - min_costs->obsidianrobot_claycost + 1)
        * (max_costs->geoderobot_orecost - min_costs->geoderobot_orecost + 1)
        * (max_costs->geoderobot_obsidiancost - min_costs->geoderobot_obsidiancost + 1);
        
    result += (costs->clayrobot_orecost - min_costs->clayrobot_orecost)
        * (max_costs->obsidianrobot_orecost - min_costs->obsidianrobot_orecost + 1)
        * (max_costs->obsidianrobot_claycost - min_costs->obsidianrobot_claycost + 1)
        * (max_costs->geoderobot_orecost - min_costs->geoderobot_orecost + 1)
        * (max_costs->geoderobot_obsidiancost - min_costs->geoderobot_obsidiancost + 1);
        
    result += (costs->obsidianrobot_orecost - min_costs->obsidianrobot_orecost)
        * (max_costs->obsidianrobot_claycost - min_costs->obsidianrobot_claycost + 1)
        * (max_costs->geoderobot_orecost - min_costs->geoderobot_orecost + 1)
        * (max_costs->geoderobot_obsidiancost - min_costs->geoderobot_obsidiancost + 1);
        
    result += (costs->obsidianrobot_claycost - min_costs->obsidianrobot_claycost)
        * (max_costs->geoderobot_orecost - min_costs->geoderobot_orecost + 1)
        * (max_costs->geoderobot_obsidiancost - min_costs->geoderobot_obsidiancost + 1);
        
    result += (costs->geoderobot_orecost - min_costs->geoderobot_orecost)
        * (max_costs->geoderobot_obsidiancost - min_costs->geoderobot_obsidiancost + 1);
        
    result += (costs->geoderobot_obsidiancost - min_costs->geoderobot_obsidiancost);
    
    return result;
}


static void generate_tablebase(int64_t moves, struct robot_costs* min_costs, struct robot_costs* max_costs, FILE* file) {
    
    size_t tablebase_size = (max_costs->orerobot_orecost - min_costs->orerobot_orecost + 1)
        * (max_costs->clayrobot_orecost - min_costs->clayrobot_orecost + 1)
        * (max_costs->obsidianrobot_orecost - min_costs->obsidianrobot_orecost + 1)
        * (max_costs->obsidianrobot_claycost - min_costs->obsidianrobot_claycost + 1)
        * (max_costs->geoderobot_orecost - min_costs->geoderobot_orecost + 1)
        * (max_costs->geoderobot_obsidiancost - min_costs->geoderobot_obsidiancost + 1);
        
    int64_t* tablebase = calloc(tablebase_size, sizeof(int64_t));
    
    // This is one alloc we should *probably* actually check for success...
    if (!tablebase) {
        printf("failed tablebase alloc\n");
        abort();
    }
    
    uint64_t done = 0;
    
    // :)
    #pragma omp parallel for collapse(6) schedule(dynamic) num_threads(14)
    for (int64_t orerobot_orecost=min_costs->orerobot_orecost; orerobot_orecost<=max_costs->orerobot_orecost; ++orerobot_orecost) {
        
        for (int64_t clayrobot_orecost=min_costs->clayrobot_orecost; clayrobot_orecost<=max_costs->clayrobot_orecost; ++clayrobot_orecost) {
            
            for (int64_t obsidianrobot_orecost=min_costs->obsidianrobot_orecost; obsidianrobot_orecost<=max_costs->obsidianrobot_orecost; ++obsidianrobot_orecost) {
                
                for (int64_t obsidianrobot_claycost=min_costs->obsidianrobot_claycost; obsidianrobot_claycost<=max_costs->obsidianrobot_claycost; ++obsidianrobot_claycost) {
                    
                    for (int64_t geoderobot_orecost=min_costs->geoderobot_orecost; geoderobot_orecost<=max_costs->geoderobot_orecost; ++geoderobot_orecost) {
                        
                        for (int64_t geoderobot_obsidiancost=min_costs->geoderobot_obsidiancost; geoderobot_obsidiancost<=max_costs->geoderobot_obsidiancost; ++geoderobot_obsidiancost) {
                            
                            int64_t quality = 0;
                            struct resource_counts resources;
                            struct resource_counts robots;
                            struct robot_costs costs;
                            
                            costs.orerobot_orecost = orerobot_orecost;
                            costs.clayrobot_orecost = clayrobot_orecost;
                            costs.obsidianrobot_orecost = obsidianrobot_orecost;
                            costs.obsidianrobot_claycost = obsidianrobot_claycost;
                            costs.geoderobot_orecost = geoderobot_orecost;
                            costs.geoderobot_obsidiancost = geoderobot_obsidiancost;
                            
                            resources.ore = 0;
                            resources.clay = 0;
                            resources.obsidian = 0;
                            resources.geodes = 0;
                            
                            robots.ore = 1;
                            robots.clay = 0;
                            robots.obsidian = 0;
                            robots.geodes = 0;
                            
                            dfs(moves, 0, &resources, &robots, &costs, &quality);
                            
                            #pragma omp critical
                            {
                                tablebase[tablebase_index(min_costs, max_costs, &costs)] = quality;
                                done++;
                                if (done % 100 == 0) {
                                    printf("Done %lu of %lu\n", done, tablebase_size);
                                }
                            }
                        }
                        
                    }
                    
                }
                
            }
            
        }
    }
    
    fprintf(file, "#pragma once\n");
    fprintf(file, "\n");
    fprintf(file, "static const uint64_t tablebase%lu_size = %lu;\n", moves, tablebase_size);
    fprintf(file, "\n");
    
    fprintf(file, "static const uint64_t tablebase%lu_orerobot_orecost_min = %lu;\n", moves, min_costs->orerobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_clayrobot_orecost_min = %lu;\n", moves, min_costs->clayrobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_obsidianrobot_orecost_min = %lu;\n", moves, min_costs->obsidianrobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_obsidianrobot_claycost_min = %lu;\n", moves, min_costs->obsidianrobot_claycost);
    fprintf(file, "static const uint64_t tablebase%lu_geoderobot_orecost_min = %lu;\n", moves, min_costs->geoderobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_geoderobot_obsidiancost_min = %lu;\n", moves, min_costs->geoderobot_obsidiancost);
    fprintf(file, "\n");
    
    fprintf(file, "static const uint64_t tablebase%lu_orerobot_orecost_max = %lu;\n", moves, max_costs->orerobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_clayrobot_orecost_max = %lu;\n", moves, max_costs->clayrobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_obsidianrobot_orecost_max = %lu;\n", moves, max_costs->obsidianrobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_obsidianrobot_claycost_max = %lu;\n", moves, max_costs->obsidianrobot_claycost);
    fprintf(file, "static const uint64_t tablebase%lu_geoderobot_orecost_max = %lu;\n", moves, max_costs->geoderobot_orecost);
    fprintf(file, "static const uint64_t tablebase%lu_geoderobot_obsidiancost_max = %lu;\n", moves, max_costs->geoderobot_obsidiancost);
    fprintf(file, "\n");
    
    fprintf(file, "static const uint64_t tablebase%lu[%lu] = {\n", moves, tablebase_size);
    
    for (uint64_t i=0; i<tablebase_size; ++i) {
        fprintf(file, "    %ld,\n", tablebase[i]);
    }
    fprintf(file, "};\n");
    
}


int main(int argc, char** argv) {
    
    struct robot_costs min_costs;
    min_costs.orerobot_orecost = 2;
    min_costs.clayrobot_orecost = 2;
    min_costs.obsidianrobot_orecost=2;
    min_costs.obsidianrobot_claycost=5;
    min_costs.geoderobot_orecost=2;
    min_costs.geoderobot_obsidiancost=5;
    
    struct robot_costs max_costs;
    max_costs.orerobot_orecost = 4;
    max_costs.clayrobot_orecost = 4;
    max_costs.obsidianrobot_orecost=4;
    max_costs.obsidianrobot_claycost=20;
    max_costs.geoderobot_orecost=4;
    max_costs.geoderobot_obsidiancost=20;
    
    FILE* tablebase24 = fopen("tablebase24.h", "w");
    
    printf("Generating 24-move tablebase...\n");
    generate_tablebase(24, &min_costs, &max_costs, tablebase24);
    printf("... done\n");
    
    fclose(tablebase24);
    
    FILE* tablebase32 = fopen("tablebase32.h", "w");
    
    printf("Generating 32-move tablebase...\n");
    generate_tablebase(32, &min_costs, &max_costs, tablebase32);
    printf("... done\n");
    
    fclose(tablebase32);
    
    return EXIT_SUCCESS;
} 
