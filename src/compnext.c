#include <string.h>
#include <stdio.h>

void compnext(char *pat, int *next) {
    int patlen = strlen(pat);
    for (int i = 1; i < patlen; i++) {
        for (int j = 0; j < (patlen - i); j++) {
            if (pat[i+j] != pat[j]) {
                if (next[i+j] < j + 1) {
                    next[i+j] = j + 1;
                }
                break;
            }
        }
    }
}
