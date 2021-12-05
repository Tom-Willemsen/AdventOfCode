#include "day5_impl.h"

int main(int argc, char** argv) {
    FILE* fptr = open_arg_as_file_or_exit(argc, argv);
    uint64_t data_size;
    int64_t max_x = 0, max_y = 0;
    char** points_s = load_file_as_str_arr(fptr, &data_size);
    fclose(fptr);
    
    int64_t** points = parse_points(points_s, data_size);
    free_str_arr(points_s, data_size);
    
    for (uint64_t i=0; i<data_size; ++i) {
        max_x = max(max_x, points[i][0]+1);
        max_y = max(max_y, points[i][1]+1);
        max_x = max(max_x, points[i][2]+1);
        max_y = max(max_y, points[i][3]+1);
    }
    
    int64_t** array = calloc(max_y, sizeof(int64_t*));
    for (int64_t i=0; i<max_y; ++i) {
        array[i] = calloc(max_x, sizeof(int64_t));
    }
    
    mark_straight(array, points, data_size);
    int64_t part1 = count_gt_2(array, max_x, max_y);
    mark_diagonal(array, points, data_size);
    int64_t part2 = count_gt_2(array, max_x, max_y);
    
    for (int64_t i=0; i<max_y; ++i) {
        free(array[i]);
    }
    free(array);
    for (int64_t i=0; i<data_size; ++i) {
        free(points[i]);
    }
    free(points);
    
    printf("Part 1: %"PRId64"\n", part1);
    printf("Part 2: %"PRId64"\n", part2);
    
    return EXIT_SUCCESS;
}
