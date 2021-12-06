#include "day6_impl.h"

int64_t simulate(ll_i64* initialstate, int64_t days) {
    int64_t numbers[MAX_DAYS], result = 0, day, i, resetfish;
    
    for(day=0; day<MAX_DAYS; ++day) {
        numbers[day] = 0;
    }
    
    ll_i64_node* it = initialstate->start;
    while(ll_i64_next(&it, &day)) {
        assert(day < MAX_DAYS);
        numbers[day]++;
    }
    
    for(i=0; i<days; ++i) {
        resetfish = numbers[0];
        
        for (day=1; day<MAX_DAYS; ++day) {
            numbers[day-1] = numbers[day];
        }
        
        numbers[6] += resetfish;
        numbers[8] = resetfish;
    }
    
    for (day=0; day<MAX_DAYS; ++day) {
        result += numbers[day];
    }
    return result;
}
