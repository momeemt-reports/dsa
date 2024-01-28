#include "cmp.h"

bool cmp(char a, char b) {
  if (isVerbose) {
    fprintf(stderr, "cmp(%c, %c)\n", a, b);
  }

  Ncmp++;
  return a == b;
}
