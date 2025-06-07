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
  // pList = InitList(); //���÷���ֵ��ʼ��
  InitList2(&pList);     //����ָ������ĵ�ַ��ʼ����Ч������һ����ͬ

  for (i = 1; i <= 10; i++)
    InsertElem(pList, i, a[i]);
  PrintList(pList);
  DelElem(pList, 4, &x);
  printf("ɾ�����ĸ�Ԫ�غ�Ľ��Ϊ��");
  PrintList(pList);
  //���´���Ϊ���Ա߽����
  InsertElem(pList, 4, a[4]);  // ������ĸ�Ԫ���Իָ�����
  DelElem(pList, 1, &x);  //����ɾ����һ��Ԫ��
  printf("���߽������ɾ����һ��Ԫ�غ�Ľ��Ϊ��");
  PrintList(pList);
  InsertElem(pList, 1, a[1]);  // �����һ��Ԫ���Իָ�����
  DelElem(pList, 10, &x);  //����ɾ�����һ��Ԫ��
  printf("���߽������ɾ�����һ��Ԫ�غ�Ľ��Ϊ��");
  PrintList(pList);
  return 0;
}

/*
 * ��ʼ��˳���ķ�ʽ֮һ�����÷���ֵ�ķ���ʹ���÷����ָ��˳����ָ��
 */

SeqList * InitList() {
  SeqList *pList;
  pList = (SeqList *)malloc(sizeof(SeqList));
  pList->len = 0;
  return pList;
}

/*
 * ��ʼ��˳���ʽ�������õ��÷�������ָ��ṹ��ָ�������ָ�루������ָ�룩
 * ʹ���÷��Ľṹ��ָ��������˳����ָ�룬���ܺͷ�ʽһ��ͬ�������÷�ʽ��ͬ
 */
void InitList2(SeqList **ppList) {
  *ppList = (SeqList *)malloc(sizeof(SeqList));
  (*ppList)->len = 0;
}

/*
 * �ж�˳����Ƿ�Ϊ��
 */
int ListFull(SeqList *pList) {
  /*
  // ��δ����Ѿ���Ϊһ��
  if (pList->len == MAXSIZE)
    return 1;
  else
    return 0;
  */
  return (pList->len == MAXSIZE) ? 1 : 0;
}

/*
 * �жϵ������Ƿ�Ϊ��
 */
int ListEmpty(SeqList *pList) {
  return (pList->len == 0) ? 1 : 0;
}

/*
 * ���ص�����ĳ���
 */
int ListLen(SeqList *pList) {
  return pList->len;
}

/*
 * ������ʾ�İ������������Ը��õĸ�ʽ��ʾ������Ϣ
 */
void Error(char *msg) {
  printf("error: %s\n", msg);
}

/*
 * ��ȡiλ�õ�Ԫ��
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
 * ��iλ�ò�������Ԫ��elm
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
 * ɾ��iλ�õ�Ԫ�أ���Ԫ��ͨ��pElm���ص��÷�
 * ���ú����д������ҳ����󲢸���
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
  //�����������ɾ��ָ��λ��Ԫ��ʱ��û�н�����Ԫ��������ǰ�ƶ������ɾ��Ԫ�ص�λ��
  if (i < pList->len) {  //���һ��Ԫ�������ƶ���ֱ��len-1�ͺ�
      for (; i < pList->len; i++)
          pList->a[i] = pList->a[i + 1];
  }
  //���涼����ȷ��
  pList->len -= 1;
  return 1;
}

/*
 * ��ӡ���˳���ȫ��Ԫ��
 */
void PrintList(SeqList *pList) {
  int i;
  for (i = 1; i <= pList->len; i++)
    printf("%.2lf ", pList->a[i]);
  putchar('\n');
}
