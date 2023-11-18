#include "linked_list.h"

Cell *head = NULL;

void insert_cell(Cell *p, int d) {
    Cell *new_cell = (Cell *)malloc(sizeof(Cell));
    new_cell->data = d;
    new_cell->next = p->next;
    p->next = new_cell;
}

void insert_cell_top(int d) {
    Cell *new_cell = (Cell *)malloc(sizeof(Cell));
    new_cell->data = d;
    new_cell->next = head;
    head = new_cell;
}

void delete_cell(Cell *p) {
    Cell *target = p->next;
    p->next = target->next;
    free(target);
}

void delete_cell_top(void) {
    Cell *target = head;
    head = head->next;
    free(target);
}

void delete_all_cells(void) {
    Cell *p = head;
    while (p != NULL) {
        Cell *target = p;
        p = p->next;
        free(target);
    }
    head = NULL;
}

void linked_list_to_string(char *buffer) {
    if (head == NULL) {
        sprintf(buffer, "Empty");
        return;
    }
    Cell *p = head;
    while (p != NULL) {
        sprintf(buffer + strlen(buffer), "[%d]", p->data);
        if (p->next != NULL) {
            sprintf(buffer + strlen(buffer), "->");
        }
        p = p->next;
    }
}

void display_linked_list(void) {
    char buffer[1024] = "";
    linked_list_to_string(buffer);
    printf("%s\n", buffer);
}
