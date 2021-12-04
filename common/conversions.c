#include "conversions.h"

ll_i64* str_to_int64_ll(const char* const data, const char delim) {
    int64_t slen = strlen(data);
    char* buffer = calloc(slen + 1, sizeof(char));
    
    ll_i64* ll = ll_i64_init();
    
    int64_t buffer_idx = 0;
    char c;
    
    for (int64_t idx = 0; idx < slen; ++idx) {
        c = data[idx];
        if (c == '\n' || (c == delim && buffer_idx > 0)) {
            ll_i64_push_back(ll, strtol(buffer, NULL, 10));
            
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
    return ll;
}
