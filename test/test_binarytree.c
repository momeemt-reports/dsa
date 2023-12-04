#include "test_binarytree.h"

int main(void) {
    CU_initialize_registry();

    CU_pSuite binarytree_suite = CU_add_suite("Binarytree Test", NULL, NULL);
    if (binarytree_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(binarytree_suite, "Binarytree_Test_Preorder",
                binarytree_test_preorder);
    CU_add_test(binarytree_suite, "Binarytree_Test_Inorder",
                binarytree_test_inorder);
    CU_add_test(binarytree_suite, "Binarytree_Test_Postorder",
                binarytree_test_postorder);
    CU_add_test(binarytree_suite, "Binarytree_Test_Display",
                binarytree_test_display);
    CU_add_test(binarytree_suite, "Binarytree_Test_Breadth_First",
                binarytree_test_breadth_first);
    CU_add_test(binarytree_suite, "Binarytree_Test_Height",
                binarytree_test_height);
    CU_add_test(binarytree_suite, "Binarytree_Test_Create_Mirror",
                binarytree_test_create_mirror);
    CU_add_test(binarytree_suite, "Binarytree_Test_Are_Mirrors_True",
                binarytree_test_are_mirrors_true);
    CU_add_test(binarytree_suite, "Binarytree_Test_Are_Mirrors_False",
                binarytree_test_are_mirrors_false);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

Node *create_tree_for_test(void) {
    Node *i = create_tree("I", NULL, NULL);
    Node *h = create_tree("H", NULL, NULL);
    Node *g = create_tree("G", NULL, NULL);
    Node *d = create_tree("D", NULL, NULL);
    Node *e = create_tree("E", NULL, i);
    Node *f = create_tree("F", h, g);
    Node *c = create_tree("C", d, e);
    Node *b = create_tree("B", f, NULL);
    Node *a = create_tree("A", c, b);

    return a;
}

Node *create_mirror_tree_for_test(void) {
    Node *d = create_tree("D", NULL, NULL);
    Node *i = create_tree("I", NULL, NULL);
    Node *h = create_tree("H", NULL, NULL);
    Node *g = create_tree("G", NULL, NULL);
    Node *e = create_tree("E", i, NULL);
    Node *f = create_tree("F", g, h);
    Node *c = create_tree("C", e, d);
    Node *b = create_tree("B", NULL, f);
    Node *a = create_tree("A", b, c);

    return a;
}

void binarytree_test_preorder(void) {
    Node *tree = create_tree_for_test();
    char buffer[1024] = "";
    binarytree_to_string_by_preorder(tree, buffer);
    CU_ASSERT_STRING_EQUAL("A C D E I B F H G", buffer);
    delete_tree(tree);
}

void binarytree_test_inorder(void) {
    Node *tree = create_tree_for_test();
    char buffer[1024] = "";
    binarytree_to_string_by_inorder(tree, buffer);
    CU_ASSERT_STRING_EQUAL("D C E I A H F G B", buffer);
    delete_tree(tree);
}

void binarytree_test_postorder(void) {
    Node *tree = create_tree_for_test();
    char buffer[1024] = "";
    binarytree_to_string_by_postorder(tree, buffer);
    CU_ASSERT_STRING_EQUAL("D I E C H G F B A", buffer);
    delete_tree(tree);
}

void binarytree_test_display(void) {
    Node *tree = create_tree_for_test();
    char buffer[1024] = "";
    binarytree_to_string(tree, buffer);
    CU_ASSERT_STRING_EQUAL(
        "A(C(D(null,null),E(null,I(null,null))),B(F(H(null,null),G(null,null)),"
        "null))",
        buffer);
    delete_tree(tree);
}

void binarytree_test_breadth_first(void) {
    Node *tree = create_tree_for_test();
    char buffer[1024] = "";
    binarytree_to_string_by_breadth_first(tree, buffer);
    CU_ASSERT_STRING_EQUAL("A C B D E F I H G", buffer);
    delete_tree(tree);
}

void binarytree_test_height(void) {
    Node *tree = create_tree_for_test();
    CU_ASSERT_EQUAL(height(tree), 4);
    delete_tree(tree);
}

void binarytree_test_create_mirror(void) {
    Node *tree = create_tree_for_test();
    Node *mirror = create_mirror(tree);
    char buffer[1024] = "";
    binarytree_to_string_by_preorder(mirror, buffer);
    CU_ASSERT_STRING_EQUAL("A B F G H C E I D", buffer);
    delete_tree(tree);
    delete_tree(mirror);
}

void binarytree_test_are_mirrors_true(void) {
    Node *tree = create_tree_for_test();
    Node *mirror = create_mirror_tree_for_test();
    CU_ASSERT_TRUE(are_mirrors(tree, mirror));
    delete_tree(tree);
    delete_tree(mirror);
}

void binarytree_test_are_mirrors_false(void) {
    Node *tree1 = create_tree_for_test();
    Node *tree2 = create_tree("J", NULL, create_tree_for_test());
    CU_ASSERT_FALSE(are_mirrors(tree1, tree2));
    delete_tree(tree1);
    delete_tree(tree2);
}
