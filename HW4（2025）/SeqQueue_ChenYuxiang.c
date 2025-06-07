/*****************************************************************************************
 * 文件编码：GBK
 * Task 1:
 *   Write a function that will read one line of input from the terminal. The input
 *   is supposed to consist of two parts separated by a colon ':'. As its result, your
 *   function should produce a single character as follows:
 *   N :No colon on the line.
 *   L :The left part (before the colon) is longer than the right.
 *   R :The right part (after the colon) is longer than the left.
 *   D :The left and right parts have the same length but are different.
 *   S :The left and right parts are exactly the same.
******************************************************************************************/

#include <stdio.h>
#include <string.h>
#define Maxsize 100

typedef struct
{
    char data[Maxsize];
    int front;
    int rear;
    int count;
} Queue;

// 初始化队列
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// 判断队空
int isEmpty(Queue q)
{
    return q.rear == q.front;
}

// 入队
void enterQueue(Queue *q, char c)
{
    q->data[q->rear] = c;
    q->rear = (q->rear+1)%Maxsize;
    q->count++;
}

// 出队
char outQueue(Queue *q)
{
    if(isEmpty(*q))
    {
        printf("队列是空的");
        return 'a';
    }
    char c = q->data[q->front];
    q->front = (q->front + 1)%Maxsize;
    q->count--;
    return c;
}

// 比较
char compare(char *line)
{
    Queue q;
    initQueue(&q);
    char c;
    int len = strlen(line);
    int L_len,R_len,i = 0;
    int PD = 0; // 判断是否有 ":"
    for(i; i<len; i++)
    {
        if(line[i] == ':')
        {
            PD = 1;
            break;
        }
        else
        {
            enterQueue(&q,line[i]);
        }
    }
    if(PD == 0)
        return 'N';
    L_len = q.count;
    R_len = len - L_len -1;
    if(L_len > R_len)
        return 'L';
    else if(L_len < R_len)
        return  'R';
    else if(L_len == R_len)
    {
        for(i= R_len+1; i<len; i++)
        {
            c = outQueue(&q);
            if(c != line[i])
                return 'D';
        }
        return 'S';
    }
}

int main()
{
    char line[Maxsize];
    char result;
    printf("Enter a line:");
    fgets(line, Maxsize, stdin);
    line[strcspn(line, "\n")] = 0;  // 去除 fgets 可能读取的换行符
    result = compare(line);
    printf("result: %c",result);
}