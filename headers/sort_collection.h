#ifndef _SORT_COLLECTION_H_ 
#define _SORT_COLLECTION_H_ 

extern unsigned long compare_count;
extern unsigned long swap_count;

void cmp_cnt_reset(void);
void swap_cnt_reset(void);
void display(int a[], int n);
void selection_sort(int a[], int n);
void insertion_sort(int a[], int n);
void heap_sort(int a[], int n);
void q_sort(int a[], int n);
void radix_sort(int a[], int n, int k);
void sift_down(int a[], int i, int n);
void build_heap(int a[], int n);
int partition(int a[], int pivot, int left, int right);

#endif  // _SORT_COLLECTION_H_ 

