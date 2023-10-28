#include "gcd.h"
#include "utils.h"

int gcd_iter(int n, int m) {
    if (n > m) {
        swap(&n, &m);
    }
    int gcd = 1;
    int i = 1;
    while (i <= n) {
        if (n % i == 0 && m % i == 0) {
            gcd = i;
        }
        i++;
        printf("n: %d, m: %d, i: %d, gcd: %d\n", n, m, i, gcd);
    }
    return gcd;
}
