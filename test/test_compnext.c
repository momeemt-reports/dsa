#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "compnext.h"

void compnext_test1();

int main(void) {
    CU_initialize_registry();

    CU_pSuite compnext_suite = CU_add_suite("Comp Next Test", NULL, NULL); 
    if (compnext_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(compnext_suite, "Comp_Next_Test_1", compnext_test1);
    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void compnext_test1() {
    char *pat = "ababc";
    int next[5] = { 0 };
    compnext(pat, next);
    int expected[5] = { 0, 1, 0, 1, 3 };
    CU_ASSERT_EQUAL(memcmp(next, expected, sizeof(expected)), 0);
}
