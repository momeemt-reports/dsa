#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "bst_advanced.h"

void bst_advanced_test_insert1(void);
void bst_advanced_test_inorder1(void);
void bst_advanced_test_search_existence1(void);
void bst_advanced_test_search_nonexistence1(void);
void bst_advanced_test_search_minimum1(void);
void bst_advanced_test_delete1(void);
void bst_advanced_test2(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite bst_advanced_suite =
        CU_add_suite("BST Advanced Test", NULL, NULL);
    if (bst_advanced_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(bst_advanced_suite, "BST_Advanced_Test_Insert1",
                bst_advanced_test_insert1);
    CU_add_test(bst_advanced_suite, "BST_Advanced_Test_Inorder1",
                bst_advanced_test_inorder1);
    CU_add_test(bst_advanced_suite, "BST_Advanced_Test_Search_Existence1",
                bst_advanced_test_search_existence1);
    CU_add_test(bst_advanced_suite, "BST_Advanced_Test_Search_Nonexistence1",
                bst_advanced_test_search_nonexistence1);
    CU_add_test(bst_advanced_suite, "BST_Advanced_Test_Search_Minimum1",
                bst_advanced_test_search_minimum1);
    CU_add_test(bst_advanced_suite, "BST_Advanced_Test_Delete1",
                bst_advanced_test_delete1);
    CU_add_test(bst_advanced_suite, "BST_Advanced_Test2", bst_advanced_test2);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

Node *create_tree_for_test1(void) {
    Node *root = NULL;
    root = insert_bst(root, 20);
    root = insert_bst(root, 10);
    root = insert_bst(root, 26);
    root = insert_bst(root, 14);
    root = insert_bst(root, 13);
    root = insert_bst(root, 5);
    return root;
}

Node *create_tree_for_test2(void) {
    Node *root = NULL;
    root = insert_bst(root, 10);
    root = insert_bst(root, 15);
    root = insert_bst(root, 18);
    root = insert_bst(root, 6);
    root = insert_bst(root, 12);
    root = insert_bst(root, 20);
    root = insert_bst(root, 19);
    root = insert_bst(root, 9);
    return root;
}

void bst_advanced_test_insert1(void) {
    Node *tree = create_tree_for_test1();
    char buffer[1024] = "";
    binarysearchtree_to_string(tree, buffer);
    CU_ASSERT_STRING_EQUAL(
        "20#4(10#3(5#1(null,null),14#2(13#1(null,null),null)),26#1(null,null))",
        buffer);
    delete_tree(tree);
}

void bst_advanced_test_inorder1(void) {
    Node *tree = create_tree_for_test1();
    char buffer[1024] = "";
    binarysearchtree_to_string_by_inorder(tree, buffer);
    CU_ASSERT_STRING_EQUAL("5 10 13 14 20 26", buffer);
    delete_tree(tree);
}

void bst_advanced_test_search_existence1(void) {
    Node *tree = create_tree_for_test1();
    CU_ASSERT_TRUE(search_bst(tree, 14));
    delete_tree(tree);
}

void bst_advanced_test_search_nonexistence1(void) {
    Node *tree = create_tree_for_test1();
    CU_ASSERT_FALSE(search_bst(tree, 7));
    delete_tree(tree);
}

void bst_advanced_test_search_minimum1(void) {
    Node *tree = create_tree_for_test1();
    CU_ASSERT_EQUAL(min_bst(tree), 5);
    delete_tree(tree);
}

void bst_advanced_test_delete1(void) {
    Node *tree = create_tree_for_test1();
    tree = delete_bst(tree, 10);

    char buffer[1024] = "";
    binarysearchtree_to_string(tree, buffer);
    CU_ASSERT_STRING_EQUAL(
        "20#3(13#2(5#1(null,null),14#1(null,null)),26#1(null,null))", buffer);

    buffer[0] = '\0';
    binarysearchtree_to_string_by_inorder(tree, buffer);
    CU_ASSERT_STRING_EQUAL("5 13 14 20 26", buffer);

    delete_tree(tree);
}

void bst_advanced_test2(void) {
    Node *tree = create_tree_for_test2();

    char buffer[1024] = "";
    binarysearchtree_to_string(tree, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10#5(6#2(null,9#1(null,null)),15#4(12#1(null,null),18#3(null,20#2(19#"
        "1(null,null),null))))",
        buffer);

    buffer[0] = '\0';
    tree = delete_bst(tree, 15);
    binarysearchtree_to_string(tree, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10#4(6#2(null,9#1(null,null)),18#3(12#1(null,null),20#2(19#1(null,"
        "null),null)))",
        buffer);

    buffer[0] = '\0';
    tree = delete_bst(tree, 19);
    binarysearchtree_to_string(tree, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10#3(6#2(null,9#1(null,null)),18#2(12#1(null,null),20#1(null,null)))",
        buffer);

    delete_tree(tree);
}
