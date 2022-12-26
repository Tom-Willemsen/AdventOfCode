#include "day25_impl.h"


static void remove_leading_zeros(char* str) {
    uint64_t len = strlen(str);
    uint64_t nonzero = 0;
    while (str[nonzero] == '0') {
        nonzero++;
    }
    memmove(str, str + nonzero, len - nonzero * sizeof(char));
    str[len-nonzero] = '\0';
}


static uint8_t replace_chars(char* str, char c1, char c2, char r1, char r2) {
    
    uint64_t len = strlen(str);
    for (uint64_t i=0; i<len - 1; ++i) {
        if (str[i] == c1 && str[i+1] == c2) {
            str[i] = r1;
            str[i+1] = r2;
            return 1;
        }
    }
    return 0;
}


char* dec_to_snafu(int64_t dec) {
    int64_t places = 1;
    while (pow(5, places) < dec) {
        places++;
    }
    char* result = calloc(places + 3, sizeof(char));
    result[0] = '0';
    int64_t i=1;
    for (int64_t p=places; p >= 0; --p) {
        int64_t r = (dec / ((int64_t) pow(5, p))) % 5;
        
        result[i] = '0' + r;
        i++;
    }
    
    while (1) {
        
        if (replace_chars(result, '-', '4', '0', '-')) continue;
        if (replace_chars(result, '=', '4', '-', '-')) continue;
        if (replace_chars(result, '0', '4', '1', '-')) continue;
        if (replace_chars(result, '1', '4', '2', '-')) continue;
        if (replace_chars(result, '2', '4', '3', '-')) continue;
        if (replace_chars(result, '3', '4', '4', '-')) continue;
        if (replace_chars(result, '0', '3', '1', '=')) continue;
        if (replace_chars(result, '1', '3', '2', '=')) continue;
        if (replace_chars(result, '2', '3', '3', '=')) continue;
        if (replace_chars(result, '-', '3', '0', '=')) continue;
        if (replace_chars(result, '=', '3', '1', '=')) continue;
        if (replace_chars(result, '3', '3', '4', '-')) continue;
        
        break;
    }
    remove_leading_zeros(result);
    return result;
}


int64_t snafu_to_dec(char* snafu) {
    int64_t result = 0;
    int64_t mul = 1;
    
    for (int64_t i = strlen(snafu)-1; i>=0; --i) {
        if (snafu[i] == '\n') {
            continue;
        } else if (snafu[i] == '=') {
            result -= 2 * mul;
        } else if (snafu[i] == '-') {
            result -= mul;
        } else if (snafu[i] == '1') {
            result += mul;
        } else if (snafu[i] == '2') {
            result += 2 * mul;
        }
        mul *= 5;
    }
    return result;
}


char* calculate(char** data, uint64_t data_size) {
    int64_t p1 = 0;
    for (uint64_t i=0; i<data_size; ++i) {
        p1 += snafu_to_dec(data[i]);
    }
    return dec_to_snafu(p1);
}
