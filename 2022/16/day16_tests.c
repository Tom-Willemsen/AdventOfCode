#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day16_impl.h"

char* testdata[10] = {
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


void test_day_16_ex (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 10, &part1, &part2);
    assert_int_equal(part1, 1651);
    
    #ifndef DISABLE_2022_16_P2
    assert_int_equal(part2, 1707);
    #endif
    
    #ifdef DISABLE_2022_16_P2
    assert_int_equal(part2, 0);
    #endif
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_16_ex),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
