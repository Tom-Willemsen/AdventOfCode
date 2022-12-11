#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>
#include "file_loading.h"
#include "simd_util.h"
#include "util.h"

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2);
