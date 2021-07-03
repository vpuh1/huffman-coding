#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "io.h"

void chartobin(char a, char *buff, size_t size) {
  int mask = 0x80, tmp = 0, pos = 0;
  while(mask > 0) {
    tmp = snprintf(buff + pos, size - pos, "%d", (a & mask) > 0);
    pos += tmp;
    mask >>= 1;
  }
}

int read_buffer(char *buff, FILE *input, int *nnulls) {
  int nchar;
  fscanf(input, "%d %d ", &nchar, nnulls);
  int i;
  int x;
  for(i = 0; i < nchar; i++) {
    fscanf(input, "%d ", &x);
    //x = fgetc(input);
    fscanf(input, " %s ", ans[x]);
    if(x == '\n')
      printf("%s\n", ans[x]);
  }
  int buff_size;
  fscanf(input, "%d ", &buff_size);
  for(i = 0; i < buff_size; i++) {
    buff[i] = fgetc(input);
  }
  return buff_size;
}

char *convert(char *buff, size_t size, int nnulls) {
  char *huff = (char *) malloc(sizeof(char) * MAX_BUFF);
  int i = 0, tmp = 0, pos = 0;
  printf("%d\n", size);
  for(i = 0; i < size; i++) {
    char *bin = (char *) malloc(sizeof(char) * 9);
    chartobin(buff[i], bin, 9);
    tmp = snprintf(huff + pos, MAX_BUFF - pos, "%s", bin + 1);
    pos += tmp;
    free(bin);
  }
  printf("%s\n", buff);
  for(i = 0; i < size * 8; i++) {
    printf("%c", huff[i]);
  }
  printf("\n");
  char *ascii = (char *) malloc(sizeof(char) * MAX_BUFF);
  int j;
  pos = 0, tmp = 0;
  for(i = 0; i < strlen(huff) - 8 - nnulls; i++) {
    for(j = 1; j <= strlen(huff) - 8 - i; j++) {
      char substr[j + 1];
      memcpy(substr, &huff[i], j);
      substr[j] = '\0';
      int found = 0;
      for(int k = 0; k < 128; k++) {
        if(!strcmp(substr, ans[k])) {
          i += (j - 1);
          tmp = snprintf(ascii + pos, MAX_BUFF - pos, "%c", (char) k);
          pos += tmp;
          found = 1;
          break;
        }
      }
      if(found)
        break;
    }
  }
  return ascii;
}
