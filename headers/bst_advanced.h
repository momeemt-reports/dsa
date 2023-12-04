#ifndef _BST_ADVANCED_H_
#define _BST_ADVANCED_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    int height;
    struct node *left;
    struct node *right;
} Node;

// advanced bst-specific functions
Node *insert_bst(Node *root, int d);
Node *delete_bst(Node *root, int d);

// Reuse the following functions implemented for the binarytree and
// binarysearchtree
int min_bst(Node *root);
bool search_bst(Node *root, int d);
void inorder(Node *root);
void display(Node *root);
void delete_tree(Node *root);

void binarysearchtree_to_string(Node *root, char *buffer);
void binarysearchtree_to_string_by_inorder(Node *root, char *buffer);

#endif  // _BST_ADVANCED_H_
