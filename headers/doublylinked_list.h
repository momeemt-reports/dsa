#ifndef __DOUBLYLINKED_LIST_H__
#define __DOUBLYLINKED_LIST_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell {
    int data;
    bool is_head;
    struct cell *prev;
    struct cell *next;
} DoublyLinkedListCell;

DoublyLinkedListCell *CreateCell(int d, bool is_head);
void InsertNext(DoublyLinkedListCell *this_cell, DoublyLinkedListCell *p);
void InsertPrev(DoublyLinkedListCell *this_cell, DoublyLinkedListCell *p);
void DeleteCell(DoublyLinkedListCell *this_cell);
void DeleteAllCells(DoublyLinkedListCell *this_cell);
DoublyLinkedListCell *SearchCell(DoublyLinkedListCell *this_cell, int d);
void doublylinked_list_to_string(DoublyLinkedListCell *this_cell, char *buffer);
void Display(DoublyLinkedListCell *this_cell);

#endif
