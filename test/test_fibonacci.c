#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

#include "fibonacci.h"

void fibonacci_recursive_test_1(void);
void fibonacci_recursive_test_2(void);
void fibonacci_recursive_test_3(void);

int main(void) {
    CU_initialize_registry();
    
    CU_pSuite fibonacci_recursive_suite = CU_add_suite("Fibonacci Recursive Test", NULL, NULL);
    if (fibonacci_recursive_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(fibonacci_recursive_suite, "Fibonacci_Recursive_Test_1", fibonacci_recursive_test_1);
    CU_add_test(fibonacci_recursive_suite, "Fibonacci_Recursive_Test_2", fibonacci_recursive_test_2);
    CU_add_test(fibonacci_recursive_suite, "Fibonacci_Recursive_Test_3", fibonacci_recursive_test_3);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void fibonacci_recursive_test_1(void) {
    called_fibonacci = 0;
    int result = fibonacci_recursive(3);
    CU_ASSERT_EQUAL(2, result);
    return;
}

void fibonacci_recursive_test_2(void) {
    called_fibonacci = 0;
    int result = fibonacci_recursive(4);
    CU_ASSERT_EQUAL(3, result);
    return;
}

void fibonacci_recursive_test_3(void) {
    called_fibonacci = 0;
    int result = fibonacci_recursive(5);
    CU_ASSERT_EQUAL(5, result);
    return;
}
