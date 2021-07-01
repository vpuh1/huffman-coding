#ifndef __HUFFMAN_H
#define __HUFFMAN_H

char ans[128][16]; /* final codes */
char dp[128][16];  /* get Huffman codes using dynamic programming */

typedef struct QueueNode {
  char data;
  int freq;
  struct QueueNode *left, *right;
  struct QueueNode *next;
} qnode;

void insert_qnode(qnode *head, qnode *node);
void delete_qnode(qnode **head);
void sort_queue(qnode *head);
qnode *build_huffman_tree(qnode **head);
qnode *create_qnode(char data, size_t freq);
void get_codes(qnode *cur, int k, qnode *head);

#endif
