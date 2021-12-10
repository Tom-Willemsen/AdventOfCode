#include "day06_impl.h"

int64_t simulate(list_i64* initialstate, int64_t days) {
    int64_t numbers[MAX_DAYS], result = 0, day, i;
    
    for(day=0; day<MAX_DAYS; ++day) {
        numbers[day] = 0;
    }
    
    for(i=0; i<initialstate->size; ++i) {
        day = list_i64_get(initialstate, i);
        assert(day < MAX_DAYS);
        numbers[day]++;
    }
    
    for(i=0; i<days; ++i) {
        // instead of treating numbers as a bin count treat numbers
        // as a circular list. i.e. effective "starting index" of fish
        // with 0 ticks left shifts by 1 (modulo MAX_DAYS) each "day".
        // Then only need to do something about the fish who are on
        // "tick 0" that day (by incrementing "tick 7" by that amount)
        // The fish which were in tick 0 will get effectively moved to 
        // the end (i.e. tick 9)
        numbers[(i+REPRO_DAYS)%MAX_DAYS] += numbers[i%MAX_DAYS];
    }
    
    for (day=0; day<MAX_DAYS; ++day) {
        result += numbers[day];
    }
    return result;
}
