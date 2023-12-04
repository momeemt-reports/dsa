#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "binarysearchtree.h"

void binary_search_tree_test_insert(void);
void binary_search_tree_test_search_root_data(void);
void binary_search_tree_test_search_leaf_data(void);
void binary_search_tree_test_search_node_data(void);
void binary_search_tree_test_search_nonexistent_data(void);
void binary_search_tree_test_minimum_search_for_empty_tree(void);
void binary_search_tree_test_minimum_search(void);
void binary_search_tree_test_delete_leaf(void);
void binary_search_tree_test_delete_one_child(void);
void binary_search_tree_test_delete_two_children(void);
void binary_search_tree_test_delete_root(void);
void binary_search_tree_test_delete_nonexistent(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite binary_search_tree_suite =
        CU_add_suite("Binary Search Tree Test", NULL, NULL);
    if (binary_search_tree_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(binary_search_tree_suite, "Binary_Search_Tree_Test_Insert",
                binary_search_tree_test_insert);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Search_Root_Data",
                binary_search_tree_test_search_root_data);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Search_Leaf_Data",
                binary_search_tree_test_search_leaf_data);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Search_Node_Data",
                binary_search_tree_test_search_node_data);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Nonexistent_Data",
                binary_search_tree_test_search_nonexistent_data);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Minimum_Search_For_Empty_Tree",
                binary_search_tree_test_minimum_search_for_empty_tree);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Minimum_Search",
                binary_search_tree_test_minimum_search);
    CU_add_test(binary_search_tree_suite, "Binary_Search_Tree_Test_Delete_Leaf",
                binary_search_tree_test_delete_leaf);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Delete_One_Child",
                binary_search_tree_test_delete_one_child);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Delete_Two_Children",
                binary_search_tree_test_delete_two_children);
    CU_add_test(binary_search_tree_suite, "Binary_Search_Tree_Test_Delete_Root",
                binary_search_tree_test_delete_root);
    CU_add_test(binary_search_tree_suite,
                "Binary_Search_Tree_Test_Delete_Nonexistent",
                binary_search_tree_test_delete_nonexistent);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

Node *create_tree_for_test(void) {
    Node *root = NULL;
    insert_bst(&root, 10);
    insert_bst(&root, 15);
    insert_bst(&root, 18);
    insert_bst(&root, 6);
    insert_bst(&root, 12);
    insert_bst(&root, 20);
    insert_bst(&root, 9);

    return root;
}

Node *create_empty_tree_for_test(void) {
    Node *root = NULL;
    return root;
}

void binary_search_tree_test_insert(void) {
    Node *root = create_tree_for_test();
    char buffer[1024] = "";
    binarysearchtree_to_string(root, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10(6(null,9(null,null)),15(12(null,null),18(null,20(null,null))))",
        buffer);
    delete_tree(root);
}

void binary_search_tree_test_search_root_data(void) {
    Node *root = create_tree_for_test();
    CU_ASSERT_TRUE(search_bst(root, 10));
    delete_tree(root);
}

void binary_search_tree_test_search_leaf_data(void) {
    Node *root = create_tree_for_test();
    CU_ASSERT_TRUE(search_bst(root, 9));
    delete_tree(root);
}

void binary_search_tree_test_search_node_data(void) {
    Node *root = create_tree_for_test();
    CU_ASSERT_TRUE(search_bst(root, 15));
    delete_tree(root);
}

void binary_search_tree_test_search_nonexistent_data(void) {
    Node *root = create_tree_for_test();
    CU_ASSERT_FALSE(search_bst(root, 11));
    delete_tree(root);
}

void binary_search_tree_test_minimum_search_for_empty_tree(void) {
    Node *root = create_empty_tree_for_test();
    CU_ASSERT_EQUAL(min_bst(root), -1);
    delete_tree(root);
}

void binary_search_tree_test_minimum_search(void) {
    Node *root = create_tree_for_test();
    CU_ASSERT_EQUAL(min_bst(root), 6);
    delete_tree(root);
}

void binary_search_tree_test_delete_leaf(void) {
    Node *root = create_tree_for_test();
    delete_bst(&root, 9);
    char buffer[1024] = "";
    binarysearchtree_to_string(root, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10(6(null,null),15(12(null,null),18(null,20(null,null))))", buffer);
    delete_tree(root);
}

void binary_search_tree_test_delete_one_child(void) {
    Node *root = create_tree_for_test();
    delete_bst(&root, 6);
    char buffer[1024] = "";
    binarysearchtree_to_string(root, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10(9(null,null),15(12(null,null),18(null,20(null,null))))", buffer);
    delete_tree(root);
}

void binary_search_tree_test_delete_two_children(void) {
    Node *root = create_tree_for_test();
    delete_bst(&root, 15);
    char buffer[1024] = "";
    binarysearchtree_to_string(root, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10(6(null,9(null,null)),18(12(null,null),20(null,null)))", buffer);
    delete_tree(root);
}

void binary_search_tree_test_delete_root(void) {
    Node *root = create_tree_for_test();
    delete_bst(&root, 10);
    char buffer[1024] = "";
    binarysearchtree_to_string(root, buffer);
    CU_ASSERT_STRING_EQUAL(
        "15(12(6(null,9(null,null)),null),18(null,20(null,null)))", buffer);
    delete_tree(root);
}

void binary_search_tree_test_delete_nonexistent(void) {
    Node *root = create_tree_for_test();
    delete_bst(&root, 100);
    char buffer[1024] = "";
    binarysearchtree_to_string(root, buffer);
    CU_ASSERT_STRING_EQUAL(
        "10(6(null,9(null,null)),15(12(null,null),18(null,20(null,null))))",
        buffer);
    delete_tree(root);
}
