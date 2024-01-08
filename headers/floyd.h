#ifndef FLOYD_H
#define FLOYD_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void floyd(int **input, int **output, unsigned int length, int ***path);
void path_to_string (int **path, int start, int end, char *output);

#endif  // FLOYD_H
