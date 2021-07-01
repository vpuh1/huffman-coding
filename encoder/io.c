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

char *convert(char *buff, size_t size) { 
  char huff[MAX_BUFF]; /* convert from ASCII codes to Huffman codes */
  int i, tmp = 0, pos = 0;
  for(i = 0; i < size; i++) {
    tmp = snprintf(huff + pos, MAX_BUFF - pos, "%s", ans[buff[i]]);
    pos += tmp;
  }
  if(strlen(buff) % 8 != 0) {
    size_t bufflen = (int) strlen(buff);
    for(i = bufflen; i < bufflen + 8 - tmp % 8; i++) {
      snprintf(huff + i, MAX_BUFF - i, "0");
    }
  }
  pos = 0;
  char *huff_ascii = (char *) malloc(sizeof(char) * MAX_BUFF); /* represent each 8 bits with ASCII character */
  for(i = 0; i <= strlen(huff) - 8; i += 8) {
    char substr[9];
    memcpy(substr, &huff[i], 8);
    substr[8] = '\0';
    char *strptr;
    tmp = snprintf(huff_ascii + pos, MAX_BUFF - pos, "%c", (char) strtol(substr, &strptr, 2));
    pos += tmp; 
  }
  return huff_ascii;
}

void write_buff(int nchar, char *buff, FILE *output) {
  fprintf(output, "%d ", nchar);
  for(int i = 0; i < 128; i++) {
    if(strcmp(ans[i], "\0")) {
      fprintf(output, "%c %s ", (char) i, ans[i]);
    }
  }
  fprintf(output, "%s", buff);
}

