#include <stdio.h>
#include <string.h>

#include "io.h"

int main(int argc, char **argv) {
  if(argc != 3) {
    printf("usage: huffman-decoder <input file> <output file>\n");
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen(argv[1], "r");

  if(!input) {
    fprintf(stderr, "huffman-decoder: cannot open %s\n", argv[1]);
    return 1;
  }
  if(!output) {
    fprintf(stderr, "huffman-decoder: cannot open %s\n", argv[2]);
    return 1;
  }

  char buff[MAX_BUFF];
  read_buffer(buff, input);
  for(int i = 0; i < 128; i++) {
    if(strcmp(ans[i], "\0")) {
      printf("%c %s\n", (char) i, ans[i]);
    }
  }

  fclose(input);
  fclose(output);
}
