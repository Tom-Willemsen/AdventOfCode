#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "list.h"

list_i64* str_to_int64_list(const char* const data, const char delim);
