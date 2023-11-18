#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "linked_list.h"

void linked_list_test_1(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite linked_list_suite = CU_add_suite("Linked List Test", NULL, NULL);
    if (linked_list_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(linked_list_suite, "Linked_List_Test_1", linked_list_test_1);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

void setup_test_linked_list(void) {
    head = NULL;
    delete_all_cells();
}

// Test case corresponding to the presented `main_linked_list.c`
void linked_list_test_1(void) {
    setup_test_linked_list();

    insert_cell_top(1);
    insert_cell(head, 3);
    insert_cell(head, 2);

    char buffer[1024] = "";
    linked_list_to_string(buffer);
    CU_ASSERT_STRING_EQUAL("[1]->[2]->[3]", buffer);

    delete_cell(head);
    buffer[0] = '\0';
    linked_list_to_string(buffer);
    CU_ASSERT_STRING_EQUAL("[1]->[3]", buffer);

    delete_cell_top();
    buffer[0] = '\0';
    linked_list_to_string(buffer);
    CU_ASSERT_STRING_EQUAL("[3]", buffer);
}
