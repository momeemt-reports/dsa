#include "naive.h"
#include "cmp.h"

int naive(char* text, unsigned int textlen, char* pat, unsigned int patlen) {
    int i = 0;
    int j = 0;
    while (j < (int)textlen) {
        if (!cmp(pat[i], text[j])) {
            j = j - i + 1;
            i = 0;
            continue;
        } else if (i == (int)patlen - 1) {
            return j - patlen + 1;
        }
        i++;
        j++;
    }
    return -1;
}
