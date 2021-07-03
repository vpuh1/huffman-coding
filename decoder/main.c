#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "io.h"

int main(int argc, char **argv) {
  if(argc != 3) {
    printf("usage: huffman-decoder <input file> <output file>\n");
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen(argv[2], "w");

  if(!input) {
    fprintf(stderr, "huffman-decoder: cannot open %s\n", argv[1]);
    return 1;
  }
  if(!output) {
    fprintf(stderr, "huffman-decoder: cannot open %s\n", argv[2]);
    return 1;
  }
  
  char buff[MAX_BUFF];
  int nnulls;
  int buff_size = read_buffer(buff, input, &nnulls);
  /*printf("%d\n", nnulls);
  for(int i = 0; i < 128; i++) {
    if(strcmp(ans[i], "\0")) {
      printf("%c %s\n", (char) i, ans[i]);
    }
  }*/
  printf("%d\n", strlen(buff));
  char *res = (char *) malloc(sizeof(char) * MAX_BUFF);
  res = convert(buff, buff_size, nnulls);
  if(res) {
    fprintf(output, "%s", res);
    free(res);
  }


  fclose(input);
  fclose(output);
}
