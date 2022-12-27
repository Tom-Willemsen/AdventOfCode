#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_loading.h"
#include "deque.h"
#include "map.h"
#include "list_tuple2.h"
#include "list_tuple3.h"
#include "set_tuple2.h"
#include "set_tuple3.h"
#include "util.h"

char* dec_to_snafu(int64_t dec);
int64_t snafu_to_dec(char* snafu);
char* calculate(char** data, uint64_t data_size);
