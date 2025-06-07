#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
typedef double ElemType;
typedef struct list {
  ElemType a[MAXSIZE + 1];
  int len;
} SeqList;

SeqList * InitList();
void InitList2(SeqList **ppList);
int ListFull(SeqList *pList);
int ListEmpty(SeqList *pList);
int ListLen(SeqList *pList);
void Error(char *msg);
int GetElem(SeqList *pList, int i, ElemType *pElm);
int InsertElem(SeqList * pList, int i, ElemType elm);
int DelElem(SeqList *pList, int i, ElemType *pElm);
void PrintList(SeqList *pList);


int main() {
  int i;
  SeqList *pList;
  ElemType x;
  // ElemType a[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ElemType a[11] = {0.1, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.9};
  // ElemType a[11] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
  // pList = InitList(); //利用返回值初始化
  InitList2(&pList);     //利用指针变量的地址初始化，效果与上一句相同

  for (i = 1; i <= 10; i++)
    InsertElem(pList, i, a[i]);
  PrintList(pList);
  DelElem(pList, 4, &x);
  printf("删除第四个元素后的结果为：");
  PrintList(pList);
  //以下代码为测试边界情况
  InsertElem(pList, 4, a[4]);  // 插入第四个元素以恢复长度
  DelElem(pList, 1, &x);  //测试删除第一个元素
  printf("（边界情况）删除第一个元素后的结果为：");
  PrintList(pList);
  InsertElem(pList, 1, a[1]);  // 插入第一个元素以恢复长度
  DelElem(pList, 10, &x);  //测试删除最后一个元素
  printf("（边界情况）删除最后一个元素后的结果为：");
  PrintList(pList);
  return 0;
}

/*
 * 初始化顺序表的方式之一，利用返回值的方法使调用方获得指向顺序表的指针
 */

SeqList * InitList() {
  SeqList *pList;
  pList = (SeqList *)malloc(sizeof(SeqList));
  pList->len = 0;
  return pList;
}

/*
 * 初始化顺序表方式二，利用调用方传来的指向结构体指针变量的指针（即二级指针）
 * 使调用方的结构体指针变量获得顺序表的指针，功能和方式一相同，但调用方式不同
 */
void InitList2(SeqList **ppList) {
  *ppList = (SeqList *)malloc(sizeof(SeqList));
  (*ppList)->len = 0;
}

/*
 * 判断顺序表是否为满
 */
int ListFull(SeqList *pList) {
  /*
  // 这段代码已经简化为一行
  if (pList->len == MAXSIZE)
    return 1;
  else
    return 0;
  */
  return (pList->len == MAXSIZE) ? 1 : 0;
}

/*
 * 判断单链表是否为空
 */
int ListEmpty(SeqList *pList) {
  return (pList->len == 0) ? 1 : 0;
}

/*
 * 返回单链表的长度
 */
int ListLen(SeqList *pList) {
  return pList->len;
}

/*
 * 出错提示的包裹函数，能以更好的格式显示错误消息
 */
void Error(char *msg) {
  printf("error: %s\n", msg);
}

/*
 * 获取i位置的元素
 */
int GetElem(SeqList *pList, int i, ElemType *pElm) {
  if (ListEmpty(pList)) {
    Error("Get element from empty list");
    return 0;
  }
  if (i < 1 || i > MAXSIZE) {
    Error("Get element from illegal position!");
    return 0;
  }
  *pElm = pList->a[i];
  return 1;
}

/*
 * 在i位置插入数据元素elm
 */
int InsertElem(SeqList * pList, int i, ElemType elm) {
  int k;
  if (ListFull(pList)) {
    Error("Insert element to a full list!");
    return 0;
  }
  if (i < 1 || i > pList->len + 1) {
    Error("insert element out of range!");
    return 0;
  }
  for (k = pList->len; k >= i; k--) pList->a[k + 1] = pList->a[k];
  pList->a[i] = elm;
  pList->len += 1;
  return 1;
}

/*
 * 删除i位置的元素，该元素通过pElm带回调用方
 * 但该函数有错误，请找出错误并更正
 */
int DelElem(SeqList *pList, int i, ElemType *pElm) {
  if (ListEmpty(pList)) {
    Error("delete element from an empty list");
    return 0;
  }
  if (i < 1 || i > pList->len) {
    Error("delete element out of range");
    return 0;
  }
  *pElm = pList->a[i];
  //在这里出错误：删除指定位置元素时，没有将后续元素依次向前移动来填补被删除元素的位置
  if (i < pList->len) {  //最后一个元素无需移动，直接len-1就好
      for (; i < pList->len; i++)
          pList->a[i] = pList->a[i + 1];
  }
  //下面都是正确的
  pList->len -= 1;
  return 1;
}

/*
 * 打印输出顺序表全部元素
 */
void PrintList(SeqList *pList) {
  int i;
  for (i = 1; i <= pList->len; i++)
    printf("%.2lf ", pList->a[i]);
  putchar('\n');
}
