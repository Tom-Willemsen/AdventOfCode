#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "file_loading.h"
#include "list_tuple3.h"
#include "set_tuple3.h"
#include "util.h"

typedef struct Transform {
    int64_t axis_x;
    int64_t axis_y;
    int64_t axis_z;
    int64_t sign_x;
    int64_t sign_y;
    int64_t sign_z;
} Transform;

static const uint64_t NUM_ROTATION_TRANSFORMS = 24;
static const Transform ROTATION_TRANSFORMS[24] = {
    {0, 1, 2, 1, 1, 1},
    {1, 2, 0, 1, 1, 1},
    {2, 0, 1, 1, 1, 1},
    {0, 2, 1, 1, 1, -1},
    {1, 0, 2, 1, 1, -1},
    {2, 1, 0, 1, 1, -1},
    {0, 2, 1, 1, -1, 1},
    {1, 0, 2, 1, -1, 1},
    {2, 1, 0, 1, -1, 1},
    {0, 1, 2, 1, -1, -1},
    {1, 2, 0, 1, -1, -1},
    {2, 0, 1, 1, -1, -1},
    {0, 2, 1, -1, 1, 1},
    {1, 0, 2, -1, 1, 1},
    {2, 1, 0, -1, 1, 1},
    {0, 1, 2, -1, 1, -1},
    {1, 2, 0, -1, 1, -1},
    {2, 0, 1, -1, 1, -1},
    {0, 1, 2, -1, -1, 1},
    {1, 2, 0, -1, -1, 1},
    {2, 0, 1, -1, -1, 1},
    {0, 2, 1, -1, -1, -1},
    {1, 0, 2, -1, -1, -1},
    {2, 1, 0, -1, -1, -1},
};

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2);
