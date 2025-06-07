/**********************************************
 * 任务2：按照以下定义完成不带头结点的链式队列，并测试。*
 * 文件编码：GBK                                *
 **********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node {
    ElemType elem;
    struct node *next;
} Node;
typedef struct queue {
    Node * front;
    Node * rear;
} Que;

// 初始化队列
void initQue(Que *q)
{
    q->front = NULL;
    q->rear = NULL;
}

// 队列判空
int isEmpty(Que *q)
{
    return q->front == NULL;
}

// 新元素队尾入队
void enterQue(Que *q, ElemType x)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("内存分配失败\n");
        return;
    }
    node->elem = x;
    node->next = NULL;
    if(isEmpty(q))
    {
        q->rear = node;
        q->front = node;
    }
    else
    {
        q->rear->next = node;
        q->rear = node;
    }
    printf("元素:%d已入队\n",x);
}

// 队头出队
int outQue(Que *q, ElemType *x)
{
    if (isEmpty(q))
    {
        printf("队列是空的，无队头元素可以出队\n");
        return 0;
    }
    Node *outNode = q->front;
    *x = outNode->elem;
    q->front = outNode->next;
    if(q->front ==NULL)
        q->rear = NULL;
    free(outNode);
    return 1;
}

// 获取队头元素
int getFirst(Que *q, ElemType *x)
{
    if(isEmpty(q))
    {
        printf("队列是空的，无队头元素\n");
        return 0;
    }
    *x = q->front->elem;
    return 1;
}

// 销毁队列
void destroyQue(Que *q)
{
    while (q->front != NULL)
    {
        Node *destroy = q->front;
        q->front = destroy->next;
        free(destroy);
    }
    q->rear = NULL;
}

// 队列测试
int main()
{
    Que q;
    initQue(&q);  // 初始化队列
    enterQue(&q,5);  // 元素5入队
    enterQue(&q,2);  // 元素2入队
    enterQue(&q,6);  // 元素6入队
    ElemType x;
    outQue(&q,&x);  // 队头元素出队
    printf("队头元素为:%d\n", x);
    getFirst(&q,&x);  // 获取当前队头元素
    printf("队头元素为:%d\n", x);
    destroyQue(&q);  // 销毁队列
    return 0;
}