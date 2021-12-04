#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

FILE* open_arg_as_file_or_exit(int argc, char** argv);
char** load_file_as_str_arr(FILE* fptr, uint64_t *size);
void free_str_arr(char** const str_arr, const uint64_t size);
ll_i64* load_file_as_ll_i64(FILE* fptr);
