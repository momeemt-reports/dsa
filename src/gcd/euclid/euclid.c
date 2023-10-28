#include "gcd.h"
#include "utils.h"

int gcd_euclid(int n, int m) {
    if (n < 0) n = -n;
    if (m < 0) m = -m;
    while (m != 0) {
        int r = n % m;
        n = m;
        m = r;
        printf("n: %d, m: %d, r: %d\n", n, m, r);
    }
    return n;
}

int gcd_recursive(int n, int m) {
    if (n < 0) n = -n;
    if (m < 0) m = -m;
    int r = n % m;
    if (r == 0) return m;
    return gcd_recursive(m, r);
}
