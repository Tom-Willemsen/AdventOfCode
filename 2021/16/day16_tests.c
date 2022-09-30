#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day16_impl.h"

void test_day_16_p1_ex1 (void ** state) {
    int64_t part1, part2;
    calculate("8A004A801A8002F478", &part1, &part2);
    assert_int_equal(part1, 16);
}

void test_day_16_p1_ex2 (void ** state) {
    int64_t part1, part2;
    calculate("620080001611562C8802118E34", &part1, &part2);
    assert_int_equal(part1, 12);
}

void test_day_16_p1_ex3 (void ** state) {
    int64_t part1, part2;
    calculate("C0015000016115A2E0802F182340", &part1, &part2);
    assert_int_equal(part1, 23);
}

void test_day_16_p1_ex4 (void ** state) {
    int64_t part1, part2;
    calculate("A0016C880162017C3686B18A3D4780", &part1, &part2);
    assert_int_equal(part1, 31);
}

void test_day_16_p2_ex1 (void ** state) {
    int64_t part1, part2;
    calculate("C200B40A82", &part1, &part2);
    assert_int_equal(part2, 3);
}

void test_day_16_p2_ex2 (void ** state) {
    int64_t part1, part2;
    calculate("04005AC33890", &part1, &part2);
    assert_int_equal(part2, 54);
}

void test_day_16_p2_ex3 (void ** state) {
    int64_t part1, part2;
    calculate("880086C3E88112", &part1, &part2);
    assert_int_equal(part2, 7);
}

void test_day_16_p2_ex4 (void ** state) {
    int64_t part1, part2;
    calculate("CE00C43D881120", &part1, &part2);
    assert_int_equal(part2, 9);
}

void test_day_16_p2_ex5 (void ** state) {
    int64_t part1, part2;
    calculate("D8005AC2A8F0", &part1, &part2);
    assert_int_equal(part2, 1);
}

void test_day_16_p2_ex6 (void ** state) {
    int64_t part1, part2;
    calculate("F600BC2D8F", &part1, &part2);
    assert_int_equal(part2, 0);
}

void test_day_16_p2_ex7 (void ** state) {
    int64_t part1, part2;
    calculate("9C005AC2F8F0", &part1, &part2);
    assert_int_equal(part2, 0);
}

void test_day_16_p2_ex8 (void ** state) {
    int64_t part1, part2;
    calculate("9C0141080250320F1802104A08", &part1, &part2);
    assert_int_equal(part2, 1);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_16_p1_ex1),
        cmocka_unit_test (test_day_16_p1_ex2),
        cmocka_unit_test (test_day_16_p1_ex3),
        cmocka_unit_test (test_day_16_p1_ex4),
        cmocka_unit_test (test_day_16_p2_ex1),
        cmocka_unit_test (test_day_16_p2_ex2),
        cmocka_unit_test (test_day_16_p2_ex3),
        cmocka_unit_test (test_day_16_p2_ex4),
        cmocka_unit_test (test_day_16_p2_ex5),
        cmocka_unit_test (test_day_16_p2_ex6),
        cmocka_unit_test (test_day_16_p2_ex7),
        cmocka_unit_test (test_day_16_p2_ex8),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
