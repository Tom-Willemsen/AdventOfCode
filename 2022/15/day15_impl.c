#include "day15_impl.h"

static inline int64_t is_undetected(int64_t x, int64_t y, list_tuple3_i64* sensor_distances, int64_t min_x, int64_t min_y, int64_t max_x, int64_t max_y) {
    int64_t sensor_x, sensor_y, distance;

    if (x < min_x || y < min_y || x > max_x || y > max_y) {
        return 0;
    }

    for (uint64_t i=0; i<list_tuple3_i64_size(sensor_distances); ++i) {
        list_tuple3_i64_get(sensor_distances, i, &sensor_x, &sensor_y, &distance);
        if (i64abs(x - sensor_x) + i64abs(y - sensor_y) <= distance) {
            return 0;
        }
    }
    return 1;
}

static void parse(char** data, uint64_t data_size, list_tuple3_i64* sensor_distances, set_tuple_i64* beacons) {
    int64_t sensor_x, sensor_y, beacon_x, beacon_y;
    for (uint64_t i=0; i<data_size; ++i) {
        sscanf(data[i], "Sensor at x=%"SCNd64", y=%"SCNd64": closest beacon is at x=%"SCNd64", y=%"SCNd64, &sensor_x, &sensor_y, &beacon_x, &beacon_y);
        list_tuple3_i64_push_back(sensor_distances, sensor_x, sensor_y, i64abs(sensor_x - beacon_x) + i64abs(sensor_y - beacon_y));
        set_tuple_i64_add(beacons, beacon_x, beacon_y);
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2, int64_t param1, int64_t param2) {
    int64_t min_x = INT64_MAX, max_x = INT64_MIN;
    int64_t x, y;
    
    list_tuple3_i64* sensor_distances = list_tuple3_i64_init(32);
    set_tuple_i64* beacons = set_tuple_i64_init(32);
    
    parse(data, data_size, sensor_distances, beacons);
    
    for (uint64_t i=0; i<list_tuple3_i64_size(sensor_distances); ++i) {
        int64_t sensor_x, sensor_y, distance;
        list_tuple3_i64_get(sensor_distances, i, &sensor_x, &sensor_y, &distance);
        min_x = min(sensor_x - distance, min_x);
        max_x = max(sensor_x + distance, max_x);
    }
    
    bitset* bs = bitset_init(max_x - min_x + 1);
    for (uint64_t i=0; i<list_tuple3_i64_size(sensor_distances); ++i) {
        int64_t x, y, dist;
        list_tuple3_i64_get(sensor_distances, i, &x, &y, &dist);
        if (i64abs(y-param1) <= dist) {
            for (int64_t j = x - (dist - i64abs(y-param1)); j<x + (dist - i64abs(y-param1))+1; ++j) {
                bitset_set(bs, j-min_x);
            }
        }
    }
    
    set_tuple_i64_iterator* beacons_iter = set_tuple_i64_iter(beacons);
    while (set_tuple_i64_next(beacons_iter, &x, &y)) {
        if (y == param1) {
            bitset_clear(bs, x - min_x);
        }
    }
    
    *part1 = bitset_popcnt(bs);
    bitset_free(bs);
    set_tuple_i64_iter_free(beacons_iter);
    set_tuple_i64_free(beacons);
    
    list_tuple_i64* line_segments = list_tuple_i64_init(256);
    set_tuple_i64* intersection_points = set_tuple_i64_init(256);
    
    for (uint64_t i=0; i<list_tuple3_i64_size(sensor_distances); ++i) {
        int64_t x, y, dist;
        list_tuple3_i64_get(sensor_distances, i, &x, &y, &dist);
        
        // y = mx + c , store m & c
        list_tuple_i64_push_back(line_segments, 1, y-x+dist+1);
        list_tuple_i64_push_back(line_segments, 1, y-x-dist-1);
        list_tuple_i64_push_back(line_segments, -1, y+x+dist+1);
        list_tuple_i64_push_back(line_segments, -1, y+x-dist-1);
    }
    
    for (uint64_t i=0; i<list_tuple_i64_size(line_segments); ++i) { 
        int64_t m1, c1, m2, c2;
        list_tuple_i64_get(line_segments, i, &m1, &c1);
        
        for (uint64_t j=i; j<list_tuple_i64_size(line_segments); ++j) {
            list_tuple_i64_get(line_segments, j, &m2, &c2);
            
            if (m1 == m2) {
                // parallel lines, won't intersect
                continue;
            }
            
            int64_t px = (c2-c1)/(m1-m2);
            int64_t py = (m1*(c2-c1))/(m1-m2) + c1;
            if (px >= 0 && px <= param2 && py >= 0 && py <= param2) {
                set_tuple_i64_add(intersection_points, px, py);
            }
        }
    }
    
    set_tuple_i64_iterator* iter = set_tuple_i64_iter(intersection_points);
    while (set_tuple_i64_next(iter, &x, &y)) {
        if (is_undetected(x, y, sensor_distances, 0, 0, param2, param2)) {
            *part2 = 4000000 * x + y;
            break;
        }
    }
    set_tuple_i64_iter_free(iter);
    
    list_tuple_i64_free(line_segments);
    set_tuple_i64_free(intersection_points);
    
    list_tuple3_i64_free(sensor_distances);
}
