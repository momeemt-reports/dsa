#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node {
    char *label;
    struct node *left;
    struct node *right;
} Node;

Node *create_tree(char *label, Node *left, Node *right);
void preorder(Node *n);
void inorder(Node *n);
void postorder(Node *n);
void display(Node *n);
void breadth_first_search(Node *n);
int height(Node *n);
Node *create_mirror(Node *n);
bool are_mirrors(Node *n0, Node *n1);
void delete_tree(Node *n);

void binarytree_to_string_by_preorder(Node *n, char *buffer);
void binarytree_to_string_by_inorder(Node *n, char *buffer);
void binarytree_to_string_by_postorder(Node *n, char *buffer);
void binarytree_to_string(Node *n, char *buffer);
void binarytree_to_string_by_breadth_first(Node *n, char *buffer);

#endif  // _BINARYTREE_H_
