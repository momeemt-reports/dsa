#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <string.h>

#include "sort_collection.h"
#include "timer.h"

void insertion_sort_test(void);
void heap_sort_test(void);
void quick_sort_test(void);
void test_sort_compare_count(void);
void test_sort_speed(void);
void worst_quick_sort_test(void);
void radix_sort_test(void);
void sift_down_test(void);
void build_heap_test(void);
void partition_test(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite sort_suite =
        CU_add_suite("Sort Test", NULL, NULL);
    if (sort_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    /* CU_add_test(sort_suite, "Insertion_Sort_Test", */
    /*             insertion_sort_test); */
    /* CU_add_test(sort_suite, "Heap_Sort_Test", */
    /*             heap_sort_test); */
    /* CU_add_test(sort_suite, "Quick_Sort_Test", */
    /*             quick_sort_test); */
    CU_add_test(sort_suite, "Radix_Sort_Test",
                radix_sort_test);
    /* CU_add_test(sort_suite, "Sift_Down_Test", */
    /*             sift_down_test); */
    /* CU_add_test(sort_suite, "Build_Heap_Test", */
    /*             build_heap_test); */
    /* CU_add_test(sort_suite, "Partition_Test", */
    /*             partition_test); */

    char *dsa_output_graph_env = getenv("DSA_OUTPUT_GRAPH");
    if (dsa_output_graph_env != NULL) {
      test_sort_compare_count();
      test_sort_speed();
      worst_quick_sort_test();
    }

    CU_basic_run_tests();
    unsigned int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return (int)ret;
}

void sift_down_test(void) {
    const int arr_size = 7;
    int arr1[arr_size] = { 5, 2, 4, 6, 1, 3, 7 };
    int arr2[arr_size] = { 5, 2, 7, 6, 1, 3, 4 };
    sift_down(arr1, arr_size / 2 - 1, arr_size);
    for (int i = 0; i < arr_size; i++) {
      printf("%d ", arr1[i]);
    }
    CU_ASSERT_EQUAL(0, memcmp(arr1, arr2, sizeof(arr1)));
}

void build_heap_test(void) {
    const int arr_size = 7;
    int arr1[arr_size] = { 5, 2, 4, 6, 1, 3, 7 };
    int arr2[arr_size] = { 7, 6, 5, 2, 1, 3, 4 };
    build_heap(arr1, arr_size);
    CU_ASSERT_EQUAL(0, memcmp(arr1, arr2, sizeof(arr1)));
}

void partition_test(void) {
    const int arr_size = 7;
    int arr1[arr_size] = { 5, 2, 4, 6, 1, 3, 7 };
    int pivot = partition(arr1, 4, 0, arr_size - 1);
    CU_ASSERT_EQUAL(3, pivot);
}

void insertion_sort_test(void) {
    const int arr_size = 7;
    int arr1[arr_size] = { 5, 2, 4, 6, 1, 3, 7 };
    int arr2[arr_size] = { 1, 2, 3, 4, 5, 6, 7 };
    cmp_cnt_reset();
    swap_cnt_reset();
    insertion_sort(arr1, arr_size);
    printf("compare_count: %lu\n", compare_count);
    printf("swap_count: %lu\n", swap_count);
    CU_ASSERT_EQUAL(0, memcmp(arr1, arr2, sizeof(arr1)));
}

void heap_sort_test(void) {
    const int arr_size = 7;
    int arr1[arr_size] = { 5, 2, 4, 6, 1, 3, 7 };
    int arr2[arr_size] = { 1, 2, 3, 4, 5, 6, 7 };
    cmp_cnt_reset();
    swap_cnt_reset();
    heap_sort(arr1, arr_size);
    printf("compare_count: %lu\n", compare_count);
    printf("swap_count: %lu\n", swap_count);
    CU_ASSERT_EQUAL(0, memcmp(arr1, arr2, sizeof(arr1)));
}

void quick_sort_test(void) {
    const int arr_size = 7;
    int arr1[arr_size] = { 5, 2, 4, 6, 1, 3, 7 };
    int arr2[arr_size] = { 1, 2, 3, 4, 5, 6, 7 };
    cmp_cnt_reset();
    swap_cnt_reset();
    q_sort(arr1, arr_size);
    printf("compare_count: %lu\n", compare_count);
    printf("swap_count: %lu\n", swap_count);
    CU_ASSERT_EQUAL(0, memcmp(arr1, arr2, sizeof(arr1)));
}

void output_graph_compare_count(char *name, char *title, int *heap_sort_compare_count_data, int *quick_sort_compare_count_data) {
  char *now = (char *)malloc(sizeof(char) * 20);
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  strftime(now, 20, "%Y%m%d%H%M%S", tm);

  FILE *gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set terminal jpeg size 512, 512\n");
  fprintf(gp, "set output \"./test/graph/%s_%s.jpeg\"\n", name, now);

  fprintf(gp, "set title \"%s\"\n", title);
  fprintf(gp, "set xlabel \"numdata\"\n");
  fprintf(gp, "set ylabel \"compare count\"\n");
  fprintf(gp, "set xrange [1000:10000]\n");
  fprintf(gp, "set yrange [0:*]\n");
  fprintf(gp, "set size square\n");
  fprintf(gp, "set xtics rotate by -45 font \",8\"\n");

  fprintf(gp, "plot '-' with lines title \"Heap Sort\", '-' with lines title \"Quick Sort\"\n");
  
  for (int i = 0; i < 10; i++) {
    int numdata = (i + 1) * 1000;
    fprintf(gp, "%d %d\n", numdata, heap_sort_compare_count_data[i]);
  }
  fprintf(gp, "e\n");

  for (int i = 0; i < 10; i++) {
    int numdata = (i + 1) * 1000;
    fprintf(gp, "%d %d\n", numdata, quick_sort_compare_count_data[i]);
  }
  fprintf(gp, "e\n");

  fflush(gp);
  pclose(gp);
  free(now);
}

void test_sort_compare_count(void) {
  const int RANDOM_SEED = 19;
  srand(RANDOM_SEED);
  int *heap_sort_compare_count_data = (int *)malloc(sizeof(int) * 10);
  int *quick_sort_compare_count_data = (int *)malloc(sizeof(int) * 10);
  for (int numdata = 1000; numdata <= 10000; numdata += 1000) {
    int *heap_sort_data = malloc(sizeof(int) * numdata);
    int *quick_sort_data = malloc(sizeof(int) * numdata);
    for (int i = 0; i < numdata; i++) {
      heap_sort_data[i] = rand();
    }
    memcpy(quick_sort_data, heap_sort_data, sizeof(int) * numdata);
    cmp_cnt_reset();
    heap_sort(heap_sort_data, numdata);
    heap_sort_compare_count_data[numdata / 1000 - 1] = compare_count;
    cmp_cnt_reset();
    q_sort(quick_sort_data, numdata);
    quick_sort_compare_count_data[numdata / 1000 - 1] = compare_count;
  }
  output_graph_compare_count("sort_compare_count", "Sort Compare Count", heap_sort_compare_count_data, quick_sort_compare_count_data);
}

void output_graph_time(char *name, char *title, double *time_data) {
  char *now = (char *)malloc(sizeof(char) * 20);
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  strftime(now, 20, "%Y%m%d%H%M%S", tm);

  FILE *gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set terminal jpeg size 512, 512\n");
  fprintf(gp, "set output \"./test/graph/%s_%s.jpeg\"\n", name, now);

  fprintf(gp, "set title \"%s\"\n", title);
  fprintf(gp, "set xlabel \"Sort Algorithm\"\n");
  fprintf(gp, "set ylabel \"time [sec]\"\n");
  fprintf(gp, "set style data histogram\n");
  fprintf(gp, "set style histogram cluster gap 1\n");
  fprintf(gp, "set style fill solid border -1\n");
  fprintf(gp, "set boxwidth 0.9\n");
  fprintf(gp, "set xtics format \"\" nomirror\n");
  fprintf(gp, "set xtics ('Heap Sort' 0, 'Quick Sort' 1)\n");

  fprintf(gp, "plot '-' using 2:xtic(1) title ''\n");
  fprintf(gp, "\"Heap Sort\" %lf\n", time_data[0]);
  fprintf(gp, "\"Quick Sort\" %lf\n", time_data[1]);
  fprintf(gp, "e\n");

  fflush(gp);
  pclose(gp);
  free(now);
}

void test_sort_speed(void) {
  const int RANDOM_SEED = 19;
  const int TRY_NUMBER = 10;
  const int NUM_DATA = 200000;
  Timer *timer = new_timer();

  double heap_sort_time_total = 0.0;
  double quick_sort_time_total = 0.0;

  for (int try = 0; try < TRY_NUMBER; try++) {
    int *heap_sort_data = malloc(sizeof(int) * NUM_DATA);
    int *quick_sort_data = malloc(sizeof(int) * NUM_DATA);
    srand(RANDOM_SEED);
    for (int i = 0; i < NUM_DATA; i++) {
      heap_sort_data[i] = rand();
    }
    memcpy(quick_sort_data, heap_sort_data, sizeof(int) * NUM_DATA);

    timer->reset(timer);
    timer->start(timer);
    heap_sort(heap_sort_data, NUM_DATA);
    timer->stop(timer);
    heap_sort_time_total += timer->result(timer);

    timer->reset(timer);
    timer->start(timer);
    q_sort(quick_sort_data, NUM_DATA);
    timer->stop(timer);
    quick_sort_time_total += timer->result(timer);

    free(heap_sort_data);
    free(quick_sort_data);
  }

  double heap_sort_time_avg = heap_sort_time_total / TRY_NUMBER;
  double quick_sort_time_avg = quick_sort_time_total / TRY_NUMBER;

  double time_data[2] = {heap_sort_time_avg, quick_sort_time_avg};
  output_graph_time("sort_time", "Sort Time", time_data);
}

void worst_array_for_quick_sort(int *data, int n) {
  for (int i = 0; i < n/2; i++) {
    data[i] = i;
  }
  for (int i = n/2; i < n; i++) {
    data[i] = n - i - 1;
  }
}

void output_graph_worst_sort(char *name, char *title, int *compare_data) {
  char *now = (char *)malloc(sizeof(char) * 20);
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  strftime(now, 20, "%Y%m%d%H%M%S", tm);

  FILE *gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set terminal jpeg size 512, 512\n");
  fprintf(gp, "set output \"./test/graph/%s_%s.jpeg\"\n", name, now);

  fprintf(gp, "set title \"%s\"\n", title);
  fprintf(gp, "set xlabel \"Sort Algorithm\"\n");
  fprintf(gp, "set ylabel \"compare count\"\n");
  fprintf(gp, "set logscale y\n");
  fprintf(gp, "set style data histogram\n");
  fprintf(gp, "set style histogram cluster gap 1\n");
  fprintf(gp, "set style fill solid border -1\n");
  fprintf(gp, "set boxwidth 0.9\n");
  fprintf(gp, "set xtics rotate by -45 font \",8\"\n");
  fprintf(gp, "set xtics ('Heap Sort' 0, 'Quick Sort' 1)\n");

  fprintf(gp, "plot '-' using 2:xtic(1) title ''\n");
  fprintf(gp, "\"Quick Sort (Random)\" %d\n", compare_data[2]);
  fprintf(gp, "\"Quick Sort (Worst)\" %d\n", compare_data[3]);
  fprintf(gp, "\"Heap Sort (Random)\" %d\n", compare_data[0]);
  fprintf(gp, "\"Heap Sort (Worst)\" %d\n", compare_data[1]);
  fprintf(gp, "e\n");

  fflush(gp);
  pclose(gp);
  free(now);
}

void worst_quick_sort_test(void) {
  const int size = 10000;

  int *random_quick_sort_data = malloc(sizeof(int) * size);
  int *random_heap_sort_data = malloc(sizeof(int) * size);
  int *worst_quick_sort_data = malloc(sizeof(int) * size);
  int *worst_heap_sort_data = malloc(sizeof(int) * size);

  srand(19);
  for (int i = 0; i < size; i++) {
    random_quick_sort_data[i] = rand();
    random_heap_sort_data[i] = random_quick_sort_data[i];
  }
  worst_array_for_quick_sort(worst_quick_sort_data, size);
  memcpy(worst_heap_sort_data, worst_quick_sort_data, sizeof(int) * size);

  int *compare_data = malloc(sizeof(int) * 4);
  cmp_cnt_reset();
  heap_sort(random_heap_sort_data, size);
  compare_data[0] = compare_count;
  cmp_cnt_reset();
  heap_sort(worst_heap_sort_data, size);
  compare_data[1] = compare_count;
  cmp_cnt_reset();
  q_sort(random_quick_sort_data, size);
  compare_data[2] = compare_count;
  cmp_cnt_reset();
  q_sort(worst_quick_sort_data, size);
  compare_data[3] = compare_count;

  output_graph_worst_sort("worst_sort", "Worst Sort", compare_data);
  free(random_quick_sort_data);
}

void radix_sort_test(void) {
  const int arr_size = 8;
  int arr1[arr_size] = { 143, 322, 246, 755, 123, 563, 514, 522 };
  int arr2[arr_size] = { 123, 143, 246, 322, 514, 522, 563, 755 };
  cmp_cnt_reset();
  radix_sort(arr1, arr_size, 3);
  CU_ASSERT_EQUAL(0, memcmp(arr1, arr2, sizeof(arr1)));

  int arr3[10] = { 597, 198, 436, 333, 777, 125, 234, 124, 864, 200 };
  cmp_cnt_reset();
  radix_sort(arr3, 10, 3);
}
