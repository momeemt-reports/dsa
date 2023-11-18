#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "doublylinked_list.h"

void doublylinked_list_test_1(void);
void doublylinked_list_test_2(void);
void doublylinked_list_test_3(void);
void doublylinked_list_test_4(void);
void doublylinked_list_test_5(void);
void doublylinked_list_test_6(void);
void doublylinked_list_test_7(void);
void doublylinked_list_test_8(void);
void doublylinked_list_test_9(void);
void doublylinked_list_test_10(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite doublylinked_list_suite =
        CU_add_suite("Doubly Linked List Test", NULL, NULL);
    if (doublylinked_list_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_1",
                doublylinked_list_test_1);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_2",
                doublylinked_list_test_2);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_3",
                doublylinked_list_test_3);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_4",
                doublylinked_list_test_4);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_5",
                doublylinked_list_test_5);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_6",
                doublylinked_list_test_6);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_7",
                doublylinked_list_test_7);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_8",
                doublylinked_list_test_8);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_9",
                doublylinked_list_test_9);
    CU_add_test(doublylinked_list_suite, "Doubly_Linked_List_Test_10",
                doublylinked_list_test_10);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

// Test case where a cell can be inserted at the beginning of a list
void doublylinked_list_test_1(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);

    char buffer[1024] = "";
    doublylinked_list_to_string(head, buffer);
    CU_ASSERT_STRING_EQUAL("[1]", buffer);

    DeleteAllCells(head);
}

// Test case where a cell can be inserted in the middle of a list
void doublylinked_list_test_2(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(3, false);
    InsertPrev(head, q);
    DoublyLinkedListCell *r = CreateCell(2, false);
    InsertNext(p, r);

    char buffer[1024] = "";
    doublylinked_list_to_string(head, buffer);
    CU_ASSERT_STRING_EQUAL("[1]<->[2]<->[3]", buffer);

    DeleteAllCells(head);
}

// Test case where a cell can be inserted at the end of a list
void doublylinked_list_test_3(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertPrev(head, q);

    char buffer[1024] = "";
    doublylinked_list_to_string(head, buffer);
    CU_ASSERT_STRING_EQUAL("[1]<->[2]", buffer);

    DeleteAllCells(head);
}

// Test case where the first cell can be deleted
void doublylinked_list_test_4(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertPrev(head, q);

    DeleteCell(p);

    char buffer[1024] = "";
    doublylinked_list_to_string(head, buffer);
    CU_ASSERT_STRING_EQUAL("[2]", buffer);

    DeleteAllCells(head);
}

// Test case where the middle cell can be deleted
void doublylinked_list_test_5(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertNext(p, q);
    DoublyLinkedListCell *r = CreateCell(3, false);
    InsertPrev(head, r);

    DeleteCell(q);

    char buffer[1024] = "";
    doublylinked_list_to_string(head, buffer);
    CU_ASSERT_STRING_EQUAL("[1]<->[3]", buffer);

    DeleteAllCells(head);
}

// Test case where the last cell can be deleted
void doublylinked_list_test_6(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertPrev(head, q);

    DeleteCell(q);

    char buffer[1024] = "";
    doublylinked_list_to_string(head, buffer);
    CU_ASSERT_STRING_EQUAL("[1]", buffer);

    DeleteAllCells(head);
}

// Test case where dummy cells cannot be deleted
void doublylinked_list_test_7(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertPrev(head, q);

    DeleteCell(head);

    char buffer[1024] = "";
    doublylinked_list_to_string(head, buffer);
    CU_ASSERT_STRING_EQUAL("[1]<->[2]", buffer);

    DeleteAllCells(head);
}

// Test case where the first cell can be searched by `SearchCell`
void doublylinked_list_test_8(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertNext(p, q);
    DoublyLinkedListCell *r = CreateCell(3, false);
    InsertPrev(head, r);

    DoublyLinkedListCell *result = SearchCell(head, 1);
    CU_ASSERT_EQUAL(1, result->data);

    DeleteAllCells(head);
}

// Test case where the middle cell can be searched by `SearchCell`
void doublylinked_list_test_9(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertNext(p, q);
    DoublyLinkedListCell *r = CreateCell(3, false);
    InsertPrev(head, r);

    DoublyLinkedListCell *result = SearchCell(head, 2);
    CU_ASSERT_EQUAL(2, result->data);

    DeleteAllCells(head);
}

// Test case where `SearchCell` can search the last cell
void doublylinked_list_test_10(void) {
    DoublyLinkedListCell *head = CreateCell(0, true);
    DoublyLinkedListCell *p = CreateCell(1, false);
    InsertNext(head, p);
    DoublyLinkedListCell *q = CreateCell(2, false);
    InsertNext(p, q);
    DoublyLinkedListCell *r = CreateCell(3, false);
    InsertPrev(head, r);

    DoublyLinkedListCell *result = SearchCell(head, 3);
    CU_ASSERT_EQUAL(3, result->data);

    DeleteAllCells(head);
}
