#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdbool.h>

#include "kmp.h"

void kmp_test_matching();
void kmp_test_mismatching();

int main(void) {
    CU_initialize_registry();

    CU_pSuite kmp_suite = CU_add_suite("KMP Method Test", NULL, NULL); 
    if (kmp_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(kmp_suite, "KMP_Test_Matching", kmp_test_matching);
    CU_add_test(kmp_suite, "naive_Test_Mismatch", kmp_test_mismatching);
    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

int Ncmp = 0;
bool isVerbose = false;

void kmp_test_matching() {
    char* text = "This is a pen.";
    char* pat = "pen";
    int textlen = strlen(text);
    int patlen = strlen(pat);
    int result = kmp(text, textlen, pat, patlen);
    CU_ASSERT_EQUAL(result, 10);
}

void kmp_test_mismatching() {
    char *text = "This is a pen.";
    char *pat = "ix";
    int textlen = strlen(text);
    int patlen = strlen(pat);
    int result = kmp(text, textlen, pat, patlen);
    CU_ASSERT_EQUAL(result, -1);
}
