#include "day18_impl.h"


static const int64_t dirs[6][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {-1, 0, 0},
    {0, -1, 0},
    {0, 0, -1},
};


struct sizes {
    int64_t max_x;
    int64_t min_x;
    int64_t max_y;
    int64_t min_y;
    int64_t max_z;
    int64_t min_z;
};


// Depth-first search to any point outside the bounding box of all cubes.
static int64_t has_path_to_outside(int64_t x, int64_t y, int64_t z, set_tuple3_i64* cubes, struct sizes sizes, set_tuple3_i64* have_paths_cache, set_tuple3_i64* no_paths_cache) {
    int64_t has_path = 0, nx, ny, nz, tx, ty, tz;
    
    if (set_tuple3_i64_contains(no_paths_cache, x, y, z)) {
        return 0;
    }
    
    if (set_tuple3_i64_contains(have_paths_cache, x, y, z)) {
        return 1;
    }
    
    set_tuple3_i64* visited = set_tuple3_i64_init(2048);
    list_tuple3_i64* queue = list_tuple3_i64_init(2048);
    list_tuple3_i64_push_back(queue, x, y, z);
    
    while (list_tuple3_i64_size(queue) > 0) {
        list_tuple3_i64_pop_back(queue, &nx, &ny, &nz);
        set_tuple3_i64_add(visited, nx, ny, nz);
        
        if (nx >= sizes.max_x || ny >= sizes.max_y || nz >= sizes.max_z 
            || nx <= sizes.min_x || ny <= sizes.min_y || nz <= sizes.min_z 
            || set_tuple3_i64_contains(have_paths_cache, nx, ny, nz)) {
            has_path = 1;
            break;
        }
        
        for (uint64_t dir=0; dir<6; ++dir) {
            tx = nx + dirs[dir][0];
            ty = ny + dirs[dir][1];
            tz = nz + dirs[dir][2];
            if (!set_tuple3_i64_contains(cubes, tx, ty, tz) && !set_tuple3_i64_contains(visited, tx, ty, tz)) {
                list_tuple3_i64_push_back(queue, tx, ty, tz);
            }
        }
    }
    
    set_tuple3_i64_iterator* iter = set_tuple3_i64_iter(visited);
    if (has_path) {
        while (set_tuple3_i64_next(iter, &nx, &ny, &nz)) {
            set_tuple3_i64_add(have_paths_cache, nx, ny, nz);
        }
    } else {
        while (set_tuple3_i64_next(iter, &nx, &ny, &nz)) {
            set_tuple3_i64_add(no_paths_cache, nx, ny, nz);
        }
    }
    set_tuple3_i64_iter_free(iter);
    
    list_tuple3_i64_free(queue);
    set_tuple3_i64_free(visited);
    return has_path;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t x, y, z;
    set_tuple3_i64* cubes = set_tuple3_i64_init(4096);
    
    struct sizes sizes;
    sizes.max_x = INT64_MIN;
    sizes.max_y = INT64_MIN;
    sizes.max_z = INT64_MIN;
    sizes.min_x = INT64_MAX;
    sizes.min_y = INT64_MAX;
    sizes.min_z = INT64_MAX;
    
    for (uint64_t i=0; i<data_size; ++i) {
        sscanf(data[i], "%"SCNd64",%"SCNd64",%"SCNd64, &x, &y, &z);        
        set_tuple3_i64_add(cubes, x, y, z);
        
        sizes.max_x = max(sizes.max_x, x);
        sizes.min_x = min(sizes.min_x, x);
        
        sizes.max_y = max(sizes.max_y, y);
        sizes.min_y = min(sizes.min_y, y);
        
        sizes.max_z = max(sizes.max_z, z);
        sizes.min_z = min(sizes.min_z, z);
    }
    
    
    set_tuple3_i64* have_paths_cache = set_tuple3_i64_init(2048);
    set_tuple3_i64* no_paths_cache = set_tuple3_i64_init(2048);
    
    set_tuple3_i64_iterator* iter = set_tuple3_i64_iter(cubes);
    while (set_tuple3_i64_next(iter, &x, &y, &z)) {
        for (uint64_t dir=0; dir<6; ++dir) {
            if (!set_tuple3_i64_contains(cubes, x + dirs[dir][0], y + dirs[dir][1], z + dirs[dir][2])) {
                (*part1)++;
                if (has_path_to_outside(x + dirs[dir][0], y + dirs[dir][1], z + dirs[dir][2], cubes, sizes, have_paths_cache, no_paths_cache)) {
                    (*part2)++;
                }
            }
        }
    }
    set_tuple3_i64_iter_free(iter);
    
    set_tuple3_i64_free(have_paths_cache);
    set_tuple3_i64_free(no_paths_cache);
    set_tuple3_i64_free(cubes);
}
