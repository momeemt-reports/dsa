#include "fibonacci.h"

int called_fibonacci = 0;

int fibonacci_recursive(int n) {
  called_fibonacci++;
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
  }
}
