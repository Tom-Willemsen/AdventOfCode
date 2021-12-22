#include "day19_impl.h"

static list_tuple3_i64** parse_input(char** data, uint64_t data_size, uint64_t* num_scanners) {
    int64_t scanner = 0, x=0, y=0, z=0;
    *num_scanners = 0;
    for (uint64_t i=0; i<data_size; ++i) {
        if (data[i][0] == '-' && data[i][1] == '-' && data[i][2] == '-') {
            (*num_scanners)++;
        }
    }
    
    list_tuple3_i64** scanners = calloc(*num_scanners, sizeof(list_tuple3_i64*));
    for (uint64_t i=0; i<(*num_scanners); ++i) {
        scanners[i] = list_tuple3_i64_init(1);
    }
    
    for (uint64_t i=0; i<data_size; ++i) {
        if (data[i][0] == '-' && data[i][1] == '-' && data[i][2] == '-') {
            sscanf(data[i], "--- scanner %"SCNd64" ---", &scanner);
        } else if (data[i][0] != '\n') {
            sscanf(data[i], "%"SCNd64",%"SCNd64",%"SCNd64, &x, &y, &z);
            list_tuple3_i64_push_back(scanners[scanner], x, y, z);
        }
    }
    return scanners;
}

static inline void apply_coord_transform(Transform transform, int64_t px, int64_t py, int64_t pz, int64_t* tx, int64_t* ty, int64_t* tz) {
    int64_t in[3] = {px, py, pz};
    *tx = in[transform.axis_x] * transform.sign_x;
    *ty = in[transform.axis_y] * transform.sign_y;
    *tz = in[transform.axis_z] * transform.sign_z;
}

static int64_t try_arrange_with_transform(list_tuple3_i64* scanner, int64_t scanner_number, list_i64* found_scanners, list_tuple3_i64* found_beacons, 
                                          list_tuple3_i64* scanner_positions, set_tuple3_i64* known_beacons, Transform transform) {
    
    int64_t known_beacon_x, known_beacon_y, known_beacon_z;
    set_tuple3_i64_iterator* iter = set_tuple3_i64_iter(known_beacons);
    while (set_tuple3_i64_next(iter, &known_beacon_x, &known_beacon_y, &known_beacon_z)) {
        // starting at 11 here is a slight trick - If any of the first 11 would cause more than 12 matches, then we'll pick
        // up one of the others. So we can skip the first 11.
        for (uint64_t test_beacon=11; test_beacon<list_tuple3_i64_size(scanner); ++test_beacon) {
            int64_t dx, dy, dz, scanner_pos_x, scanner_pos_y, scanner_pos_z, test_beacon_x, test_beacon_y, test_beacon_z, seen_beacons = 1;
            
            list_tuple3_i64_get(scanner, test_beacon, &test_beacon_x, &test_beacon_y, &test_beacon_z);
            apply_coord_transform(transform, test_beacon_x, test_beacon_y, test_beacon_z, &dx, &dy, &dz);
            scanner_pos_x = known_beacon_x - dx;
            scanner_pos_y = known_beacon_y - dy;
            scanner_pos_z = known_beacon_z - dz;
            
            for (uint64_t j=0; j<list_tuple3_i64_size(scanner); ++j) {
                int64_t beacon_x, beacon_y, beacon_z;
                
                if (j == test_beacon) {
                    // this one is already accounted for by setting seen_beacons to 1 above.
                    continue;
                }
                
                list_tuple3_i64_get(scanner, j, &beacon_x, &beacon_y, &beacon_z);
                apply_coord_transform(transform, beacon_x, beacon_y, beacon_z, &dx, &dy, &dz);
                
                if (set_tuple3_i64_contains(known_beacons, scanner_pos_x + dx, scanner_pos_y + dy, scanner_pos_z + dz)) {
                    seen_beacons++;
                    if (seen_beacons >= 12) {
                        // We've seen enough beacons - move on
                        break;
                    }
                } else if (seen_beacons + list_tuple3_i64_size(scanner) - j < 12) {
                    // early exit condition - even if all the remaining beacons align, we still wouldn't have
                    // 12 matches
                    break;
                }
            }
            
            if (seen_beacons >= 12) {
                #pragma omp critical
                {
                    for (uint64_t j=0; j<list_tuple3_i64_size(scanner); ++j) {
                        int64_t beacon_x, beacon_y, beacon_z;
                        list_tuple3_i64_get(scanner, j, &beacon_x, &beacon_y, &beacon_z);
                        apply_coord_transform(transform, beacon_x, beacon_y, beacon_z, &dx, &dy, &dz);
                        list_tuple3_i64_push_back(found_beacons, scanner_pos_x + dx, scanner_pos_y + dy, scanner_pos_z + dz);
                    }
                    list_tuple3_i64_push_back(scanner_positions, scanner_pos_x, scanner_pos_y, scanner_pos_z);
                    list_i64_push_back(found_scanners, scanner_number);
                }
                return 1;
            }
        }
    }
    set_tuple3_i64_iter_free(iter);
    return 0;
}

static void try_arrange(list_tuple3_i64* scanner, int64_t scanner_number, list_i64* found_scanners, list_tuple3_i64* found_beacons, 
                        list_tuple3_i64* scanner_positions, set_tuple3_i64* known_beacons) {
    
    for (uint64_t i=0; i<NUM_ROTATION_TRANSFORMS; ++i) {
        if (try_arrange_with_transform(scanner, scanner_number, found_scanners, found_beacons, 
                                       scanner_positions, known_beacons, ROTATION_TRANSFORMS[i])) 
        {
            return;
        }
    }
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    uint64_t num_scanners = 0;
    list_tuple3_i64** scanners = parse_input(data, data_size, &num_scanners);
    assert(num_scanners>=2);
    
    list_i64* scanners_left_to_arrange = list_i64_init(num_scanners);
    for (uint64_t i=1; i<num_scanners; ++i) {
        list_i64_push_back(scanners_left_to_arrange, i);
    }
    
    set_tuple3_i64* known_beacons = set_tuple3_i64_init(16384);
    set_tuple3_i64_add_all(known_beacons, scanners[0]);
    
    list_tuple3_i64* scanner_positions = list_tuple3_i64_init(num_scanners);
    list_tuple3_i64_push_back(scanner_positions, 0, 0, 0);
    
    list_i64* found_scanners = list_i64_init(num_scanners);
    list_tuple3_i64* found_beacons = list_tuple3_i64_init(data_size);
    
    while (list_i64_size(scanners_left_to_arrange) > 0) {
        #pragma omp parallel for schedule(dynamic, 1) default(shared)
        for (uint64_t i=0; i<list_i64_size(scanners_left_to_arrange); ++i) {
            int64_t n = list_i64_get(scanners_left_to_arrange, i);
            list_tuple3_i64* scanner = scanners[n];
            try_arrange(scanner, n, found_scanners, found_beacons, scanner_positions, known_beacons);
        }
        
        set_tuple3_i64_add_all(known_beacons, found_beacons);
        
        for (uint64_t i=0; i<list_i64_size(found_scanners); ++i) {
            list_i64_remove(scanners_left_to_arrange, list_i64_indexof(scanners_left_to_arrange, list_i64_get(found_scanners, i)));
        }
        
        list_i64_clear(found_scanners);
        list_tuple3_i64_clear(found_beacons);
    }
    
    list_i64_free(found_scanners);
    list_tuple3_i64_free(found_beacons);
    
    *part1 = set_tuple3_i64_size(known_beacons);
    *part2 = 0;
    
    for (uint64_t i=0; i<list_tuple3_i64_size(scanner_positions); ++i) {
        int64_t p1_x, p1_y, p1_z;
        list_tuple3_i64_get(scanner_positions, i, &p1_x, &p1_y, &p1_z);
        for (uint64_t j=0; j<list_tuple3_i64_size(scanner_positions); ++j) {
            int64_t p2_x, p2_y, p2_z;
            list_tuple3_i64_get(scanner_positions, j, &p2_x, &p2_y, &p2_z);
            *part2 = max(*part2, i64abs(p2_x - p1_x) + i64abs(p2_y - p1_y) + i64abs(p2_z - p1_z));
        }
    }
    
    for (uint64_t i=0; i<num_scanners; ++i) {
        list_tuple3_i64_free(scanners[i]);
    }
    set_tuple3_i64_free(known_beacons);
    list_tuple3_i64_free(scanner_positions);
    list_i64_free(scanners_left_to_arrange);
    free(scanners);
}
