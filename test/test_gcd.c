#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

#include "gcd.h"

void gcd_iter_test_1(void);
void gcd_iter_test_2(void);
void gcd_iter_test_3(void);
void gcd_iter_test_4(void);
void gcd_iter_test_5(void);

void gcd_euclid_test_1(void);
void gcd_euclid_test_2(void);
void gcd_euclid_test_3(void);
void gcd_euclid_test_4(void);
void gcd_euclid_test_5(void);

void gcd_recursive_test_1(void);
void gcd_recursive_test_2(void);
void gcd_recursive_test_3(void);
void gcd_recursive_test_4(void);
void gcd_recursive_test_5(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite gcd_euclid_suite = CU_add_suite("GCD Euclid Test", NULL, NULL);
    if (gcd_euclid_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_1", gcd_euclid_test_1);
    // CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_2", gcd_euclid_test_2);
    // CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_3", gcd_euclid_test_3);
    // CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_4", gcd_euclid_test_4);
    // CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_5", gcd_euclid_test_5);

    CU_pSuite gcd_iter_suite = CU_add_suite("GCD Iter Test", NULL, NULL);
    if (gcd_iter_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(gcd_iter_suite, "GCD_Iter_Test_1", gcd_iter_test_1);
    // CU_add_test(gcd_iter_suite, "GCD_Iter_Test_2", gcd_iter_test_2);
    // CU_add_test(gcd_iter_suite, "GCD_Iter_Test_3", gcd_iter_test_3);
    // CU_add_test(gcd_iter_suite, "GCD_Iter_Test_4", gcd_iter_test_4);
    // CU_add_test(gcd_iter_suite, "GCD_Iter_Test_5", gcd_iter_test_5);

    CU_pSuite gcd_recursive_suite = CU_add_suite("GCD Recursive Test", NULL, NULL);
    if (gcd_recursive_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(gcd_recursive_suite, "GCD_Recursive_Test_1", gcd_recursive_test_1);
    // CU_add_test(gcd_recursive_suite, "GCD_Recursive_Test_2", gcd_recursive_test_2);
    // CU_add_test(gcd_recursive_suite, "GCD_Recursive_Test_3", gcd_recursive_test_3);
    // CU_add_test(gcd_recursive_suite, "GCD_Recursive_Test_4", gcd_recursive_test_4);
    // CU_add_test(gcd_recursive_suite, "GCD_Recursive_Test_5", gcd_recursive_test_5);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void gcd_euclid_test_1(void) {
    int result = gcd_euclid(18, 24);
    CU_ASSERT_EQUAL(6, result);
    return;
}

void gcd_euclid_test_2(void) {
    int result = gcd_euclid(7, 11);
    CU_ASSERT_EQUAL(1, result);
    return;
}

void gcd_euclid_test_3(void) {
    int result = gcd_euclid(2, 100);
    CU_ASSERT_EQUAL_FATAL(2, result);
    return;
}

void gcd_euclid_test_4(void) {
    int result = gcd_euclid(-3, 9);
    CU_ASSERT_EQUAL_FATAL(3, result);
    return;
}

void gcd_euclid_test_5(void) {
    int result = gcd_euclid(1836311903, 1134903170);
    CU_ASSERT_EQUAL(1, result);
    return;
}

void gcd_iter_test_1(void) {
    int result = gcd_iter(18, 24);
    CU_ASSERT_EQUAL(6, result);
    return;
}

void gcd_iter_test_2(void) {
    int result = gcd_iter(7, 11);
    CU_ASSERT_EQUAL(1, result);
    return;
}

void gcd_iter_test_3(void) {
    int result = gcd_iter(2, 100);
    CU_ASSERT_EQUAL(2, result);
    return;
}

void gcd_iter_test_4(void) {
    int result = gcd_iter(-3, 9);
    CU_ASSERT_EQUAL(3, result);
    return;
}

void gcd_iter_test_5(void) {
    int result = gcd_iter(1836311903, 1134903170);
    CU_ASSERT_EQUAL(1, result);
    return;
}

void gcd_recursive_test_1(void) {
    int result = gcd_recursive(18, 24);
    CU_ASSERT_EQUAL(6, result);
    return;
}

void gcd_recursive_test_2(void) {
    int result = gcd_recursive(7, 11);
    CU_ASSERT_EQUAL(1, result);
    return;
}

void gcd_recursive_test_3(void) {
    int result = gcd_recursive(2, 100);
    CU_ASSERT_EQUAL(2, result);
    return;
}

void gcd_recursive_test_4(void) {
    int result = gcd_recursive(-3, 9);
    CU_ASSERT_EQUAL(3, result);
    return;
}

void gcd_recursive_test_5(void) {
    int result = gcd_recursive(1836311903, 1134903170);
    CU_ASSERT_EQUAL(1, result);
    return;
}
