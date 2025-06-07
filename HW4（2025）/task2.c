/**********************************************
 * ����2���������¶�����ɲ���ͷ������ʽ���У������ԡ�*
 * �ļ����룺GBK                                *
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

// ��ʼ������
void initQue(Que *q)
{
    q->front = NULL;
    q->rear = NULL;
}

// �����п�
int isEmpty(Que *q)
{
    return q->front == NULL;
}

// ��Ԫ�ض�β���
void enterQue(Que *q, ElemType x)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("�ڴ����ʧ��\n");
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
    printf("Ԫ��:%d�����\n",x);
}

// ��ͷ����
int outQue(Que *q, ElemType *x)
{
    if (isEmpty(q))
    {
        printf("�����ǿյģ��޶�ͷԪ�ؿ��Գ���\n");
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

// ��ȡ��ͷԪ��
int getFirst(Que *q, ElemType *x)
{
    if(isEmpty(q))
    {
        printf("�����ǿյģ��޶�ͷԪ��\n");
        return 0;
    }
    *x = q->front->elem;
    return 1;
}

// ���ٶ���
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

// ���в���
int main()
{
    Que q;
    initQue(&q);  // ��ʼ������
    enterQue(&q,5);  // Ԫ��5���
    enterQue(&q,2);  // Ԫ��2���
    enterQue(&q,6);  // Ԫ��6���
    ElemType x;
    outQue(&q,&x);  // ��ͷԪ�س���
    printf("��ͷԪ��Ϊ:%d\n", x);
    getFirst(&q,&x);  // ��ȡ��ǰ��ͷԪ��
    printf("��ͷԪ��Ϊ:%d\n", x);
    destroyQue(&q);  // ���ٶ���
    return 0;
}