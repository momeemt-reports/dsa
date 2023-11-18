#include "binarytree.h"

Node *create_tree(char *label, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->label = label;
    node->left = left;
    node->right = right;
    return node;
}

void binarytree_to_string_by_preorder(Node *n, char *buffer) {
    if (n == NULL) {
        return;
    }
    sprintf(buffer + strlen(buffer), "%s", n->label);
    if (n->left != NULL) {
        sprintf(buffer + strlen(buffer), " ");
        binarytree_to_string_by_preorder(n->left, buffer);
    }
    if (n->right != NULL) {
        sprintf(buffer + strlen(buffer), " ");
        binarytree_to_string_by_preorder(n->right, buffer);
    }
}

void preorder(Node *n) {
    char buffer[1024] = "";
    binarytree_to_string_by_preorder(n, buffer);
    printf("%s\n", buffer);
}

void binarytree_to_string_by_inorder(Node *n, char *buffer) {
    if (n == NULL) {
        return;
    }
    if (n->left != NULL) {
        binarytree_to_string_by_inorder(n->left, buffer);
        sprintf(buffer + strlen(buffer), " ");
    }
    sprintf(buffer + strlen(buffer), "%s", n->label);
    if (n->right != NULL) {
        sprintf(buffer + strlen(buffer), " ");
        binarytree_to_string_by_inorder(n->right, buffer);
    }
}

void inorder(Node *n) {
    char buffer[1024] = "";
    binarytree_to_string_by_inorder(n, buffer);
    printf("%s\n", buffer);
}

void binarytree_to_string_by_postorder(Node *n, char *buffer) {
    if (n == NULL) {
        return;
    }
    if (n->left != NULL) {
        binarytree_to_string_by_postorder(n->left, buffer);
        sprintf(buffer + strlen(buffer), " ");
    }
    if (n->right != NULL) {
        binarytree_to_string_by_postorder(n->right, buffer);
        sprintf(buffer + strlen(buffer), " ");
    }
    sprintf(buffer + strlen(buffer), "%s", n->label);
}

void postorder(Node *n) {
    char buffer[1024] = "";
    binarytree_to_string_by_postorder(n, buffer);
    printf("%s\n", buffer);
}

void binarytree_to_string(Node *n, char *buffer) {
    if (n == NULL) {
        sprintf(buffer + strlen(buffer), "null");
        return;
    }
    sprintf(buffer + strlen(buffer), "%s(", n->label);
    binarytree_to_string(n->left, buffer);
    sprintf(buffer + strlen(buffer), ",");
    binarytree_to_string(n->right, buffer);
    sprintf(buffer + strlen(buffer), ")");
}

void display(Node *n) {
    char buffer[1024] = "";
    binarytree_to_string(n, buffer);
    printf("%s\n", buffer);
}

unsigned int size_binary_tree_node(Node *n) {
    if (n == NULL) {
        return 0;
    }
    return 1 + size_binary_tree_node(n->left) + size_binary_tree_node(n->right);
}

void binarytree_to_string_by_breadth_first(Node *n, char *buffer) {
    if (n == NULL) {
        return;
    }

    Queue *queue = create_queue(size_binary_tree_node(n), sizeof(Node *));
    if (!enqueue(queue, &n)) {
        exit(1);
    }

    while (!is_empty_queue(queue)) {
        int level_size = size_queue(queue);
        for (int i = 0; i < level_size; i++) {
            Node *current;
            if (!dequeue(queue, &current)) {
                exit(1);
            }

            sprintf(buffer + strlen(buffer), "%s", current->label);
            if (i != level_size - 1) {
                sprintf(buffer + strlen(buffer), " ");
            }

            if (current->left != NULL) {
                if (!enqueue(queue, &(current->left))) {
                    exit(1);
                }
            }
            if (current->right != NULL) {
                if (!enqueue(queue, &(current->right))) {
                    exit(1);
                }
            }
        }
        if (!is_empty_queue(queue)) {
            sprintf(buffer + strlen(buffer), " ");
        }
    }

    delete_queue(queue);
}

void breadth_first_search(Node *n) {
    char buffer[1024] = "";
    binarytree_to_string_by_breadth_first(n, buffer);
    printf("%s\n", buffer);
}

int height(Node *n) {
    if (n == NULL) {
        return 0;
    }
    int left_height = height(n->left);
    int right_height = height(n->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

Node *create_mirror(Node *n) {
    if (n == NULL) {
        return NULL;
    }
    return create_tree(n->label, create_mirror(n->right),
                       create_mirror(n->left));
}

bool are_mirrors(Node *n0, Node *n1) {
    if (n0 == NULL || n1 == NULL) {
        return n0 == NULL && n1 == NULL;
    }
    return (strcmp(n0->label, n1->label) == 0) &&
           are_mirrors(n0->left, n1->right) && are_mirrors(n0->right, n1->left);
}

void delete_tree(Node *n) {
    if (n != NULL) {
        delete_tree(n->left);
        delete_tree(n->right);
        free(n);
    }
}
