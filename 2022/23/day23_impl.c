#include "day23_impl.h"


static const int64_t DIRS[8][2] = {
    {-1, -1},
    {0, -1},
    {1, -1},
    {-1, 0},
    {1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
};


static const int64_t MOVE_DIRS[4][6] = {
    // (x, y), (x, y), (x, y)
    {-1, -1, 0, -1, 1, -1},
    {-1, 1, 0, 1, 1, 1},
    {-1, 1, -1, 0, -1, -1},
    {1, 1, 1, 0, 1, -1},
};

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    
    set_tuple_i64* elves = set_tuple_i64_init(4096);
    list_tuple3_i64* movers = list_tuple3_i64_init(4096);
    list_tuple_i64* proposals = list_tuple_i64_init(4096);
    
    for (uint64_t y=0; y<data_size; ++y) {
        uint64_t x_max = strlen(data[y]) - 1;
        for (uint64_t x=0; x<x_max; ++x) {
            if (data[y][x] == '#') {
                set_tuple_i64_add(elves, x, y);
            }
        }
    }
    
    int64_t rounds = 0;
    
    while (1) {
        int64_t elf_x, elf_y, dir;
        
        list_tuple_i64_clear(proposals);
        list_tuple3_i64_clear(movers);
        
        set_tuple_i64_iterator* iter = set_tuple_i64_iter(elves);
        while (set_tuple_i64_next(iter, &elf_x, &elf_y)) {
            uint8_t needs_move = 0;
            
            for (size_t i=0; i<8; ++i) {
                int64_t new_x = elf_x + DIRS[i][0];
                int64_t new_y = elf_y + DIRS[i][1];
                if (set_tuple_i64_contains(elves, new_x, new_y)) {
                    needs_move = 1;
                    break;
                }
            }
            
            if (needs_move) {
                for (int64_t j=rounds; j<rounds+4; ++j) {
                    int64_t dir_index = i64modulo_positive(j, 4);
                    if (
                        !set_tuple_i64_contains(elves, elf_x + MOVE_DIRS[dir_index][0], elf_y + MOVE_DIRS[dir_index][1])
                        && !set_tuple_i64_contains(elves, elf_x + MOVE_DIRS[dir_index][2], elf_y + MOVE_DIRS[dir_index][3])
                        && !set_tuple_i64_contains(elves, elf_x + MOVE_DIRS[dir_index][4], elf_y + MOVE_DIRS[dir_index][5])
                    ) 
                    {
                        list_tuple_i64_push_back(proposals, elf_x + MOVE_DIRS[dir_index][2], elf_y + MOVE_DIRS[dir_index][3]);
                        list_tuple3_i64_push_back(movers, elf_x, elf_y, dir_index);
                        break;
                    }
                }
            }
        }
        set_tuple_i64_iter_free(iter);
        
        uint8_t any_moved = 0;
        
        for (uint64_t i=0; i<list_tuple3_i64_size(movers); ++i) {
            list_tuple3_i64_get(movers, i, &elf_x, &elf_y, &dir);
            
            int64_t new_x = elf_x + MOVE_DIRS[dir][2];
            int64_t new_y = elf_y + MOVE_DIRS[dir][3];
            
            if (list_tuple_i64_count(proposals, new_x, new_y) == 1) {
                set_tuple_i64_remove(elves, elf_x, elf_y);
                set_tuple_i64_add(elves, new_x, new_y);
                any_moved = 1;
            }
        }
        
        if (!any_moved) {
            break;
        }
        
        rounds++;
        
        printf("round %ld\n", rounds);
        
        if (rounds == 10) {
            int64_t min_x = INT64_MAX, min_y = INT64_MAX, max_x = INT64_MIN, max_y = INT64_MIN;
            iter = set_tuple_i64_iter(elves);
            while (set_tuple_i64_next(iter, &elf_x, &elf_y)) {
                min_x = min(min_x, elf_x);
                max_x = max(max_x, elf_x);
                min_y = min(min_y, elf_y);
                max_y = max(max_y, elf_y);
            }
            set_tuple_i64_iter_free(iter);
            *part1 = (max_x - min_x + 1) * (max_y - min_y + 1) - set_tuple_i64_size(elves);
        }
    }
    
    *part2 = rounds + 1;
    
    list_tuple_i64_free(proposals);
    list_tuple3_i64_free(movers);
    set_tuple_i64_free(elves);
}
