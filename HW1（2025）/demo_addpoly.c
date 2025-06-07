#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define M 12
#define N 8

// �����ﲹ��һ���ṹ�壬����ϵ����ָ������

typedef struct {
    int coefficient;  //ϵ��
    int exponent;  // ָ��
}Poly;


// �������double�滻Ϊ�Լ�����Ľṹ�����ͣ���˳�����Ԫ�ص��������Լ�����ģ�
typedef Poly ElemType;

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
SeqList * AddPolynomials(SeqList *A, SeqList *B);

int main() {
  int i;
  SeqList *A, *B, *C;
  // �����a �� b��ʾ����������ʽ�������е������Ƕ���ʽϵ����
  // �����������е�λ�ñ�ʾ���ٴη�������a��ʾ���ǣ�
  // 0*X^0 + 0*X^1 + 7*X^2 + 0*X^3 + 3*X^4 + 1*X^5 + 9*X^6 + ...
  // b��ʾ���ǣ�
  // 0*X^0 + 0*X^1 + 8*X^2 + 1*X^3 + 22*X^4 + 7*X^5 ...
  int a[M] = {0, 0, 7,0,3,1,9,8,5,17,-8,100} ;
  int b[N] = {0, 0, 8,1,22,7,-9, 8};
  ElemType x;
  // a��b������ԭʼ����������
  A = InitList();
  B = InitList();
  for( i=0; i < M; i++){
      if(a[i] != 0){
          x.coefficient = a[i];
          x.exponent = i;
          InsertElem(A,A->len+1,x);
      }
  }
  for( i=0; i < N; i++){
      if(b[i] != 0){
          x.coefficient = b[i];
          x.exponent = i;
          InsertElem(B,B->len+1,x);
      }
  }
  C = AddPolynomials(A,B);
  printf("A = ");
  PrintList(A);
  printf("B = ");
  PrintList(B);
  printf("C = A + B = ");
  PrintList(C);
  free(A);
  free(B);
  free(C);

  return 0;
}


/* ���룺��
   ���أ�ָ��˳����ָ�룬ͨ������ֵ�������뵽�ġ�ָ���ڴ�ռ��ָ����ص��÷���
   ���ܣ�Ϊ˳��������ڴ�ռ䣬����˳���Ĵ�С��Ϊ0��
*/
SeqList * InitList() {
  SeqList *pList;
  pList = (SeqList *)malloc(sizeof(SeqList));
  pList->len = 0;
  return pList;
}

/* ���룺ָ��˳���ṹ��Ķ���ָ�룬���÷���Ҫ׼��һ��˳���ָ�������Ȼ��Ѹ�
         �����ĵ�ַ���ݽ�������һ��������ַ��
   ���أ���
   ���ܣ�Ϊ˳��������ڴ�ռ䣬����˳���Ĵ�С��Ϊ0��
*/
void InitList2(SeqList **ppList) {
  *ppList = (SeqList *)malloc(sizeof(SeqList));
  (*ppList)->len = 0;
}

/* ���룺ָ��˳����ָ��
   ���أ��������ͱ���1����ʾ˳�������������δ����
   ���ܣ��ж�˳����Ƿ�������
*/
int ListFull(SeqList *pList) {
  /*
  if (pList->len == MAXSIZE)
    return 1;
  else
    return 0;
  */
  return (pList->len == MAXSIZE) ? 1 : 0;
}

/* ���룺ָ��˳����ָ��
   ���أ��������ͱ���1����ʾ˳����ǿձ�����ǿա�
   ���ܣ��ж�˳����Ƿ��ѿա�
*/
int ListEmpty(SeqList *pList) {
  return (pList->len == 0) ? 1 : 0;
}

/* ���룺ָ��˳����ָ��
   ���أ��������ͱ�������ʾ˳�����ЧԪ�ظ���
   ���ܣ��ṩ˳�����ЧԪ�ظ���
*/
int ListLen(SeqList *pList) {
  return pList->len;
}

/* ���룺�ַ�ָ��
   ���أ���
   ���ܣ�����Զ���ĳ�����Ϣ����
*/
void Error(char *msg) {
  printf("[����]��%s\n", msg);
}
int GetElem(SeqList *pList, int i, ElemType *pElm) {
  if (ListEmpty(pList)) {
    Error("�ӿձ��ж�ȡ����Ԫ��");
    return 0;
  }
  if (i < 1 || i > MAXSIZE) {
    Error("��ȡλ�ô���");
    return 0;
  }
  *pElm = pList->a[i];
  return 1;
}

int InsertElem(SeqList * pList, int i, ElemType elm) {
  int k;
  if (ListFull(pList)) {
    Error("�޷����Ѿ����˵�˳����������Ԫ��!");
    return 0;
  }
  if (i < 1 || i > pList->len + 1) {
    Error("����λ��Խ��!");
    return 0;
  }
  for (k = pList->len; k >= i; k--)
    pList->a[k + 1] = pList->a[k];
  pList->a[i] = elm;
  pList->len += 1;
  return 1;
}

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
    if (i < pList->len) {  //���һ��Ԫ�������ƶ���ֱ��len-1�ͺ�
        for (; i < pList->len; i++)
            pList->a[i] = pList->a[i + 1];
    }
    pList->len -= 1;
    return 1;
}

void PrintList(SeqList *pList) {
  int i;
  for (i = 1; i <= pList->len; i++){
      printf("%d*X^%d", abs(pList->a[i].coefficient), pList->a[i].exponent);
      if (i != pList->len && pList->a[i+1].coefficient > 0)
          printf(" + ");
      else if(i != pList->len && pList->a[i+1].coefficient < 0)
        printf(" - ");
  }

  putchar('\n');
}

SeqList * AddPolynomials(SeqList *A, SeqList *B){
    SeqList *C = InitList();
    int i=1,j=1;
    while (i <= A->len || j <= B->len) {
        if(A->a[i].exponent > B->a[j].exponent){
            InsertElem(C,C->len+1,B->a[j]);
            j++;
        }
        else if(A->a[i].exponent < B->a[j].exponent){
            InsertElem(C,C->len+1,A->a[i]);
            i++;
        }
        else{
            Poly x;
            x.exponent = A->a[i].exponent;
            x.coefficient = A->a[i].coefficient + B->a[j].coefficient;
            if(x.coefficient != 0)
                InsertElem(C,C->len+1,x);
            i++;
            j++;
        }
    }
    return C;
}
