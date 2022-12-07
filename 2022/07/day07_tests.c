#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day07_impl.h"

char* testdata[23] = {
    "$ cd /\n",
    "$ ls\n",
    "dir a\n",
    "14848514 b.txt\n",
    "8504156 c.dat\n",
    "dir d\n",
    "$ cd a\n",
    "$ ls\n",
    "dir e\n",
    "29116 f\n",
    "2557 g\n",
    "62596 h.lst\n",
    "$ cd e\n",
    "$ ls\n",
    "584 i\n",
    "$ cd ..\n",
    "$ cd ..\n",
    "$ cd d\n",
    "$ ls\n",
    "4060174 j\n",
    "8033020 d.log\n",
    "5626152 d.ext\n",
    "7214296 k\n"
};

void test_day_7 (void ** state) {
    int64_t part1 = 0;
    int64_t part2 = 0;
    calculate(testdata, 23, &part1, &part2);
    assert_int_equal(part1, 95437);
    assert_int_equal(part2, 24933642);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_7),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
