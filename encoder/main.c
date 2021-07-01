/* 
 * Simple Huffman coding implementation written in c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "huffman.h"

int main(int argc, char **argv) {
  if(argc != 3) {
    printf("usage: huffman-encoder <input file> <output file>\n");
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
  read_buff(buff, input);
  get_freq(buff, strlen(buff));

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

  char *converted = convert(buff, MAX_BUFF);
  if(converted) {
    write_buff(nchar, converted, output);
    free(converted);
  }

  fclose(input);
  fclose(output);

  return 0;
}
