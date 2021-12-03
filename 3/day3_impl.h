#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t part1(char** data, uint64_t data_size);
uint64_t count_char_matching_selector(char** data, uint64_t data_size, char* selector, uint64_t pos, char c);
char* first_matching_selector(char** data, uint64_t data_size, char* selector, uint64_t pos);
uint64_t part2(char** data, uint64_t data_size, uint64_t is_co2);
