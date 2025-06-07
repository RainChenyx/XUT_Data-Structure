#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct node {
  ElemType elm;
  struct node *next;
}SLNode;

void ListInit(SLNode **ppHead) {
  (*ppHead) = (SLNode*)(malloc(sizeof(SLNode)));
  (*ppHead)->next = NULL;
}

/* ���룺ָ��ͷ����һ��ָ��
   ���أ�������Ԫ�صĸ���
   ���ܣ�����������Ԫ�صĸ���
*/
int ListLen(SLNode *pHead) {
    int len=0;
    SLNode *p = pHead->next;
    while(p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

/* ���룺ָ��ͷ����һ��ָ�룬����λ�á���������
   ���أ���������0��ʾԪ�ز���ɹ�������1��ʾԪ�ز���ʧ��
   ���ܣ�Ϊ��������elem����һ���µĽڵ㣬Ȼ��Ѹýڵ���뵽iλ��
        ԭ��iλ�õĽڵ㽫��Ϊi+1λ�õĽڵ�
*/
int ListInsert(SLNode *pHead, int i, ElemType elm) {
    if(i<1)
        return 1;
    SLNode *p = pHead;
    int j=0;
    while(p!=NULL && j<i-1)
    {
        p = p->next;
        j++;
    }
    if(p == NULL)
        return 1;
    SLNode *newNode = (SLNode *)malloc(sizeof(SLNode));
    if(newNode == NULL)
        return 1;
    newNode->next = p->next;
    p->next = newNode;
    newNode->elm = elm;
    return 0;
}

/* ���룺ָ��ͷ����һ��ָ�룬ɾ��λ�á�ָ��ElemType��һ��ָ��
   ���أ���������0��ʾԪ��ɾ���ɹ�������1��ʾԪ��ɾ��ʧ��
   ���ܣ���λ��iλ�õĽڵ�ɾ����ͬʱ�Ѹýڵ��б����data����ͨ��pElemָ���ӷ��ʣ�
        ���ظ��������ĵ��÷������ͷŸýڵ�ռ�õĶ����ڴ棬ԭ��i+1λ�õĽڵ㽫��Ϊiλ�õĽڵ�
*/
int ListDelete(SLNode *pHead, int i, ElemType *pElm) {
    if(i<1)
        return  1;
    int j=0;
    SLNode *p =pHead;
    while(p->next != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if(p->next == NULL)
        return 1;
    SLNode *delNode = p->next;
    *pElm = delNode->elm;
    p->next = delNode->next;
    free(delNode);
    return 0;
}

/* ���룺ָ��ͷ����һ��ָ�룬ָ��ElemType��һ��ָ��
   ���أ���������0��ʾԪ�ػ�ȡ�ɹ�������1��ʾԪ�ػ�ȡʧ��
   ���ܣ���λ��iλ�õĽڵ��е�data����һ�ݸ�*pElem
*/
int ListGet(SLNode *pHead, int i, ElemType *pElm) {
    if(i<1)
        return 1;
    int j=0;
    SLNode *p = pHead->next;
    while(p!= NULL && j < i-1)
    {
        p=p->next;
        j++;
    }
    if(p == NULL)
        return 1;
    *pElm = p->elm;
    return 0;
}

/* ���룺ָ��ͷ���Ķ���ָ��
   ���أ��޷���ֵ
   ���ܣ���*ppHead��ָ�������е�Ԫ�أ������ɾ�����ͷţ�
        ����*ppHeadһ��ָ������Ϊ��ֵ
*/
void ListDestroy(SLNode **ppHead) {
    SLNode *p = *ppHead;
    while (p != NULL) {
        SLNode *temp = p;
        p = p->next;
        free(temp);
    }
    *ppHead = NULL;
}

/* ���룺ָ��ͷ����һ��ָ��
   ���أ��޷���ֵ
   ���ܣ���*ppHead��ָ�������е�Ԫ�أ�����ش�ӡ������̨������Ļ�������
*/
void ListPrint(SLNode *pHead) {
    SLNode *p = pHead->next;
    while(p !=NULL)
    {
        printf("%d ",p->elm);
        p = p->next;
    }
    printf("\n");
}

// main���������ϵ�����������в���
int main() {
  int i;
  ElemType a[10], b[10], x;
  SLNode *pHead;
  for (i = 0; i < 10; i++) {
    b[i] = 100 + i;
    a[i] = i + 1;
  }
  ListInit(&pHead);
  for (i = 0; i < 10; i++)
    ListInsert(pHead, i + 1, a[i]);
  puts("��a�����е�����Ԫ�ز��뵽����pHead��Ľ����");
  ListPrint(pHead);
  for (i = 0; i < 10; i++)
    ListInsert(pHead, i + 1, b[i]);
  puts("��b�����е�����Ԫ�ؼ������뵽����pHead��Ľ����");
  ListPrint(pHead);
  for (i = 0; i < 10; i++) {
    ListDelete(pHead, 1, &x);
    printf("ɾ���ˣ�%d\n", x);
  }
  puts("������ɾ��һ���ֺ󣬼�����ӡ�����");
  ListPrint(pHead);

  return 0;
}

