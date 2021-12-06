#include "day6_impl.h"

int64_t simulate(ll_i64* initialstate, int64_t days) {
    int64_t numbers[MAX_DAYS+1], value, result = 0, day, i, resetfish, newfish;
    
    for(i=0; i<MAX_DAYS+1; ++i) {
        numbers[i] = 0;
    }
    
    ll_i64_node* it = initialstate->start;
    while(ll_i64_next(&it, &value)) {
        assert(value <= MAX_DAYS);
        numbers[value]++;
    }
    
    for(day=0; day<days; ++day) {
        resetfish = numbers[0];
        newfish = numbers[0];
        
        for (i=1; i<MAX_DAYS+1; ++i) {
            numbers[i-1] = numbers[i];
        }
        
        numbers[6] += resetfish;
        numbers[8] = newfish;
    }
    
    for (i=0; i<MAX_DAYS+1; ++i) {
        result += numbers[i];
    }
    return result;
}
