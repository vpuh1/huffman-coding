#ifndef __IO_H
#define __IO_H

#define MAX_BUFF 1000000

char ans[128][16];

void chartobin(char a, char *buff, size_t size);
int read_buffer(char *buff, FILE *input, int *nnulls);
char *convert(char *buff, size_t size, int nnulls);

#endif
