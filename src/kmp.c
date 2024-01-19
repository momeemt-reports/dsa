#include "kmp.h"

int kmp(char *text, unsigned textlen, char *pat, unsigned patlen) {
    int i = 0;
    int j = 0;
    int next[patlen];
    compnext(pat, next);
    while (j < (int)textlen) {
        while (i >= 0 && pat[i] != text[j]) {
            i = next[i] - 1;
        }
        if (i != (int)patlen - 1) {
            i++;
            j++;
        } else {
            return j - patlen + 1;
        }
    }
    return -1;
}
