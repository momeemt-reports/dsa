#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell {
    int data;
    struct cell *next;
} Cell;

extern Cell *head;

void insert_cell(Cell *p, int d);
void insert_cell_top(int d);
void delete_cell(Cell *p);
void delete_cell_top(void);
void delete_all_cells(void);
void linked_list_to_string(char *buffer);
void display_linked_list(void);

#endif  // __LINKED_LIST_H__
