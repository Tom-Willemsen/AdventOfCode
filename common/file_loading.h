#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

FILE* open_arg_as_file_or_exit(int argc, char** argv);
char** load_file_as_str_arr(FILE* fptr, uint64_t *size);
void free_str_arr(char** const str_arr, const uint64_t size);
uint8_t** load_dense_file_as_uint8_arr(FILE* fptr, uint64_t *y_size, uint64_t *x_size);
list_i64* load_file_as_list_i64(FILE* fptr);
