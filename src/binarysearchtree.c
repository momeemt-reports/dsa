#include "binarysearchtree.h"

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

void insert_bst(Node **root, int d) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = d;
    new_node->left = NULL;
    new_node->right = NULL;

    if (*root == NULL) {
        *root = new_node;
    } else {
        Node *current = *root;
        Node *parent = NULL;

        while (true) {
            parent = current;
            if (d < parent->value) {
                current = current->left;
                if (current == NULL) {
                    parent->left = new_node;
                    return;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = new_node;
                    return;
                }
            }
        }
    }
}

void delete_bst(Node **root, int d) {
    Node *parent = NULL;
    Node *current = *root;
    Node *temp = NULL;

    while (current != NULL && current->value != d) {
        parent = current;
        if (d < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return;
    }

    if (current->left == NULL && current->right == NULL) {
        if (current != *root) {
            if (parent->left == current) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            *root = NULL;
        }
        free(current);
    } else if (current->left && current->right) {
        temp = current->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        temp->left = current->left;

        if (current != *root) {
            if (parent->left == current) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
        } else {
            *root = current->right;
        }
        free(current);
    } else {
        if (current->left != NULL) {
            temp = current->left;
        } else {
            temp = current->right;
        }

        if (current != *root) {
            if (parent->left == current) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
        } else {
            *root = temp;
        }
        free(current);
    }
}

void binarysearchtree_to_string_by_inorder(Node *root, char *buffer) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        binarysearchtree_to_string_by_inorder(root->left, buffer);
    }
    char value[12];
    sprintf(value, "%d ", root->value);
    strcat(buffer, value);
    if (root->right != NULL) {
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
    sprintf(buffer + strlen(buffer), "%d(", root->value);
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
