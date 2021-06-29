/*
 * Calculate the frequency of each character from file.
 */

#include <stdio.h>

#include "freq.h"

size_t read_buff(char *buff, FILE *input) {
  size_t i = 0;
  while((buff[i] = fgetc(input)) != EOF) {
    i++;
  }
  return i;
}

void get_freq(char *buff, size_t size) {
  size_t i;
  for(i = 0; i < size; i++) {
    freq[(int) buff[i]]++;
  }
}
