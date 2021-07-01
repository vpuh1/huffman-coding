#include <stdio.h>

#include "decode.h"

int main() {
  char buffer[2048];
  form_buff(buffer, 10);
  printf("%s\n", buffer);
}
