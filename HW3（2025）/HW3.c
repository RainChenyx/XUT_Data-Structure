/*************************************************************
 * ���ʣ����ܴӺ��������ж����п��������ó�ʼ�������ĵ��÷���           *
 *       Ӧ��׼��ʲô���ı�����                                 *
 *                                                           *
 * Note:                                                     *
 *   1. Sequencial implementation of stack                   *
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef char ElemType;
typedef struct stack {
  ElemType a[MAX];
  int top;
} Stack;

void InitStack(Stack *p) {
    p->top=-1;
}

int StackEmpty(Stack *p) {
    return p->top == -1;
}

int StackFull(Stack *p) {
    return p->top == MAX-1;
}

void Push(Stack *p, ElemType x) {
    if(StackFull(p))
    {
        printf("��ջ�������޷���ջ");
        return;
    }
    p->top += 1;
    p->a[p->top]=x;
}

void Pop(Stack *p, ElemType *q) {
    if(StackEmpty(p))
    {
        printf("ջ��,�޷���ջ");
        return;
    }
    *q = p->a[p->top];
    p->top -= 1;
}

int StackTop(Stack *p, ElemType *q) {
    if(StackEmpty(p))
    {
        printf("ջ��,�޷���ջ");
        return 0;
    }
    *q = p->a[p->top];
    return 1;
}

void StackClear(Stack *p) {
    p->top = -1;
}

// ���жϵ��ַ�������������a�У��������Ч���ȱ�����n��
// ͨ�����㷵��0����ʾ���Ų�ƥ�䣬����1��ʾƥ��
int Match(char a[], int n)
{
    Stack s;
    InitStack(&s);
    for (int i=0; i<n; i++) {
        if (a[i] == '{' || a[i] == '[' || a[i] == '(')
        {
            if (!StackFull(&s))
                Push(&s, a[i]);
        }
        else if (a[i] == '}')
        {
            if (StackEmpty(&s) || s.a[s.top] != '{')
                return 0;
            Pop(&s, &a[i]);
        }
        else if (a[i] == ']')
        {
            if (StackEmpty(&s) || s.a[s.top] != '[')
                return 0;
            Pop(&s, &a[i]);
        }
        else if(a[i] == ')')
        {
            if (StackEmpty(&s) || s.a[s.top] != '(')
                return 0;
            Pop(&s, &a[i]);
        }
    }
    return StackEmpty(&s);
}
                                

int main() {
  //char str[100] = "()[]{}";
  char str[100] = "{[()][(()())]}";
  //char str[100] = "([)]{}";
  //char str[100] = "{[)(]{}}";

  int n = strlen(str);  // ��ȡ�ַ����ĳ���
  int result = Match(str, n);  // �ж������Ƿ�ƥ��

  if (result) {
      printf("����ƥ��\n");
  }
  else {
      printf("���Ų�ƥ��\n");
  }
  return 0;
}        
