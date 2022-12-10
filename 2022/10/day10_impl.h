#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_loading.h"
#include "set_tuple2.h"
#include "util.h"
#include "bitset.h"

static const int HEIGHT = 6;
static const int WIDTH = 40;
static const int SPRITE_WIDTH = 3;

void calculate(char** data, uint64_t data_size, int64_t* part1, char* part2);
