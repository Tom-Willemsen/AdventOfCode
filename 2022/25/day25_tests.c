#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day25_impl.h"

char* testdata[13] = {
    "1=-0-2\n",
    "12111\n",
    "2=0=\n",
    "21\n",
    "2=01\n",
    "111\n",
    "20012\n",
    "112\n",
    "1=-1=\n",
    "1-12\n",
    "12\n",
    "1=\n",
    "122\n",
};

void test_day_25_ex (void ** state) {
    char* part1 = calculate(testdata, 13);
    assert_string_equal(part1, "2=-1=0");
    free(part1);
}

void test_day_25_dec_to_snafu_1 (void** state) {
    char* result = dec_to_snafu(1);
    assert_string_equal(result, "1");
    free(result);
}

void test_day_25_dec_to_snafu_2 (void** state) {
    char* result = dec_to_snafu(2);
    assert_string_equal(result, "2");
    free(result);
}

void test_day_25_dec_to_snafu_3 (void** state) {
    char* result = dec_to_snafu(3);
    assert_string_equal(result, "1=");
    free(result);
}

void test_day_25_dec_to_snafu_4 (void** state) {
    char* result = dec_to_snafu(4);
    assert_string_equal(result, "1-");
    free(result);
}

void test_day_25_dec_to_snafu_5 (void** state) {
    char* result = dec_to_snafu(5);
    assert_string_equal(result, "10");
    free(result);
}

void test_day_25_dec_to_snafu_6 (void** state) {
    char* result = dec_to_snafu(6);
    assert_string_equal(result, "11");
    free(result);
}

void test_day_25_dec_to_snafu_7 (void** state) {
    char* result = dec_to_snafu(7);
    assert_string_equal(result, "12");
    free(result);
}

void test_day_25_dec_to_snafu_8 (void** state) {
    char* result = dec_to_snafu(8);
    assert_string_equal(result, "2=");
    free(result);
}

void test_day_25_dec_to_snafu_9 (void** state) {
    char* result = dec_to_snafu(9);
    assert_string_equal(result, "2-");
    free(result);
}

void test_day_25_dec_to_snafu_10 (void** state) {
    char* result = dec_to_snafu(10);
    assert_string_equal(result, "20");
    free(result);
}

void test_day_25_dec_to_snafu_15 (void** state) {
    char* result = dec_to_snafu(15);
    assert_string_equal(result, "1=0");
    free(result);
}

void test_day_25_dec_to_snafu_20 (void** state) {
    char* result = dec_to_snafu(20);
    assert_string_equal(result, "1-0");
    free(result);
}

void test_day_25_dec_to_snafu_2022 (void** state) {
    char* result = dec_to_snafu(2022);
    assert_string_equal(result, "1=11-2");
    free(result);
}

void test_day_25_dec_to_snafu_12345 (void** state) {
    char* result = dec_to_snafu(12345);
    assert_string_equal(result, "1-0---0");
    free(result);
}

void test_day_25_dec_to_snafu_314159265 (void** state) {
    char* result = dec_to_snafu(314159265);
    assert_string_equal(result, "1121-1110-1=0");
    free(result);
}

void test_day_25_snafu_to_dec_1(void** state) {
    assert_int_equal(snafu_to_dec("1"), 1);
}

void test_day_25_snafu_to_dec_2(void** state) {
    assert_int_equal(snafu_to_dec("2"), 2);
}

void test_day_25_snafu_to_dec_3(void** state) {
    assert_int_equal(snafu_to_dec("1="), 3);
}

void test_day_25_snafu_to_dec_4(void** state) {
    assert_int_equal(snafu_to_dec("1-"), 4);
}

void test_day_25_snafu_to_dec_5(void** state) {
    assert_int_equal(snafu_to_dec("10"), 5);
}

void test_day_25_snafu_to_dec_6(void** state) {
    assert_int_equal(snafu_to_dec("11"), 6);
}

void test_day_25_snafu_to_dec_7(void** state) {
    assert_int_equal(snafu_to_dec("12"), 7);
}

void test_day_25_snafu_to_dec_8(void** state) {
    assert_int_equal(snafu_to_dec("2="), 8);
}

void test_day_25_snafu_to_dec_9(void** state) {
    assert_int_equal(snafu_to_dec("2-"), 9);
}

void test_day_25_snafu_to_dec_10(void** state) {
    assert_int_equal(snafu_to_dec("20"), 10);
}

void test_day_25_snafu_to_dec_15(void** state) {
    assert_int_equal(snafu_to_dec("1=0"), 15);
}

void test_day_25_snafu_to_dec_20(void** state) {
    assert_int_equal(snafu_to_dec("1-0"), 20);
}

void test_day_25_snafu_to_dec_2022(void** state) {
    assert_int_equal(snafu_to_dec("1=11-2"), 2022);
}

void test_day_25_snafu_to_dec_12345(void** state) {
    assert_int_equal(snafu_to_dec("1-0---0"), 12345);
}

void test_day_25_snafu_to_dec_314159265(void** state) {
    assert_int_equal(snafu_to_dec("1121-1110-1=0"), 314159265);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_25_ex),
        cmocka_unit_test (test_day_25_dec_to_snafu_1),
        cmocka_unit_test (test_day_25_dec_to_snafu_2),
        cmocka_unit_test (test_day_25_dec_to_snafu_3),
        cmocka_unit_test (test_day_25_dec_to_snafu_4),
        cmocka_unit_test (test_day_25_dec_to_snafu_5),
        cmocka_unit_test (test_day_25_dec_to_snafu_6),
        cmocka_unit_test (test_day_25_dec_to_snafu_7),
        cmocka_unit_test (test_day_25_dec_to_snafu_8),
        cmocka_unit_test (test_day_25_dec_to_snafu_9),
        cmocka_unit_test (test_day_25_dec_to_snafu_10),
        cmocka_unit_test (test_day_25_dec_to_snafu_15),
        cmocka_unit_test (test_day_25_dec_to_snafu_20),
        cmocka_unit_test (test_day_25_dec_to_snafu_2022),
        cmocka_unit_test (test_day_25_dec_to_snafu_12345),
        cmocka_unit_test (test_day_25_dec_to_snafu_314159265),
        cmocka_unit_test (test_day_25_snafu_to_dec_1),
        cmocka_unit_test (test_day_25_snafu_to_dec_2),
        cmocka_unit_test (test_day_25_snafu_to_dec_3),
        cmocka_unit_test (test_day_25_snafu_to_dec_4),
        cmocka_unit_test (test_day_25_snafu_to_dec_5),
        cmocka_unit_test (test_day_25_snafu_to_dec_6),
        cmocka_unit_test (test_day_25_snafu_to_dec_7),
        cmocka_unit_test (test_day_25_snafu_to_dec_8),
        cmocka_unit_test (test_day_25_snafu_to_dec_9),
        cmocka_unit_test (test_day_25_snafu_to_dec_10),
        cmocka_unit_test (test_day_25_snafu_to_dec_15),
        cmocka_unit_test (test_day_25_snafu_to_dec_20),
        cmocka_unit_test (test_day_25_snafu_to_dec_2022),
        cmocka_unit_test (test_day_25_snafu_to_dec_12345),
        cmocka_unit_test (test_day_25_snafu_to_dec_314159265),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
