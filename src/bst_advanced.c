#include "bst_advanced.h"

Node *create_tree(int value, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->left = left;
    node->right = right;
    node->height = 1;
    return node;
}

int min_bst(Node *root) {
    if (root == NULL) {
        return -1;
    }
    if (root->left == NULL) {
        return root->value;
    }
    return min_bst(root->left);
}

bool search_bst(Node *root, int d) {
    if (root == NULL) {
        return false;
    }
    if (root->value == d) {
        return true;
    }
    if (root->value < d) {
        return search_bst(root->right, d);
    }
    return search_bst(root->left, d);
}

int get_height(Node *root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->height;
    }
}

int reset_height(Node *root) {
    int lh = get_height(root->left);
    int rh = get_height(root->right);
    return 1 + (lh > rh ? lh : rh);
}

Node *insert_bst(Node *root, int d) {
    if (root == NULL) {
        return create_tree(d, NULL, NULL);
    }
    if (d < root->value) {
        root->left = insert_bst(root->left, d);
    } else if (d > root->value) {
        root->right = insert_bst(root->right, d);
    }
    root->height = reset_height(root);

    return root;
}

Node *delete_min_bst(Node *root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL) {
        Node *right = root->right;
        free(root);
        return right;
    }

    root->left = delete_min_bst(root->left);
    root->height = reset_height(root);
    return root;
}

Node *delete_bst(Node *root, int d) {
    if (root == NULL) {
        return NULL;
    }

    if (d < root->value) {
        root->left = delete_bst(root->left, d);
    } else if (d > root->value) {
        root->right = delete_bst(root->right, d);
    } else {
        if (root->left == NULL) {
            Node *right = root->right;
            free(root);
            return right;
        } else if (root->right == NULL) {
            Node *left = root->left;
            free(root);
            return left;
        }

        root->value = min_bst(root->right);
        root->right = delete_min_bst(root->right);
    }

    root->height = reset_height(root);
    return root;
}

void binarysearchtree_to_string_by_inorder(Node *root, char *buffer) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        binarysearchtree_to_string_by_inorder(root->left, buffer);
        sprintf(buffer + strlen(buffer), " ");
    }
    char value[12];
    sprintf(value, "%d", root->value);
    strcat(buffer, value);
    if (root->right != NULL) {
        sprintf(buffer + strlen(buffer), " ");
        binarysearchtree_to_string_by_inorder(root->right, buffer);
    }
}

void inorder(Node *root) {
    char buffer[1024] = "";
    binarysearchtree_to_string_by_inorder(root, buffer);
    printf("%s\n", buffer);
}

void binarysearchtree_to_string(Node *root, char *buffer) {
    if (root == NULL) {
        sprintf(buffer + strlen(buffer), "null");
        return;
    }
    sprintf(buffer + strlen(buffer), "%d#%d(", root->value, root->height);
    binarysearchtree_to_string(root->left, buffer);
    sprintf(buffer + strlen(buffer), ",");
    binarysearchtree_to_string(root->right, buffer);
    sprintf(buffer + strlen(buffer), ")");
}

void display(Node *root) {
    char buffer[1024] = "";
    binarysearchtree_to_string(root, buffer);
    printf("%s\n", buffer);
}

void delete_tree(Node *root) {
    if (root != NULL) {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}
