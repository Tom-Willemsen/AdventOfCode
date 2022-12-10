#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_loading.h"
#include "util.h"

static const size_t HEIGHT = 6;
static const size_t WIDTH = 40;
static const size_t SPRITE_WIDTH = 3;

void calculate(char** data, uint64_t data_size, int64_t* part1, char* part2);
