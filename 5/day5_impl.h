#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "file_loading.h"
#include "util.h"

int64_t** parse_points(char** strings, uint64_t data_size);
int64_t count_gt_2(int64_t** array, int64_t max_x, int64_t max_y);
void mark_straight(int64_t** array, int64_t** points, uint64_t data_size);
void mark_diagonal(int64_t** array, int64_t** points, uint64_t data_size);
