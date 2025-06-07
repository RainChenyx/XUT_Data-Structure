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

/* 输入：指向头结点的一级指针
   返回：链表中元素的个数
   功能：计算链表中元素的个数
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

/* 输入：指向头结点的一级指针，插入位置、插入数据
   返回：函数返回0表示元素插入成功，返回1表示元素插入失败
   功能：为插入数据elem创建一个新的节点，然后把该节点插入到i位置
        原来i位置的节点将变为i+1位置的节点
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

/* 输入：指向头结点的一级指针，删除位置、指向ElemType的一级指针
   返回：函数返回0表示元素删除成功，返回1表示元素删除失败
   功能：把位于i位置的节点删除，同时把该节点中保存的data数据通过pElem指针间接访问，
        带回给本函数的调用方，并释放该节点占用的堆区内存，原来i+1位置的节点将变为i位置的节点
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

/* 输入：指向头结点的一级指针，指向ElemType的一级指针
   返回：函数返回0表示元素获取成功，返回1表示元素获取失败
   功能：把位于i位置的节点中的data拷贝一份给*pElem
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

/* 输入：指向头结点的二级指针
   返回：无返回值
   功能：把*ppHead所指的链表中的元素，逐个地删除和释放，
        最后把*ppHead一级指针设置为空值
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

/* 输入：指向头结点的一级指针
   返回：无返回值
   功能：把*ppHead所指的链表中的元素，逐个地打印到控制台（即屏幕输出），
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

// main函数对以上单链表操作进行测试
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
  puts("把a数组中的所有元素插入到链表pHead后的结果：");
  ListPrint(pHead);
  for (i = 0; i < 10; i++)
    ListInsert(pHead, i + 1, b[i]);
  puts("把b数组中的所有元素继续插入到链表pHead后的结果：");
  ListPrint(pHead);
  for (i = 0; i < 10; i++) {
    ListDelete(pHead, 1, &x);
    printf("删除了：%d\n", x);
  }
  puts("把链表删除一部分后，继续打印结果：");
  ListPrint(pHead);

  return 0;
}

