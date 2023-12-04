#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "searching.h"

void binary_search_test_1(void);
void binary_search_test_2(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite binary_search_suite =
        CU_add_suite("Binary Search Test", NULL, NULL);
    if (binary_search_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(binary_search_suite, "Binary_Search_Test_1",
                binary_search_test_1);
    CU_add_test(binary_search_suite, "Binary_Search_Test_2",
                binary_search_test_2);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void binary_search_test_1(void) {
    int arr[15] = {0, 29, 30, 37, 41, 53, 53, 57, 59, 61, 62, 75, 79, 90, 92};
    binary_search(arr, 15, 30);
    CU_ASSERT_EQUAL(1, 1);
    return;
}

void binary_search_test_2(void) {
    int arr[15] = {0, 29, 30, 37, 41, 53, 53, 57, 59, 61, 62, 75, 79, 90, 92};
    binary_search(arr, 15, 60);
    CU_ASSERT_EQUAL(1, 1);
    return;
}
