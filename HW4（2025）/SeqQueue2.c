/***************************************************
 * Note:
 *   1. Sequencial implementation of circular queue
 *   2. Use size to dicide whether queue is empty
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef int ElemType;
typedef struct seqQue {
  ElemType a[MAX];
  int front;
  int rear;
  int size;
} SeqQue;

void InitQue(SeqQue **p) {
  *p = malloc(sizeof(SeqQue));
  (*p)->front = 0;
  (*p)->rear  = -1;
  (*p)->size = 0;
}

int QueEmpty(SeqQue *p) {
  return p->size == 0;
}

int QueFull(SeqQue *p) {
  return p->size == MAX;
}

void EnQue(SeqQue *p, ElemType x) {
  // printf("p->front: %d, p->rear: %d\n", p->front, p->rear);
  if (QueFull(p)) {
    puts("error: enqueue to a full queue!");
    return;
  }
  p->rear = (p->rear + 1) % MAX;
  p->a[p->rear] = x;
  p->size += 1;
}

void DeQue(SeqQue *p, ElemType *q) {
  if (QueEmpty(p)) {
    puts("error: depart from an empty queue!");
    return;
  }
  *q = p->a[p->front];
  p->front = (p->front + 1) % MAX;
  p->size -= 1;
}

void PrintQue(SeqQue *p) {
  if (QueEmpty(p)) return;
  puts("the queue has: ");
  int i = p->front;
  while (i != p->rear) {
    printf("%5d", p->a[i]);
    i = (i + 1) % MAX;
  }
  printf("%5d\n", p->a[i]);
}

void QueClear(SeqQue *p) {
  p->front = 0;
  p->rear = -1;
}

void QueDestory(SeqQue **p) {
  free(*p);
  *p = NULL;
}

int main() {
  int i, tmp;
  ElemType a[5] = {11, 22, 33, 44, 55};
  SeqQue *p;
  InitQue(&p);
  // printf("int main: p->front: %d, p->rear: %d\n", p->front, p->rear);
  for (i = 0; i < 5; i++) {
    EnQue(p, a[i]);
    PrintQue(p);
  }
  for (i = 0; i < 5; i++) {
    DeQue(p, &tmp);
    PrintQue(p);
  }
  return 0;
}



