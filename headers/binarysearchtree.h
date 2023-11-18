#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;

int min_bst(Node *root);
bool search_bst(Node *root, int d);
void insert_bst(Node **root, int d);
void delete_bst(Node **root, int d);

void inorder(Node *root);
void display(Node *root);
void delete_tree(Node *root);

void binarysearchtree_to_string_by_inorder(Node *root, char *buffer);
void binarysearchtree_to_string(Node *root, char *buffer);

#endif  // _BINARYSEARCHTREE_H_
