/*************************************************************
 * 提问：你能从函数的首行定义中看出，调用初始化函数的调用方，           *
 *       应该准备什么样的变量吗？                                 *
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
        printf("该栈已满，无法入栈");
        return;
    }
    p->top += 1;
    p->a[p->top]=x;
}

void Pop(Stack *p, ElemType *q) {
    if(StackEmpty(p))
    {
        printf("栈空,无法出栈");
        return;
    }
    *q = p->a[p->top];
    p->top -= 1;
}

int StackTop(Stack *p, ElemType *q) {
    if(StackEmpty(p))
    {
        printf("栈空,无法出栈");
        return 0;
    }
    *q = p->a[p->top];
    return 1;
}

void StackClear(Stack *p) {
    p->top = -1;
}

// 待判断的字符串保存在数组a中，数组的有效长度保存在n中
// 通过计算返回0，表示括号不匹配，返回1表示匹配
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

  int n = strlen(str);  // 获取字符串的长度
  int result = Match(str, n);  // 判断括号是否匹配

  if (result) {
      printf("括号匹配\n");
  }
  else {
      printf("括号不匹配\n");
  }
  return 0;
}        
