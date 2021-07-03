#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "huffman.h"

void read_buff(char *buff, FILE *input) {
  size_t i = 0;
  while((buff[i] = fgetc(input)) != EOF) {
    i++;
  }
}

void get_freq(char *buff, size_t size) {
  size_t i = 0;
  for(i = 0; i < size; i++) {
    freq[(int) buff[i]]++;
  }
}

char *convert(char *buff, size_t size, int *nnulls) { 
  char huff[MAX_BUFF]; /* convert from ASCII codes to Huffman codes */
  int i, tmp = 0, pos = 0;
  for(i = 0; i < size; i++) {
    tmp = snprintf(huff + pos, MAX_BUFF - pos, "%s", ans[buff[i]]);
    pos += tmp;
  }
  if(pos % 7 != 0) {
    *nnulls = 8 - pos % 7;
    for(i = pos; i < pos + 7 - pos % 7 + 1; i++) {
      snprintf(huff + i, MAX_BUFF - i, "0");
    }
  }
  else {
    *nnulls = 0;
  }
  pos = 0;
  char *huff_ascii = (char *) malloc(sizeof(char) * MAX_BUFF); /* represent each 8 bits with ASCII character */
  for(i = 0; i <= strlen(huff) - 7; i += 7) {
    char substr[9];
    substr[0] = '0';
    memcpy(substr + 1, &huff[i], 7);
    substr[8] = '\0';
    char *strptr;
    tmp = snprintf(huff_ascii + pos, MAX_BUFF - pos, "%c", (char) strtol(substr, &strptr, 2));
    pos += tmp; 
  }
  return huff_ascii;
}

void tochar(int a, char *buff, size_t size) {
  long long mask = 0x80000000;
  int pos = 0, tmp = 0;
  while(mask > 0) {
    tmp = snprintf(buff + pos, size - pos, "%d", (a& mask) > 0);
    pos += tmp;
    mask >>= 1;
  }
}

void write_buff(int nchar, int nnulls, char *buff, FILE *output) {
  fprintf(output, "%c", (unsigned char) nchar);
  for(int i = 0; i < 128; i++) {
    if(strcmp(ans[i], "\0")) {
      char substr[33];
      tochar(freq[i], substr, 33);
      int c[4];
      int k = 0;
      for(int i = 0; i <= 24; i += 8, k++) {
        char tmp[9];
        memcpy(tmp, &substr[i], 8);
        tmp[8] = '\0';
        char *ptr;
        c[k] = strtol(tmp, &ptr, 2);
      }
      //fprintf(output, "%c%c", (unsigned char) i, (unsigned char) freq[i]);
      fprintf(output, "%c%c%c%c%c", (unsigned char) i, c[3], c[2], c[1], c[0]);
    }
  }
  /*fprintf(output, "%d ", strlen(buff));
  for(int i = 0; i < strlen(buff); i++) {
    if(buff[i] != '\0')fprintf(output, "%c", buff[i]);

  }*/
}

