#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <limits.h>
#include <stdlib.h>

#include "floyd.h"

void floyd_test1(void);
void floyd_test2(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite floyd_suite =
        CU_add_suite("Warshall-Floyd Algorithm Test", NULL, NULL);
    if (floyd_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(floyd_suite, "Warshall_Floyd_Test1", floyd_test1);
    CU_add_test(floyd_suite, "Warshall_Floyd_Test2", floyd_test2);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void set_external_variables1(int **input) {
    const int N = 6;
    const int M = INT_MAX;
    int temp[6][6] = {
        {0, M, M, 8, 15, M},
        {10, 0, 24, M, 8, M},
        {M, M, 0, M, M, 6},
        {M, M, M, 0, 5, M},
        {M, M, 12, M, 0, 7},
        {M, M, 3, M, M, 0}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            input[i][j] = temp[i][j];
        }
    }
}

void set_external_variables2(int **input) {
    const int N = 6;
    const int M = INT_MAX;
    int temp[6][6] = {
        {0, 12, 7, M, M, M},
        {12, 0, 9, 3, M, M},
        {7, 9, 0, 10, 4, M},
        {M, 3, 10, 0, 2, 8},
        {M, M, 4, 2, 0, 6},
        {M, M, M, 8, 6, 0}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            input[i][j] = temp[i][j];
        }
    }
}                              

void floyd_test1() {
    const int N = 6;
    const int M = INT_MAX;
    int **input = (int **)malloc(sizeof(int *) * N);
    int **output = (int **)malloc(sizeof(int *) * N);
    int **path = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        input[i] = (int *)malloc(sizeof(int) * N);
        output[i] = (int *)malloc(sizeof(int) * N);
        path[i] = (int *)malloc(sizeof(int ) * N);
    }

    int output_expected[6][6] = {
        {0, M, 23, 8, 13, 20},
        {10, 0, 18, 18, 8, 15},
        {M, M, 0, M, M, 6},
        {M, M, 15, 0, 5, 12},
        {M, M, 10, M, 0, 7},
        {M, M, 3, M, M, 0},
    };
    char *path_expected[6][6] = {
        {"0", "Nothing", "0 3 4 5 2", "0 3", "0 3 4", "0 3 4 5"},
        {"1 0", "1", "1 4 5 2", "1 0 3", "1 4", "1 4 5"},
        {"Nothing", "Nothing", "2", "Nothing", "Nothing", "2 5"},
        {"Nothing", "Nothing", "3 4 5 2", "3", "3 4", "3 4 5"},
        {"Nothing", "Nothing", "4 5 2", "Nothing", "4", "4 5"},
        {"Nothing", "Nothing", "5 2", "Nothing", "Nothing", "5"}
    };
    set_external_variables1(input);

    floyd(input, output, N, &path);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char temp[100];
            path_to_string(path, i, j, temp);
            CU_ASSERT_EQUAL(strcmp(temp, path_expected[i][j]), 0);
        }
        CU_ASSERT_EQUAL(memcmp(output[i], output_expected[i], sizeof(int) * N), 0);
    }

    for (int i = 0; i < N; i++) {
        free(input[i]);
        free(output[i]);
        free(path[i]);
    }
    free(input);
    free(output);
    free(path);
}

void floyd_test2() {
    const int N = 6;
    int **input = (int **)malloc(sizeof(int *) * N);
    int **output = (int **)malloc(sizeof(int *) * N);
    int **path = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        input[i] = (int *)malloc(sizeof(int) * N);
        output[i] = (int *)malloc(sizeof(int) * N);
        path[i] = (int *)malloc(sizeof(int ) * N);
    }

    int output_expected[6][6] = {
        {0, 12, 7, 13, 11, 17},
        {12, 0, 9, 3, 5, 11},
        {7, 9, 0, 6, 4, 10},
        {13, 3, 6, 0, 2, 8},
        {11, 5, 4, 2, 0, 6},
        {17, 11, 10, 8, 6, 0}
    };
    char *path_expected[6][6] = {
        {"0", "0 1", "0 2", "0 2 4 3", "0 2 4", "0 2 4 5"},
        {"1 0", "1", "1 2", "1 3", "1 3 4", "1 3 5"},
        {"2 0", "2 1", "2", "2 4 3", "2 4", "2 4 5"},
        {"3 4 2 0", "3 1", "3 4 2", "3", "3 4", "3 5"},
        {"4 2 0", "4 3 1", "4 2", "4 3", "4", "4 5"},
        {"5 4 2 0", "5 3 1", "5 4 2", "5 3", "5 4", "5"}
    };
    set_external_variables2(input);

    floyd(input, output, N, &path);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char temp[100];
            path_to_string(path, i, j, temp);
            CU_ASSERT_EQUAL(strcmp(temp, path_expected[i][j]), 0);
        }
        CU_ASSERT_EQUAL(memcmp(output[i], output_expected[i], sizeof(int) * N), 0);
    }
}
