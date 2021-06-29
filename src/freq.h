#ifndef __FREQ_H
#define __FREQ_H

#define MAX_BUFF 1000000

size_t freq[128]; /* ASCII table contains 128 characters */

size_t read_buff(char *buff, FILE *input);
void get_freq(char *buff, size_t size);

#endif
