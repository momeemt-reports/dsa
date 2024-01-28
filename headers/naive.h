#ifndef naive_H
#define naive_H

#include <stdlib.h>
#include <stdbool.h>
#include "cmp.h"

extern bool isVerbose;
extern int Ncmp;

int naive(char* text, unsigned int textlen, char* pat, unsigned int patlen);

#endif // naive_H
