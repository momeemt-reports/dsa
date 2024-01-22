#include "kmp.h"
#include "cmp.h"

int kmp(char *text, unsigned textlen, char *pat, unsigned patlen) {
    int i = 0;
    int j = 0;
    int next[patlen];
    memset(next, 0, patlen * sizeof(int));
    compnext(pat, next);
    while (j < (int)textlen) {
        while (i >= 0 && i < (int)patlen && cmp(text[j], pat[i])) {
            i++;
            j++;
            if (i == (int)patlen) {
                return j - i;
            }
        }

        if (i > 0) {
            i = next[i - 1];
        } else {
            j++;
        }
    }
    return -1;
}
