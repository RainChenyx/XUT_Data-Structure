#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 5 // 停车场最大容量

// 车辆结构体
typedef struct Car {
    char license_plate[20]; // 车牌号
    int parking_time; // 停车时间（单位：秒）
} Car;

// 便道车辆结点
typedef struct carNode {
    Car car;
    struct carNode *next; // 链表的下一个车辆
} CNode;

// 停车场栈 & 退出栈
typedef struct Stack {
    Car* cars[MAX_CARS];
    int top;
} Stack;

// 初始化便道链表
void initLink(CNode **head) {
    *head = (CNode*)malloc(sizeof(CNode));
    (*head)->next = NULL;
}

// 函数声明
int LinkLen(CNode *head);
int deLink(CNode *head, char *license_plate);
void initStack(Stack* s);
int isStackFull(Stack* s);
int isStackEmpty(Stack* s);
void push(Stack* s, Car* car);
Car* pop(Stack* s);
int isLinkEmpty(CNode *head);
int enLink(CNode* head, Car* car);
Car* dequeue(CNode* head);
void parkCar(Stack* parkingLot, CNode* head);
void leaveCar(Stack* parkingLot, Stack* exit, CNode* head);
void displayParkingLot(Stack* parkingLot);
void displayRoadside(CNode* head);
void freeCars(CNode* head);

int main() {
    Stack parkingLot;
    Stack exit;
    CNode *head;
    initLink(&head);  // 初始化便道Link
    initStack(&parkingLot); // 初始化停车场Stack
    initStack(&exit); // 初始化退出栈Stack

    int choice;
    while (1) {
        printf("\n停车场管理系统\n");
        printf("1. 停车\n");
        printf("2. 离开\n");
        printf("3. 显示停车场\n");
        printf("4. 显示便道\n");
        printf("5. 退出\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                parkCar(&parkingLot, head);
                break;
            case 2:
                leaveCar(&parkingLot, &exit, head);
                break;
            case 3:
                displayParkingLot(&parkingLot);
                break;
            case 4:
                displayRoadside(head);
                break;
            case 5:
                freeCars(head);
                break;
            default:
                printf("无效的选择，请重试。\n");
        }
        if(choice == 5)
            break;
    }
    return 0;
}

// 初始化停车场栈
void initStack(Stack* s) {
    s->top = -1;
}

// 判断栈是否满
int isStackFull(Stack* s) {
    return s->top == MAX_CARS - 1;
}

// 判断栈是否空
int isStackEmpty(Stack* s) {
    return s->top == -1;
}

// 入栈
void push(Stack* s, Car* car) {
    if (!isStackFull(s)) {
        s->cars[++(s->top)] = car;
    } else {
        printf("停车场已满，请在便道上排队等待。\n");
    }
}

// 出栈
Car* pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->cars[(s->top)--];
    }
    return NULL;
}

// 判断便道链表是否空
int isLinkEmpty(CNode *head) {
    return head->next == NULL;
}

// 加入便道链表
int enLink(CNode* head, Car* car) {
    CNode *newNode = (CNode*)malloc(sizeof(CNode));
    if (newNode == NULL) {
        printf("分配内存失败\n");
        return 0;
    }
    newNode->car = *car; // 复制车辆信息
    newNode->next = NULL;

    CNode *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
    return 1;
}

// 查询便道链队车辆个数
int LinkLen(CNode *head){
    int len = 0;
    CNode *p = head->next;
    while(p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

// 删除结点(取消排队，1表示删除成功，0表示删除失败)
int deLink(CNode *head, char *license_plate) {
    int j = 0, len = LinkLen(head);
    CNode *p = head;
    CNode *q = NULL;

    // 遍历链表查找匹配的车牌号
    while (p != NULL && j <= len) {
        q = p; // 保存当前节点
        p = p->next; // 移动到下一个节点

        // 检查是否找到匹配的车牌号
        if (p != NULL && strcmp(p->car.license_plate, license_plate) == 0)
            break;

        j++;
    }

    // 如果未找到匹配的节点或链表为空
    if (p == NULL)
        return 0;

    // 删除找到的节点
    q->next = p->next; // 将前一个节点的next指向删除节点的下一个节点
    free(p); // 释放删除节点的内存

    return 1;
}

// 停车
void parkCar(Stack* parkingLot, CNode* head) {
    Car* car = (Car*)malloc(sizeof(Car));
    printf("请输入车牌号: ");
    scanf("%s", car->license_plate);

    if (isStackFull(parkingLot)) {
        enLink(head, car);
        printf("停车场已满，车辆停在便道上，等待停车场分配空位。\n");
    } else {
        push(parkingLot, car);
        printf("车辆已停入停车场。\n");
    }
}

// 离开
void leaveCar(Stack* parkingLot, Stack* exit, CNode* head) {
    if (isStackEmpty(parkingLot)) {
        printf("停车场为空，没有车辆可以离开。\n");
        return;
    }

    char find[20]; // 查找该车
    printf("请输入车牌号：");
    scanf("%s", find);

    // 查找停车场需要离开的车辆
    int found = 0;
    for (int i = parkingLot->top; i >= 0; i--) {
        if (strcmp(parkingLot->cars[i]->license_plate, find) == 0) {
            found = 1;

            // 将后面的车辆移动到退出栈
            for (int j = parkingLot->top; j > i; j--) {
                push(exit, pop(parkingLot));
            }

            // 离开车辆
            Car* leavingCar = pop(parkingLot);
            printf("车辆 %s 离开停车场，停车时间: %d 秒，费用: %d 元\n",
                   leavingCar->license_plate, leavingCar->parking_time, leavingCar->parking_time * 5);
            free(leavingCar);

            // 将退出栈中的车辆返回停车场
            while (!isStackEmpty(exit)) {
                Car* carToReturn = pop(exit);
                push(parkingLot, carToReturn);
            }
            break;
        }
    }

    // 检查便道是否有车辆可以进入停车场
    if (found ==1 && !isLinkEmpty(head)) {
        Car* nextCar = dequeue(head);
        push(parkingLot, nextCar);
        printf("便道上的车辆 %s 进入停车场\n", nextCar->license_plate);
    }


    if (!found) {
        int in;  // 查找便道需要离开的车辆
        in = deLink(head,find);
        if(in == 1)
        {
            printf("便道上的车辆 %s 离开\n", find);
        }
        if(in == 0)
        {
            printf("未找到车牌号为 %s 的车辆\n", find);
        }
    }
}

// 从便道中出队
Car* dequeue(CNode* head) {
    if (isLinkEmpty(head)) {
        return NULL;
    }
    CNode* firstNode = head->next;
    head->next = firstNode->next;
    Car* car = (Car*)malloc(sizeof(Car));
    *car = firstNode->car; // 复制车辆信息
    free(firstNode);
    return car;
}

// 显示停车场
void displayParkingLot(Stack* parkingLot) {
    if (isStackEmpty(parkingLot)) {
        printf("停车场为空。\n");
        return;
    }
    printf("停车场车辆:\n");
    for (int i = parkingLot->top; i >= 0; i--) {
        printf("车牌号: %s, 停车时间: %d 秒\n", parkingLot->cars[i]->license_plate, parkingLot->cars[i]->parking_time);
    }
}

// 显示便道
void displayRoadside(CNode* head) {
    if (isLinkEmpty(head)) {
        printf("便道为空。\n");
        return;
    }
    printf("便道车辆:\n");
    CNode *current = head->next;
    while (current != NULL) {
        printf("车牌号: %s\n", current->car.license_plate);
        current = current->next;
    }
}

// 释放便道上的全部车辆
void freeCars(CNode* head) {
    CNode *p = head->next;
    while (p != NULL) {
        CNode *temp = p;
        p = p->next;
        free(temp);
    }
    free(head); // 释放头节点
}