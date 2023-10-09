#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

#include "gcd/euclid/euclid.h"

void gcd_euclid_test_1(void);
void gcd_euclid_test_2(void);
void gcd_euclid_test_3(void);

int main(void) {
    CU_pSuite gcd_euclid_suite;
    CU_initialize_registry();

    gcd_euclid_suite = CU_add_suite("GCD Euclid Test", NULL, NULL);
    CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_1", gcd_euclid_test_1);
    CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_2", gcd_euclid_test_2);
    CU_add_test(gcd_euclid_suite, "GCD_Euclid_Test_3", gcd_euclid_test_3);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
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
    CU_ASSERT_EQUAL(2, result);
    return;
}
