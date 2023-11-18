#include "bst_advanced.h"

int min_bst(Node *root) {}

bool search_bst(Node *root, int d) {}

int get_height(Node *root) {
    if (root == NULL)
        return 0;
    else
        return root->height;
}

int reset_height(Node *root) {
    int lh = get_height(root->left);
    int rh = get_height(root->right);
    return 1 + (lh > rh ? lh : rh);
}

Node *insert_bst(Node *root, int d) {}

Node *delete_min_bst(Node *root) {}

Node *delete_bst(Node *root, int d) {}

void inorder(Node *root) {}

void display(Node *root) {}

void delete_tree(Node *root) {}
