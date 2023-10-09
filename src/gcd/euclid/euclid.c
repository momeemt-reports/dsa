#include "gcd.h"

int gcd_euclid(int n, int m) {
    while (n != m) {
        if (n > m) {
            n -= m;
        } else {
            m -= n;
        }
    }
    return n;
}

int gcd_recursive(int n, int m) {
    int r = n % m;
    if (r == 0) {
        return m;
    }
    return gcd_recursive(m, r);   
}
