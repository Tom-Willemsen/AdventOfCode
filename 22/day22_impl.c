#include "day22_impl.h"

static int64_t** parse_data(char** data, uint64_t data_size) {
    int64_t** result = calloc(data_size, sizeof(int64_t*));
    
    for (uint64_t i=0; i<data_size; ++i) {
        char action[10];
        result[i] = calloc(7, sizeof(int64_t));
        sscanf(data[i], "%9s x=%"SCNd64"..%"SCNd64",y=%"SCNd64"..%"SCNd64",z=%"SCNd64"..%"SCNd64, action,
                   &result[i][0], &result[i][1], &result[i][2], &result[i][3], &result[i][4], &result[i][5]);
        
        result[i][6] = (action[1] == 'f' ? 0 : 1);
    }
    return result;
}

struct cuboid {
  int64_t x1;  
  int64_t x2;  
  int64_t y1;  
  int64_t y2;  
  int64_t z1;  
  int64_t z2;  
};

static struct cuboid* create_cuboid(int64_t x1, int64_t x2, int64_t y1, int64_t y2, int64_t z1, int64_t z2) {
    struct cuboid* c = calloc(1, sizeof(struct cuboid));
    c->x1 = x1;
    c->x2 = x2;
    c->y1 = y1;
    c->y2 = y2;
    c->z1 = z1;
    c->z2 = z2;
    return c;
}

static struct cuboid* intersection(struct cuboid* c1, struct cuboid* c2) {
    int64_t x1 = max(c1->x1, c2->x1);
    int64_t x2 = min(c1->x2, c2->x2);
    int64_t y1 = max(c1->y1, c2->y1);
    int64_t y2 = min(c1->y2, c2->y2);
    int64_t z1 = max(c1->z1, c2->z1);
    int64_t z2 = min(c1->z2, c2->z2);
    if (x1 <= x2 && y1 <= y2 && z1 <= z2) {
        return create_cuboid(x1, x2, y1, y2, z1, z2);
    } else {
        return NULL;
    }
}

static inline int64_t is_big_cuboid(int64_t x1, int64_t x2, int64_t y1, int64_t y2, int64_t z1, int64_t z2) {
    return min(x1, x2) < -50 || max(x1, x2) > 50 || min(y1, y2) < -50 || max(y1, y2) > 50 || min(z1, z2) < -50 || max(z1, z2) > 50;
}

static int64_t solve(int64_t** cubes, uint64_t size, int64_t ignore_big_cubes) {
    list_tuple_i64* cuboid_states = list_tuple_i64_init(1);
    int64_t result = 0, k, v;

    for (uint64_t i=0; i<size; ++i) {
        int64_t* cube = cubes[i];
        int64_t action = cube[6];
        
        if (ignore_big_cubes && is_big_cuboid(cube[0], cube[1], cube[2], cube[3], cube[4], cube[5])) {
            continue;
        }
        
        struct cuboid* cuboid = create_cuboid(cube[0], cube[1], cube[2], cube[3], cube[4], cube[5]);
        
        uint64_t s = list_tuple_i64_size(cuboid_states);
        for (uint64_t j=0; j<s; ++j) {
            list_tuple_i64_get(cuboid_states, j, &k, &v);
            struct cuboid* intersect = intersection((struct cuboid*) k, cuboid);

            if (intersect != NULL) {
                list_tuple_i64_push_back(cuboid_states, (int64_t) intersect, -v);
            }
        }
                
        if (action) {
            list_tuple_i64_push_back(cuboid_states, (int64_t) cuboid, 1);
        } else {
            free(cuboid);
        }
    }
    
    for (uint64_t j=0; j<list_tuple_i64_size(cuboid_states); ++j) {
        list_tuple_i64_get(cuboid_states, j, &k, &v);
        struct cuboid* cuboid = (struct cuboid*) k;
        result += (cuboid->x2 - cuboid->x1 + 1) * (cuboid->y2 - cuboid->y1 + 1) * (cuboid->z2 - cuboid->z1 + 1) * v;
        free(cuboid);
    }
    list_tuple_i64_free(cuboid_states);
    
    return result;
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t** cubes = parse_data(data, data_size);
    
    *part1 = solve(cubes, data_size, 1);
    *part2 = solve(cubes, data_size, 0);
    
    for (uint64_t i=0; i<data_size; ++i) {
        free(cubes[i]);
    }
    free(cubes);
}
