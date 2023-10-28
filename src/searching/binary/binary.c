#include "searching.h"

bool binary_search(int *array, int size, int value) {
    int low = 0;
    int high = size - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        if (array[mid] == value) {
            return true;
        } else if (value < array[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    printf("ans: %d\n", array[low]);
    if (array[low] == value) {
        return true;
    }
    return false;
}
