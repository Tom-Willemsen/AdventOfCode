#include "conversions.h"

list_i64* str_to_int64_list(const char* const data, const char delim) {
    int64_t slen = strlen(data);
    char* buffer = calloc(slen + 1, sizeof(char));
    
    list_i64* list = list_i64_init(slen);
    
    int64_t buffer_idx = 0;
    char c;
    
    for (int64_t idx = 0; idx < slen; ++idx) {
        c = data[idx];
        if (c == '\n' || (c == delim && buffer_idx > 0)) {
            list_i64_push_back(list, strtol(buffer, NULL, 10));
            
            for (int64_t i=0; i<slen + 1; ++i) {
                buffer[i] = '\0';
            }
            memset(buffer, '\0', slen + 1);
            buffer_idx = 0;
        } else if (c >= '0' && c <= '9') {
            buffer[buffer_idx] = c;
            buffer_idx++;
        }
    }
    
    free(buffer);
    return list;
}
