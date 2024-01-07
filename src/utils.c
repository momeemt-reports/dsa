#include "utils.h"

void utils_swap(int *n, int *m) {
    int temp = *n;
    *n = *m;
    *m = temp;
}
