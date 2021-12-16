#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_loading.h"
#include "list.h"

const uint8_t PACKETS_MODE = 1;
const uint8_t BITS_MODE = 2;

const uint8_t OP_SUM=0;
const uint8_t OP_PRODUCT=1;
const uint8_t OP_MIN=2;
const uint8_t OP_MAX=3;
const uint8_t OP_GT=5;
const uint8_t OP_LT=6;
const uint8_t OP_EQ=7;

void calculate(char* data, int64_t* part1, int64_t* part2);

static void parse_packet(list_i64* data, uint64_t offset, int64_t* n_bits, int64_t* value, int64_t* version_sum);
