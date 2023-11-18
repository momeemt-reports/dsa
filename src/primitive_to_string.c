#include "primitive_to_string.h"

void int_to_string(void *item, char *str) { sprintf(str, "%d", *(int *)item); }
