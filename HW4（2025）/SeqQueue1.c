/*******************************************************
 * Note:
 *   1. Sequencial implementation of circular queue
 *   2. Save one slot to dicide whether queue is empty 
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef int ElemType;
typedef struct seqQue {
  ElemType a[MAX];
  int front;
  int rear;
} Que;

void InitQue(Que **p) {
  *p = malloc(sizeof(Que));
  (*p)->front = 0;
  (*p)->rear  = 0;
}

int QueEmpty(Que *p) {
  return p->front == p->rear;
}

int QueFull(Que *p) {
  return (p->rear + 1) % MAX == p->front;
}

void EnQue(Que *p, ElemType x) {
  // printf("p->front: %d, p->rear: %d\n", p->front, p->rear);
  if (QueFull(p))
    puts("error: enqueue to a full queue!");
  else {
    p->rear = (p->rear + 1) % MAX;
    p->a[p->rear] = x;
  }
}

void DeQue(Que *p, ElemType *q) {
  if (QueEmpty(p))
    puts("error: depart from an empty queue!");
  else {
    *q = p->a[p->front];
    p->front = (p->front + 1) % MAX;
  }
}

void PrintQue(Que *p) {
  if (QueEmpty(p)) return;
  puts("the queue has: ");
  int i = (p->front + 1) % MAX;
  while (i != p->rear) {
    printf("%5d", p->a[i]);
    i = (i + 1) % MAX;
  }
  printf("%5d\n", p->a[i]);
}

void QueClear(Que *p) {
  p->front = p->rear = 0;
}

void QueDestory(Que **p) {
  free(*p);
  *p = NULL;
}

int main() {
  int i, tmp;
  ElemType a[5] = {11, 22, 33, 44, 55};
  Que *p;
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
