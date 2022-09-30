#include "day20_impl.h"

static const uint64_t LOOKUP_SIZE = 512;

static uint8_t* parse_lookup(char* data) {
    assert(strlen(data) > LOOKUP_SIZE);
    uint8_t* lookup = calloc(LOOKUP_SIZE, sizeof(uint8_t));
    
    for (uint64_t i=0; i<LOOKUP_SIZE; ++i) {
        lookup[i] = data[i] == '#' ? 1 : 0;
    }
    
    return lookup;
}

static uint8_t** parse_grid(char** data, uint64_t data_size, uint64_t* n_rows, uint64_t* n_cols) {
    assert(data_size >= 3);
    *n_cols = strlen(data[2]) - 1;
    *n_rows = data_size - 2;
    uint8_t** grid = calloc((*n_rows), sizeof(uint8_t*));
    
    for (uint64_t r=0; r<(*n_rows); ++r) {
        grid[r] = calloc((*n_cols), sizeof(uint8_t));
        for (uint64_t c=0; c<(*n_cols); ++c) {
            grid[r][c] = data[r+2][c] == '#' ? 1 : 0;
        }
    }
    
    return grid;
}

static inline uint64_t get_or_default(uint8_t** grid, uint64_t n_rows, uint64_t n_cols, uint64_t row, uint64_t col, uint8_t def) {
    if (row < 0 || col < 0 || row >= n_rows || col >= n_cols) {
        return def;
    } else {
        return grid[row][col];
    }
}

static uint64_t map_pixel_to_lookup_id(uint8_t** grid, uint64_t n_rows, uint64_t n_cols, uint64_t row, uint64_t col, uint8_t def) {
    return (get_or_default(grid, n_rows, n_cols, row-1, col-1, def) << 8) + 
           (get_or_default(grid, n_rows, n_cols, row-1, col, def) << 7) + 
           (get_or_default(grid, n_rows, n_cols, row-1, col+1, def) << 6) + 
           (get_or_default(grid, n_rows, n_cols, row, col-1, def) << 5) + 
           (get_or_default(grid, n_rows, n_cols, row, col, def) << 4) + 
           (get_or_default(grid, n_rows, n_cols, row, col+1, def) << 3) + 
           (get_or_default(grid, n_rows, n_cols, row+1, col-1, def) << 2) + 
           (get_or_default(grid, n_rows, n_cols, row+1, col, def) << 1) + 
           (get_or_default(grid, n_rows, n_cols, row+1, col+1, def));
}

static int64_t count_after_n_iterations(uint8_t** grid, uint64_t n_rows, uint64_t n_cols, uint8_t* lookup, int64_t iterations) {
    uint8_t** nextgrid;
    uint8_t def = 0;
    uint64_t rows = n_rows, cols = n_cols, next_rows, next_cols;
    int64_t result = 0;
    uint64_t lookup_id;
    
    uint8_t** oldgrid = calloc(n_rows, sizeof(uint8_t*));
    for (uint64_t row=0; row<n_rows; ++row) {
        oldgrid[row] = calloc(n_cols, sizeof(uint8_t));
        memcpy(oldgrid[row], grid[row], n_cols*sizeof(uint8_t));
    }
    
    for (uint64_t i=0; i<iterations; ++i) {
        next_rows = rows + 2;
        next_cols = rows + 2;
        nextgrid = calloc(next_rows, sizeof(uint8_t*));
        for (uint64_t row=0; row<next_rows; ++row) {
            nextgrid[row] = calloc(next_cols, sizeof(uint8_t));
            for (uint64_t col=0; col<next_cols; ++col) {
                lookup_id = map_pixel_to_lookup_id(oldgrid, rows, cols, row-1, col-1, def);
                assert(lookup_id >= 0 && lookup_id < LOOKUP_SIZE);
                nextgrid[row][col] = lookup[lookup_id];
            }
        }
        
        def = lookup[def ? LOOKUP_SIZE-1 : 0];
        
        for (uint64_t row=0; row<rows; ++row) {
            free(oldgrid[row]);
        }
        free(oldgrid);
        
        oldgrid = nextgrid;
        rows = next_rows;
        cols = next_cols;
    }
    
    for (uint64_t row=0; row<rows; ++row) {
        for (uint64_t col=0; col<cols; ++col) {
            result += nextgrid[row][col];
        }
        free(nextgrid[row]);
    }
    free(nextgrid);
    assert(!def);
    return result;
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    uint64_t n_rows, n_cols;
    uint8_t* lookup = parse_lookup(data[0]);
    uint8_t** grid = parse_grid(data, data_size, &n_rows, &n_cols);
    
    *part1 = count_after_n_iterations(grid, n_rows, n_cols, lookup, 2);
    *part2 = count_after_n_iterations(grid, n_rows, n_cols, lookup, 50);
    
    for (uint64_t row=0; row<n_rows; ++row) {
        free(grid[row]);
    }
    free(grid);
    free(lookup);
}
