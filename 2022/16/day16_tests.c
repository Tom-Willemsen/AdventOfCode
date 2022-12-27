#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day16_impl.h"

char* example_data[10] = {
    "Valve AA has flow rate=0; tunnels lead to valves DD, II, BB\n",
    "Valve BB has flow rate=13; tunnels lead to valves CC, AA\n",
    "Valve CC has flow rate=2; tunnels lead to valves DD, BB\n",
    "Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE\n",
    "Valve EE has flow rate=3; tunnels lead to valves FF, DD\n",
    "Valve FF has flow rate=0; tunnels lead to valves EE, GG\n",
    "Valve GG has flow rate=0; tunnels lead to valves FF, HH\n",
    "Valve HH has flow rate=22; tunnel leads to valve GG\n",
    "Valve II has flow rate=0; tunnels lead to valves AA, JJ\n",
    "Valve JJ has flow rate=21; tunnel leads to valve II\n",
};

char* testdata_linear[16] = {
    "Valve AA has flow rate=0; tunnels lead to valves BA\n",
    "Valve BA has flow rate=2; tunnels lead to valves AA, CA\n",
    "Valve CA has flow rate=4; tunnels lead to valves BA, DA\n",
    "Valve DA has flow rate=6; tunnels lead to valves CA, EA\n",
    "Valve EA has flow rate=8; tunnels lead to valves DA, FA\n",
    "Valve FA has flow rate=10; tunnels lead to valves EA, GA\n",
    "Valve GA has flow rate=12; tunnels lead to valves FA, HA\n",
    "Valve HA has flow rate=14; tunnels lead to valves GA, IA\n",
    "Valve IA has flow rate=16; tunnels lead to valves HA, JA\n",
    "Valve JA has flow rate=18; tunnels lead to valves IA, KA\n",
    "Valve KA has flow rate=20; tunnels lead to valves JA, LA\n",
    "Valve LA has flow rate=22; tunnels lead to valves KA, MA\n",
    "Valve MA has flow rate=24; tunnels lead to valves LA, NA\n",
    "Valve NA has flow rate=26; tunnels lead to valves MA, OA\n",
    "Valve OA has flow rate=28; tunnels lead to valves NA, PA\n",
    "Valve PA has flow rate=30; tunnels lead to valves OA\n",
};

char* testdata_quadratic[16] = {
    "Valve AA has flow rate=0; tunnels lead to valves BA\n",
    "Valve BA has flow rate=1; tunnels lead to valves AA, CA\n",
    "Valve CA has flow rate=4; tunnels lead to valves BA, DA\n",
    "Valve DA has flow rate=9; tunnels lead to valves CA, EA\n",
    "Valve EA has flow rate=16; tunnels lead to valves DA, FA\n",
    "Valve FA has flow rate=25; tunnels lead to valves EA, GA\n",
    "Valve GA has flow rate=36; tunnels lead to valves FA, HA\n",
    "Valve HA has flow rate=49; tunnels lead to valves GA, IA\n",
    "Valve IA has flow rate=64; tunnels lead to valves HA, JA\n",
    "Valve JA has flow rate=81; tunnels lead to valves IA, KA\n",
    "Valve KA has flow rate=100; tunnels lead to valves JA, LA\n",
    "Valve LA has flow rate=121; tunnels lead to valves KA, MA\n",
    "Valve MA has flow rate=144; tunnels lead to valves LA, NA\n",
    "Valve NA has flow rate=169; tunnels lead to valves MA, OA\n",
    "Valve OA has flow rate=196; tunnels lead to valves NA, PA\n",
    "Valve PA has flow rate=225; tunnels lead to valves OA\n",
};

char* testdata_circle[16] = {
    "Valve BA has flow rate=2; tunnels lead to valves AA, CA\n",
    "Valve CA has flow rate=10; tunnels lead to valves BA, DA\n",
    "Valve DA has flow rate=2; tunnels lead to valves CA, EA\n",
    "Valve EA has flow rate=10; tunnels lead to valves DA, FA\n",
    "Valve FA has flow rate=2; tunnels lead to valves EA, GA\n",
    "Valve GA has flow rate=10; tunnels lead to valves FA, HA\n",
    "Valve HA has flow rate=2; tunnels lead to valves GA, IA\n",
    "Valve IA has flow rate=10; tunnels lead to valves HA, JA\n",
    "Valve JA has flow rate=2; tunnels lead to valves IA, KA\n",
    "Valve KA has flow rate=10; tunnels lead to valves JA, LA\n",
    "Valve LA has flow rate=2; tunnels lead to valves KA, MA\n",
    "Valve MA has flow rate=10; tunnels lead to valves LA, NA\n",
    "Valve NA has flow rate=2; tunnels lead to valves MA, OA\n",
    "Valve OA has flow rate=10; tunnels lead to valves NA, PA\n",
    "Valve PA has flow rate=2; tunnels lead to valves OA, AA\n",
    "Valve AA has flow rate=0; tunnels lead to valves BA, PA\n",
};

char* testdata_clusters[43] = {
    "Valve AA has flow rate=0; tunnels lead to valves AB, BB, CB\n",
    "Valve AB has flow rate=0; tunnels lead to valves AA, AC\n",
    "Valve AC has flow rate=0; tunnels lead to valves AB, AD\n",
    "Valve AD has flow rate=0; tunnels lead to valves AC, AE\n",
    "Valve AE has flow rate=0; tunnels lead to valves AD, AF\n",
    "Valve AF has flow rate=0; tunnels lead to valves AE, AG\n",
    "Valve AG has flow rate=0; tunnels lead to valves AF, AH\n",
    "Valve AH has flow rate=0; tunnels lead to valves AG, AI\n",
    "Valve AI has flow rate=0; tunnels lead to valves AH, AJ\n",
    "Valve AJ has flow rate=0; tunnels lead to valves AI, AK\n",
    "Valve AK has flow rate=100; tunnels lead to valves AJ, AW, AX, AY, AZ\n",
    "Valve AW has flow rate=10; tunnels lead to valves AK\n",
    "Valve AX has flow rate=10; tunnels lead to valves AK\n",
    "Valve AY has flow rate=10; tunnels lead to valves AK\n",
    "Valve AZ has flow rate=10; tunnels lead to valves AK\n",
    "Valve BB has flow rate=0; tunnels lead to valves AA, BC\n",
    "Valve BC has flow rate=0; tunnels lead to valves BB, BD\n",
    "Valve BD has flow rate=0; tunnels lead to valves BC, BE\n",
    "Valve BE has flow rate=0; tunnels lead to valves BD, BF\n",
    "Valve BF has flow rate=0; tunnels lead to valves BE, BG\n",
    "Valve BG has flow rate=0; tunnels lead to valves BF, BH\n",
    "Valve BH has flow rate=0; tunnels lead to valves BG, BI\n",
    "Valve BI has flow rate=0; tunnels lead to valves BH, BJ\n",
    "Valve BJ has flow rate=0; tunnels lead to valves BI, BK\n",
    "Valve BK has flow rate=100; tunnels lead to valves BJ, BW, BX, BY, BZ\n",
    "Valve BW has flow rate=10; tunnels lead to valves BK\n",
    "Valve BX has flow rate=10; tunnels lead to valves BK\n",
    "Valve BY has flow rate=10; tunnels lead to valves BK\n",
    "Valve BZ has flow rate=10; tunnels lead to valves BK\n",
    "Valve CB has flow rate=0; tunnels lead to valves AA, CC\n",
    "Valve CC has flow rate=0; tunnels lead to valves CB, CD\n",
    "Valve CD has flow rate=0; tunnels lead to valves CC, CE\n",
    "Valve CE has flow rate=0; tunnels lead to valves CD, CF\n",
    "Valve CF has flow rate=0; tunnels lead to valves CE, CG\n",
    "Valve CG has flow rate=0; tunnels lead to valves CF, CH\n",
    "Valve CH has flow rate=0; tunnels lead to valves CG, CI\n",
    "Valve CI has flow rate=0; tunnels lead to valves CH, CJ\n",
    "Valve CJ has flow rate=0; tunnels lead to valves CI, CK\n",
    "Valve CK has flow rate=100; tunnels lead to valves CJ, CW, CX, CY, CZ\n",
    "Valve CW has flow rate=10; tunnels lead to valves CK\n",
    "Valve CX has flow rate=10; tunnels lead to valves CK\n",
    "Valve CY has flow rate=10; tunnels lead to valves CK\n",
    "Valve CZ has flow rate=10; tunnels lead to valves CK\n",
};

char* real_data[66] = {
    "Valve DB has flow rate=0; tunnels lead to valves AC, UN\n",
    "Valve LC has flow rate=6; tunnels lead to valves UV, CM, RD, IM, YQ\n",
    "Valve SU has flow rate=0; tunnels lead to valves OH, BX\n",
    "Valve JS has flow rate=0; tunnels lead to valves GR, RW\n",
    "Valve BX has flow rate=18; tunnels lead to valves PA, SU\n",
    "Valve WI has flow rate=0; tunnels lead to valves GR, JI\n",
    "Valve YQ has flow rate=0; tunnels lead to valves LC, SB\n",
    "Valve HX has flow rate=10; tunnels lead to valves VR, GZ, ID\n",
    "Valve RI has flow rate=0; tunnels lead to valves HF, UV\n",
    "Valve JQ has flow rate=0; tunnels lead to valves AA, IF\n",
    "Valve RK has flow rate=0; tunnels lead to valves AA, CM\n",
    "Valve AC has flow rate=0; tunnels lead to valves DB, HF\n",
    "Valve JI has flow rate=12; tunnels lead to valves WI, YH, ND, ID\n",
    "Valve DF has flow rate=0; tunnels lead to valves JW, AA\n",
    "Valve PA has flow rate=0; tunnels lead to valves BX, RB\n",
    "Valve OU has flow rate=0; tunnels lead to valves OH, XM\n",
    "Valve YO has flow rate=0; tunnels lead to valves OK, HF\n",
    "Valve YY has flow rate=0; tunnels lead to valves UN, MC\n",
    "Valve OJ has flow rate=0; tunnels lead to valves SC, GR\n",
    "Valve VR has flow rate=0; tunnels lead to valves IR, HX\n",
    "Valve EY has flow rate=0; tunnels lead to valves HR, OK\n",
    "Valve LE has flow rate=0; tunnels lead to valves GV, GZ\n",
    "Valve HF has flow rate=14; tunnels lead to valves DS, YO, AC, RI, WP\n",
    "Valve OM has flow rate=0; tunnels lead to valves DS, GV\n",
    "Valve JW has flow rate=0; tunnels lead to valves UN, DF\n",
    "Valve OK has flow rate=9; tunnels lead to valves IF, EY, OV, YO, WM \n",
    "Valve RB has flow rate=0; tunnels lead to valves PA, XM\n",
    "Valve HR has flow rate=0; tunnels lead to valves EY, CQ\n",
    "Valve YM has flow rate=0; tunnels lead to valves GB, NB\n",
    "Valve UN has flow rate=5; tunnels lead to valves RD, DB, JW, YY, WC \n",
    "Valve SO has flow rate=0; tunnels lead to valves AA, RH\n",
    "Valve RW has flow rate=0; tunnels lead to valves JS, GV\n",
    "Valve IF has flow rate=0; tunnels lead to valves OK, JQ\n",
    "Valve WP has flow rate=0; tunnels lead to valves HF, CQ\n",
    "Valve YK has flow rate=0; tunnels lead to valves MO, GV\n",
    "Valve MQ has flow rate=0; tunnels lead to valves AA, HI\n",
    "Valve RH has flow rate=0; tunnels lead to valves SO, GB\n",
    "Valve GB has flow rate=7; tunnels lead to valves YM, RH, PU\n",
    "Valve XM has flow rate=16; tunnels lead to valves OU, ND, NB, RB\n",
    "Valve RD has flow rate=0; tunnels lead to valves UN, LC\n",
    "Valve HI has flow rate=0; tunnels lead to valves MQ, GR\n",
    "Valve OH has flow rate=19; tunnels lead to valves OU, SU\n",
    "Valve DS has flow rate=0; tunnels lead to valves OM, HF\n",
    "Valve GV has flow rate=24; tunnels lead to valves RW, MC, YK, OM, LE\n",
    "Valve AA has flow rate=0; tunnels lead to valves SO, DF, RK, MQ, JQ \n",
    "Valve CQ has flow rate=17; tunnels lead to valves SB, MO, WP, SC, HR\n",
    "Valve UV has flow rate=0; tunnels lead to valves LC, RI\n",
    "Valve OV has flow rate=0; tunnels lead to valves OK, WC\n",
    "Valve CM has flow rate=0; tunnels lead to valves RK, LC\n",
    "Valve YH has flow rate=0; tunnels lead to valves NW, JI\n",
    "Valve GZ has flow rate=0; tunnels lead to valves LE, HX\n",
    "Valve WC has flow rate=0; tunnels lead to valves UN, OV\n",
    "Valve ID has flow rate=0; tunnels lead to valves JI, HX\n",
    "Valve SC has flow rate=0; tunnels lead to valves OJ, CQ\n",
    "Valve GR has flow rate=11; tunnels lead to valves OJ, WI, HI, PU, JS\n",
    "Valve IM has flow rate=0; tunnels lead to valves LC, WM\n",
    "Valve NB has flow rate=0; tunnels lead to valves YM, XM\n",
    "Valve TS has flow rate=20; tunnel leads to valve NW\n",
    "Valve SB has flow rate=0; tunnels lead to valves CQ, YQ\n",
    "Valve MC has flow rate=0; tunnels lead to valves GV, YY\n",
    "Valve ND has flow rate=0; tunnels lead to valves JI, XM\n",
    "Valve MO has flow rate=0; tunnels lead to valves CQ, YK\n",
    "Valve PU has flow rate=0; tunnels lead to valves GB, GR\n",
    "Valve IR has flow rate=13; tunnel leads to valve VR\n",
    "Valve NW has flow rate=0; tunnels lead to valves YH, TS\n",
    "Valve WM has flow rate=0; tunnels lead to valves IM, OK\n",
};


void test_day_16_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(example_data, 10, &part1, &part2);
    assert_int_equal(part1, 1651);
    assert_int_equal(part2, 1707);
}

void test_day_16_linear (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata_linear, 16, &part1, &part2);
    assert_int_equal(part1, 2640);
    assert_int_equal(part2, 2670);
}

void test_day_16_quadratic (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata_quadratic, 16, &part1, &part2);
    assert_int_equal(part1, 13468);
    assert_int_equal(part2, 12887);
}

void test_day_16_circle (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata_circle, 16, &part1, &part2);
    assert_int_equal(part1, 1288);
    assert_int_equal(part2, 1484);
}

void test_day_16_clusters (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata_clusters, 43, &part1, &part2);
    assert_int_equal(part1, 2400);
    assert_int_equal(part2, 3680);
}

void test_day_16_real (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(real_data, 66, &part1, &part2);
    assert_int_equal(part1, 1673);
    assert_int_equal(part2, 2343);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_16_ex),
        cmocka_unit_test (test_day_16_linear),
        cmocka_unit_test (test_day_16_quadratic),
        cmocka_unit_test (test_day_16_circle),
        cmocka_unit_test (test_day_16_clusters),
        cmocka_unit_test (test_day_16_real),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
