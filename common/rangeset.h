#pragma once

#include <list_tuple2.h>

typedef struct rangeset {
    list_tuple_i64* on_ranges;
} rangeset;

static rangeset* rangeset_init() {
    rangeset* rs = calloc(1, sizeof(rangeset));
    rs->on_ranges = list_tuple_i64_init(16);
    return rs;
}

static void rangeset_free(rangeset* rs) {
    list_tuple_i64_free(rs->on_ranges);
    free(rs);
}

static void _rangeset_remove_ranges_fully_within(rangeset* rs, int64_t start, int64_t end) {
    int64_t s, e;
    for (size_t i=list_tuple_i64_size(rs->on_ranges); i>0; --i) {
        list_tuple_i64_get(rs->on_ranges, i-1, &s, &e);
        if (s >= start && e <= end) {
            // remove any existing ranges that are fully within the new "on" range.
            list_tuple_i64_remove(rs->on_ranges, i-1);
        }
    }
}

static int64_t _rangeset_get_new_endpoint(rangeset* rs, int64_t end) {
    int64_t s, e;
    int64_t result = end;
    for (size_t i=0; i<list_tuple_i64_size(rs->on_ranges); ++i) {
        list_tuple_i64_get(rs->on_ranges, i, &s, &e);
        if (s <= end && e >= end) {
            result = max(result, e);
        }
    }
    return result;
}

static int64_t _rangeset_get_new_startpoint(rangeset* rs, int64_t start) {
    int64_t s, e;
    int64_t result = start;
    for (size_t i=0; i<list_tuple_i64_size(rs->on_ranges); ++i) {
        list_tuple_i64_get(rs->on_ranges, i, &s, &e);
        if (s <= start && e >= start) {
            result = min(result, s);
        }
    }
    return result;
}

static void rangeset_set(rangeset* rs, int64_t start, int64_t end) {
    assert(start < end);
    
    int64_t new_startpoint = _rangeset_get_new_startpoint(rs, start);
    int64_t new_endpoint = _rangeset_get_new_endpoint(rs, end);
    _rangeset_remove_ranges_fully_within(rs, new_startpoint, new_endpoint);
    list_tuple_i64_push_back(rs->on_ranges, new_startpoint, new_endpoint);
}

static uint64_t rangeset_popcnt(rangeset* rs) {
    uint64_t result = 0;
    int64_t s, e;
    
    for (size_t i=0; i<list_tuple_i64_size(rs->on_ranges); ++i) {
        list_tuple_i64_get(rs->on_ranges, i, &s, &e);
        result += e - s + 1;
    }
    
    return result;
}
