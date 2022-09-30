#include "day21_impl.h"

static const int64_t DIRAC_ROLL_COUNT = 7;
static const int64_t DIRAC_ROLL_VALUES[7] = {3, 4, 5, 6, 7, 8, 9};
static const int64_t DIRAC_ROLL_FREQS[7] = {1, 3, 6, 7, 6, 3, 1};

static int64_t calculate_part1(int64_t p1_pos, int64_t p2_pos) {
    int64_t p1_score = 0, p2_score = 0, rolls = 0;
    
    while (p1_score < 1000 && p2_score < 1000) {
        int64_t *pos = (rolls % 2) == 0 ? &p1_pos : &p2_pos;
        int64_t *score = (rolls % 2) == 0 ? &p1_score : &p2_score;

        for (uint64_t i=0; i<3; ++i) {
            (*pos) += (rolls % 100) + 1;
            rolls++;
        }
        (*pos) = (((*pos) - 1) % 10) + 1;
        (*score) += (*pos);
    }
    
    return min(p1_score, p2_score) * rolls;
}

static int64_t pack_state(int64_t p1pos, int64_t p1score, int64_t p2pos, int64_t p2score, int64_t turn) {
    int64_t result = turn;
    assert(p1pos >= 0 && p1pos < 32);
    assert(p2pos >= 0 && p2pos < 32);
    assert(p1score >= 0 && p1score < 32);
    assert(p2score >= 0 && p2score < 32);
    assert(turn >= 0 && turn < 32);
    result *= 32;
    result += p2score;
    result *= 32;
    result += p2pos;
    result *= 32;
    result += p1score;
    result *= 32;
    result += p1pos;
    return result;
}

static void unpack_state(int64_t packed_state, int64_t* p1pos, int64_t* p1score, int64_t* p2pos, int64_t* p2score, int64_t* turn) {
    *p1pos = packed_state % 32;
    packed_state /= 32;
    *p1score = packed_state % 32;
    packed_state /= 32;
    *p2pos = packed_state % 32;
    packed_state /= 32;
    *p2score = packed_state % 32;
    packed_state /= 32;
    *turn = packed_state;
}

static int64_t calculate_part2(int64_t p1_pos, int64_t p2_pos) {
    int64_t p1roll, p1roll_freq, p2roll, p2roll_freq, newstate, p1wins = 0, p2wins = 0;
    int64_t state, count, p1pos, p1score, p2pos, p2score, turn;
    counter_i64* game_states = counter_i64_init(10000);
    counter_i64_iterator* iter;
    
    counter_i64_set(game_states, pack_state(p1_pos, 0, p2_pos, 0, 0), 1);
    
    for (uint64_t t = 0; t<21; ++t) {
            
        iter = counter_i64_iter(game_states);
        while (counter_i64_next(iter, &state, &count)) {
            unpack_state(state, &p1pos, &p1score, &p2pos, &p2score, &turn);
            
            if (p1score >= 21 || p2score >= 21 || turn != t) {
                continue;
            }
            
            for (uint64_t i=0; i<DIRAC_ROLL_COUNT; ++i) {
                p1roll = DIRAC_ROLL_VALUES[i];
                p1roll_freq = DIRAC_ROLL_FREQS[i];
                for (uint64_t j=0; j<DIRAC_ROLL_COUNT; ++j) {
                    p2roll = DIRAC_ROLL_VALUES[j];
                    p2roll_freq = DIRAC_ROLL_FREQS[j];
                    
                    if (p1score + (p1pos + p1roll - 1) % 10 + 1 >= 21) {
                        newstate = pack_state(
                            ((p1pos + p1roll - 1) % 10) + 1, 
                            (p1score + (p1pos + p1roll - 1) % 10) + 1, 
                            p2pos, 
                            p2score, 
                            turn + 1
                        );
                    } else {
                        newstate = pack_state(
                            ((p1pos + p1roll - 1) % 10) + 1, 
                            (p1score + (p1pos + p1roll - 1) % 10) + 1, 
                            ((p2pos + p2roll - 1) % 10) + 1, 
                            (p2score + (p2pos + p2roll - 1) % 10) + 1, 
                            turn + 1
                        );
                    }
                    counter_i64_incrementby(game_states, newstate, p1roll_freq * p2roll_freq * counter_i64_get(game_states, state));
                }
            }
        }
        counter_i64_iter_free(iter);
    }
    
    iter = counter_i64_iter(game_states);
    while (counter_i64_next(iter, &state, &count)) {
        unpack_state(state, &p1pos, &p1score, &p2pos, &p2score, &turn);
        
        if (p1score >= 21) {
            p1wins += count / 27;
        } else if (p2score >= 21) {
            p2wins += count;
        }
    }
    counter_i64_iter_free(iter);
    
    counter_i64_free(game_states);
    
    return max(p1wins, p2wins);
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t p1_pos, p2_pos;
    assert(data_size >= 2);
    sscanf(data[0], "Player 1 starting position: %"SCNd64, &p1_pos);
    sscanf(data[1], "Player 2 starting position: %"SCNd64, &p2_pos);

    *part1 = calculate_part1(p1_pos, p2_pos);
    *part2 = calculate_part2(p1_pos, p2_pos);
}
