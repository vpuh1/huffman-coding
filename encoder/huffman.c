/* 
 * Build Huffman's tree 
 */

#include <stdlib.h>
#include <string.h>

#include "huffman.h"

/* insert node to queue */ 
void insert_qnode(qnode *head, qnode *node) {
  qnode *cur = head;
  while(cur->next != NULL) { /* move to the end of queue */ 
    cur = cur->next; 
  } 
  qnode *tmp = (qnode *) malloc(sizeof(qnode));
  tmp->data = node->data;
  tmp->freq = node->freq;
  tmp->next = NULL;
  tmp->left = node->left;
  tmp->right = node->right;
  cur->next = tmp;
}

void delete_qnode(qnode **head) {
  if(*head == NULL)
    return;
  qnode *tmp = (*head)->next;
  free(*head);
  *head = tmp;
}

void sort_queue(qnode *head) {
  qnode *i, *j;
  for(i = head; i->next != NULL; i = i->next) {
    for(j = i->next; j != NULL; j = j->next) {
      if(i->freq > j->freq) {
        int tmp_freq = i->freq;
        char tmp_data = i->data;
        qnode *tmp_left = i->left;
        qnode *tmp_right = i->right;
        i->freq = j->freq;
        i->data = j->data;
        i->left = j->left;
        i->right = j->right;
        j->freq = tmp_freq;
        j->data = tmp_data;
        j->left = tmp_left;
        j->right = tmp_right;
      }
    }
  }
}

qnode *create_qnode(char data, size_t freq) {
  qnode *tmp = (qnode *) malloc(sizeof(qnode));
  tmp->next = NULL;
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->data = data;
  tmp->freq = freq;
  return tmp;
}

void qnodecpy(qnode *dst, qnode *src) {
  dst->data = src->data;
  dst->freq = src->freq;
  dst->next = src->next;
  dst->left = src->left;
  dst->right = src->right;
}

qnode *build_huffman_tree(qnode **head) {
  while(*head != NULL) {
    qnode *first = (qnode *) malloc(sizeof(qnode));
    qnodecpy(first, *head);
    delete_qnode(head);
    if(*head == NULL) {
      return first;
    }
    qnode *second = (qnode *) malloc(sizeof(qnode));
    qnodecpy(second, *head);
    delete_qnode(head);
    qnode *parent = create_qnode((char) 0, first->freq + second->freq);
    if(first->freq < second->freq) {
      parent->left = first;
      parent->right = second;
    }
    else {
      parent->left = first;
      parent->right = second;
    }
    if(*head != NULL) {
      insert_qnode(*head, parent);
      sort_queue(*head);
    }
    else {
      return parent;
    }
  }
}

void get_codes(qnode *cur, int k, qnode *head) {
  if(cur->left == NULL && cur->right == NULL) {
      strcpy(ans[(int) cur->data], dp[k - 1]);
    return;
  }
  if(cur->left != NULL) {
    if(cur != head) {
      strcpy(dp[k], dp[k - 1]);
      dp[k][strlen(dp[k])] = '0';
    }
    else {
      dp[k][0] = '0';
    }
    get_codes(cur->left, k + 1, head);
  }
  if(cur->right != NULL) {
    if(cur != head) {
      strcpy(dp[k], dp[k - 1]);
      dp[k][strlen(dp[k])] = '1';
    }
    else {
       dp[k][0] = '1';
    }
    get_codes(cur->right, k + 1, head);
  }
}
