#include "readFile.h"

int readFile(char* path, char* str) {
  FILE* fp = fopen(path, "r");
  if ((fp == NULL) || (str == NULL)) {
    perror("Cannot not open file");
    exit(1);
  }

  int len = 0;
  while (!feof(fp)) {
    str[len++] = (char)fgetc(fp);
  }
  fclose(fp);
  str[--len] = '\0';
  return len;
}

