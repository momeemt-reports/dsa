#ifndef _TEST_BINARYTREE_H_
#define _TEST_BINARYTREE_H_

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "binarytree.h"

void binarytree_test_preorder(void);
void binarytree_test_inorder(void);
void binarytree_test_postorder(void);
void binarytree_test_display(void);
void binarytree_test_breadth_first(void);
void binarytree_test_height(void);
void binarytree_test_create_mirror(void);
void binarytree_test_are_mirrors_true(void);
void binarytree_test_are_mirrors_false(void);

#endif  // _TEST_BINARYTREE_H_
