#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Cell *head = NULL;

void insert_cell(Cell *p, int d) {}

void insert_cell_top(int d) {
    Cell *new_cell = (Cell *)malloc(sizeof(Cell));
    new_cell->data = d;
    new_cell->next = head;
    head = new_cell;
}

void delete_cell(Cell *p) {}

void delete_cell_top(void) {}

void display(void) {}
