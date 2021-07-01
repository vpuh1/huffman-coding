/* 
 * Simple Huffman coding implementation written in c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freq.h"
#include "huffman.h"
#include "decode.h"

void print(FILE *output) {
  fprintf(output, "char | frequency | Huffman code\n");
  for(int i = 0; i < 128; i++) {
    if(strcmp(ans[i], "\0")) {
      if((char) i == '\n')
        fprintf(output, "\\n | ");
      else
        fprintf(output, "%c | ", (char) i);
      fprintf(output, "%ld | %s\n", freq[i], ans[i]);
    }
  }
}

int main(int argc, char **argv) {
  if(argc != 3) {
    printf("usage: ./huffman <input file> <output file>\n");
    return 1;
  }
  
  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen(argv[2], "w");

  if(!input) {
    fprintf(stderr, "huffman: cannot open %s\n", argv[1]);
    return 1;
  }
  if(!output) {
    fprintf(stderr, "huffman: cannot open %s\n", argv[2]);
    return 1;
  }

  char buff[MAX_BUFF];
  size_t buff_size = read_buff(buff, input);
  get_freq(buff, buff_size);

  qnode *head = (qnode *) malloc(sizeof(qnode)); /* head for the queue */
  head->next = NULL;
  head->left = NULL;
  head->right = NULL;

  int is_head = 0;
  int nchar = 0;
  for(int i = 0; i < 128; i++) {
    if(freq[i] != 0) {
      nchar++;
      if(!is_head) { /* init head */
        head->data = (char) i;
        head->freq = freq[i];
        is_head = 1;
      }
      else {
        qnode *tmp = create_qnode((char) i, freq[i]);
        insert_qnode(head, tmp);
      }
    }
  }
  qnode *tree_head = build_huffman_tree(&head);
  get_codes(tree_head, 0, tree_head);

  //print(output);

  char outbuff[MAX_BUFF];
  form_buff(buff, strlen(buff), outbuff, MAX_BUFF, nchar);
  fprintf(output, "%s\n", outbuff);

  fclose(input);
  fclose(output);

  return 0;
}
