#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_loading.h"
#include "ocr.h"
#include "util.h"

#define HEIGHT 6
#define WIDTH 40
#define SPRITE_WIDTH 3

void calculate(char** data, uint64_t data_size, int64_t* part1, char* part2);
