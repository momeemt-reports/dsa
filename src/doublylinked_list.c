#include "doublylinked_list.h"

DoublyLinkedListCell *CreateCell(int d, bool is_head) {
    DoublyLinkedListCell *p =
        (DoublyLinkedListCell *)malloc(sizeof(DoublyLinkedListCell));
    p->data = d;
    p->is_head = is_head;
    if (is_head) {
        p->prev = p;
        p->next = p;
    } else {
        p->prev = NULL;
        p->next = NULL;
        printf(
            "Cell with data %d has been created but is not yet linked to a "
            "bi-directional circular list.\n",
            d);
    }
    return p;
}

void InsertNext(DoublyLinkedListCell *this_cell, DoublyLinkedListCell *p) {
    if (this_cell == NULL || p == NULL) return;

    DoublyLinkedListCell *next = this_cell->next;

    this_cell->next = p;
    p->prev = this_cell;

    p->next = next;
    next->prev = p;
}

void InsertPrev(DoublyLinkedListCell *this_cell, DoublyLinkedListCell *p) {
    if (this_cell == NULL || p == NULL) return;

    DoublyLinkedListCell *prev = this_cell->prev;

    this_cell->prev = p;
    p->next = this_cell;

    p->prev = prev;
    prev->next = p;
}

void DeleteCell(DoublyLinkedListCell *this_cell) {
    if (this_cell == NULL || this_cell->is_head) return;

    DoublyLinkedListCell *prev = this_cell->prev;
    DoublyLinkedListCell *next = this_cell->next;

    prev->next = next;
    next->prev = prev;

    free(this_cell);
}

void DeleteAllCells(DoublyLinkedListCell *this_cell) {
    if (this_cell == NULL || !this_cell->is_head) return;

    DoublyLinkedListCell *p = this_cell->next;
    while (p != this_cell) {
        DoublyLinkedListCell *target = p;
        p = p->next;
        free(target);
    }
    free(this_cell);
}

DoublyLinkedListCell *SearchCell(DoublyLinkedListCell *this_cell, int d) {
    if (this_cell == NULL) return NULL;
    DoublyLinkedListCell *p = this_cell->next;
    while (p != this_cell) {
        if (p->data == d) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void doublylinked_list_to_string(DoublyLinkedListCell *this_cell,
                                 char *buffer) {
    if (this_cell == NULL || !this_cell->is_head) return;

    DoublyLinkedListCell *p = this_cell->next;
    while (p != this_cell) {
        sprintf(buffer + strlen(buffer), "[%d]", p->data);
        if (p->next != this_cell) {
            sprintf(buffer + strlen(buffer), "<->");
        }
        p = p->next;
    }
}

void Display(DoublyLinkedListCell *this_cell) {
    char buffer[1024] = "";
    doublylinked_list_to_string(this_cell, buffer);
    printf("%s\n", buffer);
}
