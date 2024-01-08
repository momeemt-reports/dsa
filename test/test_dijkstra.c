#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "dijkstra.h"

void dijkstra_test1(void);
void dijkstra_test2(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite bst_advanced_suite =
        CU_add_suite("Dijkstra Algorithm Test", NULL, NULL);
    if (bst_advanced_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(bst_advanced_suite, "Dijkstra_Test1", dijkstra_test1);
    CU_add_test(bst_advanced_suite, "Dijkstra_Test2", dijkstra_test2);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

int w[N][N];
bool S[N];
int Scount;
int d[N];
int parent[N];

void set_external_variables1() {
    int w_temp[N][N] = {
        {0, M, M, 8, 15, M},
        {10, 0, 24, M, 8, M},
        {M, M, 0, M, M, 6},
        {M, M, M, 0, 5, M},
        {M, M, 12, M, 0, 7},
        {M, M, 3, M, M, 0}
    };

    for (int i = 0; i < N; i++) {
        S[i] = false;
        d[i] = M;
        parent[i] = -1;
        for (int j = 0; j < N; j++) {
            w[i][j] = w_temp[i][j];
        }
    }

    Scount = 0;
}

void set_external_variables2() {
    int w_temp[N][N] = {
        {0, 12, 7, M, M, M},
        {12, 0, 9, 3, M, M},
        {7, 9, 0, 10, 4, M},
        {M, 3, 10, 0, 2, 8},
        {M, M, 4, 2, 0, 6},
        {M, M, M, 8, 6, 0}
    };

    for (int i = 0; i < N; i++) {
        S[i] = false;
        d[i] = M;
        parent[i] = -1;
        for (int j = 0; j < N; j++) {
            w[i][j] = w_temp[i][j];
        }
    }

    Scount = 0;
}                              

void dijkstra_test1(void) {
    const int expected[6][6] = {
        {0, M, 23, 8, 13, 20},
        {10, 0, 18, 18, 8, 15},
        {M, M, 0, M, M, 6},
        {M, M, 15, 0, 5, 12},
        {M, M, 10, M, 0, 7},
        {M, M, 3, M, M, 0},
    };

    const char *expected_path[6][6] = {
        {"0", "Nothing", "0 3 4 5 2", "0 3", "0 3 4", "0 3 4 5"},
        {"1 0", "1", "1 4 5 2", "1 0 3", "1 4", "1 4 5"},
        {"Nothing", "Nothing", "2", "Nothing", "Nothing", "2 5"},
        {"Nothing", "Nothing", "3 4 5 2", "3", "3 4", "3 4 5"},
        {"Nothing", "Nothing", "4 5 2", "Nothing", "4", "4 5"},
        {"Nothing", "Nothing", "5 2", "Nothing", "Nothing", "5"}
    };
    
    for (int i = 0; i < N; i++) {
        set_external_variables1();
        dijkstra(i);
        for (int j = 0; j < N; j++) {
            char path[1000];
            get_shortest_path(parent, i, j, path);
            CU_ASSERT_EQUAL(strcmp(path, expected_path[i][j]), 0);
        }
        CU_ASSERT_EQUAL(memcmp(d, expected[i], sizeof(int) * 6), 0);
    }
}

void dijkstra_test2(void) {
    const int expected[6][6] = {
        {0, 12, 7, 13, 11, 17},
        {12, 0, 9, 3, 5, 11},
        {7, 9, 0, 6, 4, 10},
        {13, 3, 6, 0, 2, 8},
        {11, 5, 4, 2, 0, 6},
        {17, 11, 10, 8, 6, 0}
    };

    const char *expected_path[6][6] = {
        {"0", "0 1", "0 2", "0 2 4 3", "0 2 4", "0 2 4 5"},
        {"1 0", "1", "1 2", "1 3", "1 3 4", "1 3 5"},
        {"2 0", "2 1", "2", "2 4 3", "2 4", "2 4 5"},
        {"3 4 2 0", "3 1", "3 4 2", "3", "3 4", "3 5"},
        {"4 2 0", "4 3 1", "4 2", "4 3", "4", "4 5"},
        {"5 4 2 0", "5 3 1", "5 4 2", "5 3", "5 4", "5"}
    };

    for (int i = 0; i < N; i++) {
        set_external_variables2();
        dijkstra(i);
        for (int j = 0; j < N; j++) {
            char path[1000];
            get_shortest_path(parent, i, j, path);
            CU_ASSERT_EQUAL(strcmp(path, expected_path[i][j]), 0);
        }
        CU_ASSERT_EQUAL(memcmp(d, expected[i], sizeof(int) * 6), 0);
    };
}
