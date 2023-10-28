#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct cell {
  int data;
  struct cell *next;
} Cell;

extern Cell *head;

void insert_cell(Cell *p, int d);
void insert_cell_top(int d);
void delete_cell(Cell *p);
void delete_cell_top(void);
void display(void);

#endif // __LINKED_LIST_H__
