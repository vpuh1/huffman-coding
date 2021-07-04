#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "huffman.h"

void read_buff(char *buff, FILE *input) {
  size_t i = 0;
  while((buff[i] = fgetc(input)) != EOF)
    i++;
}

void get_freq(char *buff, size_t size) {
  size_t i = 0;
  for(i = 0; i < size; i++)
    freq[(int) buff[i]]++;
}

void encode(char *buff, char *res, int size) {
  int i, tmp = 0, pos = 0;
  for(i = 0; i < size; i++) {
    tmp = snprintf(res + pos, size - pos, "%s", ans[buff[i]]);
    pos += tmp;
  }
}

char *convert(char *buff, size_t size, int *mod) {
  char huff[MAX_BUFF]; /* convert from ASCII codes to Huffman codes */
  
  encode(buff, huff, MAX_BUFF);

  if(strlen(huff) % 8 != 0)
    *mod = 8 - strlen(huff) % 8;
  else
    *mod = 0;

  char *huff_ascii = (char *) malloc(sizeof(char) * MAX_BUFF); 
  int i, tmp = 0, pos = 0;
  char substr[9], *strptr;
  for(i = 0; i <= strlen(huff) - 8 - *mod; i += 8) {
    memcpy(substr, &huff[i], 8);
    substr[8] = '\0';
    tmp = snprintf(huff_ascii + pos, MAX_BUFF - pos, "%c",
                   (char) strtol(substr, &strptr, 2));
    pos += tmp; 
  }
  /* gen last byte*/
  for(int j = 0; j < *mod; j++)
    substr[j] = '0';
  memcpy(substr + *mod, &huff[i], 8 - *mod);
  substr[8] = '\0';
  tmp = snprintf(huff_ascii + pos, MAX_BUFF - pos, "%c", 
                 (char) strtol(substr, &strptr, 2));

  return huff_ascii;
}

void inttochar(int a, char *buff, size_t size) {
  long long mask = 0x80000000;
  int pos = 0, tmp = 0;
  while(mask > 0) {
    tmp = snprintf(buff + pos, size - pos, "%d", (a & mask) > 0);
    pos += tmp;
    mask >>= 1;
  }
}

void write_buff(int nchar, int nnulls, char *buff, FILE *output) {
  fprintf(output, "%c", (unsigned char) nchar);
  for(int i = 0; i < 128; i++) {
    if(strcmp(ans[i], "\0")) {
      char substr[33];
      inttochar(freq[i], substr, 33);
      substr[32] = '\0';
      int b[4];
      int k = 0;
      for(int i = 0; i <= 24; i += 8, k++) {
        char tmp[9];
        memcpy(tmp, &substr[i], 8);
        tmp[8] = '\0';
        char *ptr;
        b[k] = strtol(tmp, &ptr, 2);
      }
      fprintf(output, "%c", (unsigned char) i);
      fprintf(output, "%c%c%c%c", (unsigned char) b[3], (unsigned char) b[2], 
              (unsigned char) b[1], (unsigned char) b[0]);
    }
  }
  for(int i = 0; i < strlen(buff); i++)
    fprintf(output, "%c", buff[i]);
}

