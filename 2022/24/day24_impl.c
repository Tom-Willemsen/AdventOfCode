#include "day24_impl.h"


static const int64_t MAX_PATH_DEPTH = 500;


struct blizzards {
    set_tuple_i64* up;
    set_tuple_i64* down;
    set_tuple_i64* left;
    set_tuple_i64* right;
    int64_t x_size;
    int64_t y_size;
};


static int64_t can_move_to(int64_t x, int64_t y, int64_t round, struct blizzards* blizzards, int64_t target_x, int64_t target_y) {
    
    if ((x==1 && y == 0) || (x==target_x && y == target_y) || (x==blizzards->x_size && y == blizzards->y_size + 1)) {
        return 1;
    }
    
    if (x <= 0 || x > blizzards->x_size || y <= 0 || y > blizzards->y_size) {
        return 0;
    }
    
    if (set_tuple_i64_contains(blizzards->up, x, 1 + i64modulo_positive(y + round - 1, blizzards->y_size))) {
        return 0;
    }
    
    if (set_tuple_i64_contains(blizzards->down, x, 1 + i64modulo_positive(y - round - 1, blizzards->y_size))) {
        return 0;
    }
    
    if (set_tuple_i64_contains(blizzards->left, 1 + i64modulo_positive(x + round - 1, blizzards->x_size), y)) {
        return 0;
    }
    
    if (set_tuple_i64_contains(blizzards->right, 1 + i64modulo_positive(x - round - 1, blizzards->x_size), y)) {
        return 0;
    }
    return 1;
}


static void dfs(struct blizzards* blizzards, int64_t start_round, int64_t initial_x, int64_t initial_y, int64_t target_x, int64_t target_y, int64_t* best_distance) {
    int64_t qx, qy, qd;
    
    list_tuple3_i64* queue = list_tuple3_i64_init(1024);
    set_tuple3_i64* visited = set_tuple3_i64_init(4096);
    
    list_tuple3_i64_push_back(queue, initial_x, initial_y, 0);
    
    while(list_tuple3_i64_size(queue) > 0) {
        list_tuple3_i64_pop_back(queue, &qx, &qy, &qd);
        
        if (!set_tuple3_i64_add(visited, qx, qy, qd)) {
            continue;
        }
        
        if (qx == target_x && qy == target_y) {
            *best_distance = min(*best_distance, qd - 1);
            continue;
        }
        
        if (qd + i64abs(target_x - qx) + i64abs(target_y - qy) >= *best_distance) {
            continue;
        }
        
        if (can_move_to(qx, qy-1, start_round + qd, blizzards, target_x, target_y)) {
            list_tuple3_i64_push_back(queue, qx, qy-1, qd+1);
        }
        if (can_move_to(qx-1, qy, start_round + qd, blizzards, target_x, target_y)) {
            list_tuple3_i64_push_back(queue, qx-1, qy, qd+1);
        }
        if (can_move_to(qx, qy, start_round + qd, blizzards, target_x, target_y)) {
            list_tuple3_i64_push_back(queue, qx, qy, qd+1);
        }
        if (can_move_to(qx, qy+1, start_round + qd, blizzards, target_x, target_y)) {
            list_tuple3_i64_push_back(queue, qx, qy+1, qd+1);
        }
        if (can_move_to(qx+1, qy, start_round + qd, blizzards, target_x, target_y)) {
            list_tuple3_i64_push_back(queue, qx+1, qy, qd+1);
        }
    }
    
    list_tuple3_i64_free(queue);
    set_tuple3_i64_free(visited);
}


void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    
    struct blizzards blizzards;
    blizzards.up = set_tuple_i64_init(4096);
    blizzards.down = set_tuple_i64_init(4096);
    blizzards.left = set_tuple_i64_init(4096);
    blizzards.right = set_tuple_i64_init(4096);
    
    for(uint64_t y=0; y<data_size; ++y) {
        uint64_t linelength = strlen(data[y]);
        for (uint64_t x=0; x<linelength; ++x) {
            char c = data[y][x];
            if (c == 'v') {
                set_tuple_i64_add(blizzards.down, x, y);
            } else if (c == '^') {
                set_tuple_i64_add(blizzards.up, x, y);
            } else if (c == '<') {
                set_tuple_i64_add(blizzards.left, x, y);
            } else if (c == '>') {
                set_tuple_i64_add(blizzards.right, x, y);
            }
        }
    }
    
    blizzards.x_size = strlen(data[0]) - 3;
    blizzards.y_size = data_size - 2;
    
    int64_t path1 = MAX_PATH_DEPTH;
    int64_t path2 = MAX_PATH_DEPTH;
    int64_t path3 = MAX_PATH_DEPTH;
    
    int64_t target_x = strlen(data[0]) - 3;
    int64_t target_y = data_size - 1;
    
    dfs(&blizzards, 0, 1, 0, target_x, target_y, &path1);
    dfs(&blizzards, path1, target_x, target_y, 1, 0, &path2);
    dfs(&blizzards, path1 + path2, 1, 0, target_x, target_y, &path3);
    
    *part1 = path1;
    *part2 = path1 + path2 + path3;
    
    set_tuple_i64_free(blizzards.up);
    set_tuple_i64_free(blizzards.down);
    set_tuple_i64_free(blizzards.left);
    set_tuple_i64_free(blizzards.right);
}
