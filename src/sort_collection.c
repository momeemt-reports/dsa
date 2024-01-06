#include <stdio.h>
#include <stdlib.h>
#include "sort_collection.h"

unsigned long compare_count = 0;
unsigned long swap_count = 0;

void cmp_cnt_reset(void) {
  compare_count = 0;
}

void swap_cnt_reset(void) {
  swap_count = 0;
}

int compare(int ldata, int rdata) {
  compare_count++;

  char *dsa_debug_env = getenv("DSA_DEBUG");
  if (dsa_debug_env != NULL) {
    printf("compare: %d <-> %d\n", ldata, rdata);
  }

  if      (ldata  < rdata) return -1;
  else if (ldata == rdata) return  0;
  else                     return  1;
}

void swap(int a[], int lidx, int ridx, int n, int start) {
  swap_count++;
  int temp = a[lidx];
  a[lidx] = a[ridx];
  a[ridx] = temp;

  char *dsa_debug_env = getenv("DSA_DEBUG");
  if (dsa_debug_env != NULL) {
    printf("swap: %d([%d]) <-> %d([%d])\n", a[lidx], lidx, a[ridx], ridx);
    printf("n: %d\n", n);
    display(a + start, n);
    printf("--------------------\n");
  }
}

void display(int a[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void selection_sort(int a[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    int min = i;
    for (j = i + 1; j < n; j++) {
      if (compare(a[j], a[min]) == -1) {
        min = j;
      }
    }
    swap(a, i, min, n, n);
  }
}

void insertion_sort(int a[], int n) {
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0 && compare(a[j-1], a[j]) == 1; j--) {
      swap(a, j-1, j, n, 0);
    }
  }
}

void sift_down(int a[], int i, int n) {
  const int left = 2*i+1;
  const int right = 2*i+2;
  int largest = i;
  if (left < n && compare(a[left], a[largest]) == 1) {
    largest = left;
  }
  if (right < n && compare(a[right], a[largest]) == 1) {
    largest = right;
  }
  if (largest != i) {
    swap(a, i, largest, n, 0);
    sift_down(a, largest, n);
  }
}

void build_heap (int a[], int n) {
  for (int i = n/2-1; i >= 0; i--) {
    sift_down(a, i, n);
  }
}

void heap_sort (int a[], int n) {
  build_heap(a, n);
  for (int i = n-1; i > 0; i--) {
    swap(a, 0, i, n, 0);
    sift_down(a, 0, i);
  }
}

int partition(int a[], int pivot, int left, int right) {
  char *dsa_debug_env = getenv("DSA_DEBUG");
  if (dsa_debug_env != NULL) {
    printf("pivot: %d\n", pivot);
  }
  int l = left;
  int r = right;
  while (l <= r) {
    while (compare(a[l], pivot) == -1) {
      l++;
    }
    while (compare(a[r], pivot) == 1) {
      r--;
    }
    if (l <= r) {
      swap(a, l, r, right-left+1, left);
      l++;
      r--;
    }
  }
  return l;
}

void quick_sort(int a[], int left, int right, int n) {
  if (left < right) {
    int pivot = a[(left+right)/2];
    int index = partition(a, pivot, left, right);
    quick_sort(a, left, index-1, n);
    quick_sort(a, index, right, n);
  }
}

void q_sort(int a[], int n) {
  quick_sort(a, 0, n-1, n);
}

void radix_sort(int a[], int n, int k) {
  int *bucket = malloc(sizeof(int) * 10);
  int *tmp_bucket = malloc(sizeof(int) * n);
  int digit = 1;

  for (int i = 0; i < k; i++) {
    for (int j = 0; j < 10; j++) {
      bucket[j] = 0;
    }

    for (int j = 0; j < n; j++) {
      int index = (a[j] / digit) % 10;
      bucket[index]++;
    }

    for (int j = 1; j < 10; j++) {
      bucket[j] += bucket[j-1];
    }

    for (int j = n-1; j >= 0; j--) {
      int bucket_index = (a[j] / digit) % 10;
      int index = --bucket[bucket_index];
      tmp_bucket[index] = a[j];
    }

    for (int j = 0; j < n; j++) {
      a[j] = tmp_bucket[j];
    }

    digit *= 10;

    char *dsa_debug_env = getenv("DSA_DEBUG");
    if (dsa_debug_env != NULL) {
      printf("bucket: ");
      for (int j = 0; j < 9; j++) {
        printf("%d ", bucket[j]);
      }
      printf("%d\n", bucket[9]);
      printf("tmp_bucket: ");
      for (int j = 0; j < n; j++) {
        printf("%d ", tmp_bucket[j]);
      }
      printf("\n");
    }
  }

  free(tmp_bucket);
  free(bucket);
}

