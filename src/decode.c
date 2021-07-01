#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freq.h"
#include "huffman.h"

//write(buffer, sizeof(buffer), 1, file);

void convert(int pos, char *input, int ninput, char *output, int noutput) { /* converts text using Huffman coding from one buffer to another */
  int i;
  int tmp = 0;
  for(i = 0; i < ninput; i++) {
    tmp = snprintf(output + pos, noutput - pos, "%s", ans[input[i]]);
    pos += tmp;
  }
  if(strlen(output) % 8 != 0) {
    int tmp = (int) strlen(output);
    for(i = tmp - 1; i < tmp + 8 - tmp % 8; i++) {
      snprintf(output + i, noutput - i, "0");
    }
  }
}

void form_buff(char *input, int ninput, char *output, int noutput, int nchar) {
  int i;
  //int pos = snprintf(buff, nbuff, "%d", nchar);
  int pos = 0;
  if(!(pos >= 0 && pos < noutput)) {
    fprintf(stderr, "./huffman: cannot write write data to the buffer\n");
    return;
  }
  for(i = 0; i < 128; i++) {
    if(strcmp(ans[i], "\0")) {
      //printf("%s\n", ans[i]);
      int tmp = snprintf(output + pos, noutput - pos, "%c %s ", (char) i, ans[i]);
      pos += tmp;
    }
  }
  char tmpbuff[MAX_BUFF];
  convert(0, input, ninput, tmpbuff, MAX_BUFF);
  for(int i = 0; i <= strlen(tmpbuff) - 8; i += 8) {
    char tmp_strtol[9];
    memcpy(tmp_strtol, &tmpbuff[i], 8);
    tmp_strtol[8] = '\0';
    char *strptr;
    long int lol = strtol(tmp_strtol, &strptr, 2);
    int tmpp = snprintf(output + pos, noutput - pos, "%c", (char) lol);
    pos += tmpp;
  }
  //snprintf(output + pos, noutput - pos, "%s", tmpbuff);
}
