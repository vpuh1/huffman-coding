#ifndef __IO_H
#define __IO_H

#define MAX_BUFF 1000000

size_t freq[128];

void read_buff(char *buff, FILE *input);
void get_freq(char *buff, size_t size);
void tochar(int a, char *buff, size_t size);
char *convert(char *buff, size_t size, int *nnulls);
void write_buff(int nchar, int nnulls, char *buff, FILE *output);

#endif
