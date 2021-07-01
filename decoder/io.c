#include <stdio.h>

#include "io.h"

void read_buffer(char *buff, FILE *input) {
  int nchar;
  fscanf(input, "%d", &nchar); /* number of chars with non-zero frequency */
  int i;
  char x;
  for(i = 0; i < nchar; i++) {
    fscanf(input, "%c ", &x);
    fscanf(input, "%s ", ans[x]);
  }
}
