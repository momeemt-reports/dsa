#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "bst_advanced.h"

void bst_advanced_test_1(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite bst_advanced_suite =
        CU_add_suite("BST Advanced Test", NULL, NULL);
    if (bst_advanced_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(bst_advanced_suite, "BST_Advanced_Test_1", bst_advanced_test_1);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void bst_advanced_test_1(void) {}
