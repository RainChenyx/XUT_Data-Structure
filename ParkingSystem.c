#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_CARS 5 // 停车场最大容量
#define EMPLOYEE_FILE "employees.txt" // 员工车牌号文件

// 车辆结构体
typedef struct Car
{
    char license_plate[20]; // 车牌号
    time_t parking_time; // 停车时间
}Car;

// 便道车辆结点
typedef struct carNode
{
    Car car;
    struct carNode *next; // 链表的下一个车辆
}CNode;

// 停车场栈 & 退出栈
typedef struct Stack
{
    Car* cars[MAX_CARS];
    int top;
    int size;
}Stack;

// 初始化便道链表
void initLink(CNode **head)
{
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
void displayParkingLotAndRoadside(Stack* parkingLot, CNode* head);
void freeCars(CNode* head);
float calculateFee(time_t parking_time);
int isEmployeeCar(const char* license_plate);
void manageEmployeeCars();

int main()
{
    Stack parkingLot;
    Stack exit;
    CNode *head;
    initLink(&head);  // 初始化便道Link
    initStack(&parkingLot); // 初始化停车场Stack
    initStack(&exit); // 初始化退出栈Stack

    int choice;
    while (1)
    {
        printf("\n============================\n");
        printf("= 欢迎来到曲江新区停车场管理系统 =\n");
        printf("============================\n");
        printf("= 1. 车辆停放                =\n");
        printf("= 2. 车辆离开                =\n");
        printf("= 3. 显示停车场和便道停放车辆   =\n");
        printf("= 4. 员工车辆管理             =\n");
        printf("= 5. 退出                   =\n");
        printf("============================\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                parkCar(&parkingLot, head);
                break;
            case 2:
                leaveCar(&parkingLot, &exit, head);
                break;
            case 3:
                displayParkingLotAndRoadside(&parkingLot, head);
                break;
            case 4:
                manageEmployeeCars();
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

// 初始化停车场栈/退出栈
void initStack(Stack* s)
{
    s->top = -1;
    s->size = 0;
}

// 判断栈是否满
int isStackFull(Stack* s)
{
    return s->top == MAX_CARS - 1;
}

// 判断栈是否空
int isStackEmpty(Stack* s)
{
    return s->top == -1;
}

// 入栈
void push(Stack* s, Car* car)
{
    if (!isStackFull(s))
    {
        s->cars[++(s->top)] = car;
        s->size++;
    }
    else
    {
        printf("停车场已满，请在便道上排队等待。\n");
    }
}

// 出栈
Car* pop(Stack* s)
{
    if (!isStackEmpty(s))
    {
        return s->cars[(s->top)--];
    }
    return NULL;
}

// 判断便道链表是否空
int isLinkEmpty(CNode *head)
{
    return head->next == NULL;
}

// 加入便道链表
int enLink(CNode* head, Car* car)
{
    CNode *newNode = (CNode*)malloc(sizeof(CNode));
    if (newNode == NULL)
    {
        printf("分配内存失败\n");
        return 0;
    }
    newNode->car = *car; // 复制车辆信息
    newNode->next = NULL;

    CNode *p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newNode;
    return 1;
}

// 查询便道链队车辆个数
int LinkLen(CNode *head)
{
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
int deLink(CNode *head, char *license_plate)
{
    int j = 0, len = LinkLen(head);
    CNode *p = head;
    CNode *q = NULL;

    // 遍历链表查找匹配的车牌号
    while (p != NULL && j <= len)
    {
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

// 车辆停车
void parkCar(Stack* parkingLot, CNode* head)
{
    Car* car = (Car*)malloc(sizeof(Car));
    printf("请输入车牌号: ");
    scanf("%s", car->license_plate);
    car->parking_time = time(NULL); // 记录进入停车场的时间

    if (isStackFull(parkingLot))
    {
        enLink(head, car);
        printf("停车场已满，车辆停在便道上，等待停车场分配空位。\n");
    } else
    {
        push(parkingLot, car);
        printf("车辆 %s 已停入停车场。\n",car->license_plate);
    }
}

// 车辆离开
void leaveCar(Stack* parkingLot, Stack* exit, CNode* head)
{
    if (isStackEmpty(parkingLot))
    {
        printf("停车场为空，没有车辆可以离开。\n");
        return;
    }

    char find[20]; // 查找该车
    printf("请输入车牌号：");
    scanf("%s", find);

    // 查找停车场需要离开的车辆
    int found = 0;
    for (int i = parkingLot->top; i >= 0; i--)
    {
        if (strcmp(parkingLot->cars[i]->license_plate, find) == 0)
        {
            found = 1;

            // 将后面的车辆移动到退出栈
            for (int j = parkingLot->top; j > i; j--)
            {
                push(exit, pop(parkingLot));
            }

            // 离开车辆
            Car* leavingCar = pop(parkingLot);
            float fee = calculateFee(leavingCar->parking_time);
            if (isEmployeeCar(leavingCar->license_plate))
            {
                fee = 0;
            }
            int second = fee * 10;
            printf("车辆 %s 离开停车场，停车时长： %d 秒，停车费用: %.2f 元\n", leavingCar->license_plate, second, fee);
            free(leavingCar);

            // 将退出栈中的车辆返回停车场
            while (!isStackEmpty(exit))
            {
                Car* carToReturn = pop(exit);
                push(parkingLot, carToReturn);
            }
            break;
        }
    }

    // 检查便道是否有车辆可以进入停车场
    if (found ==1 && !isLinkEmpty(head))
    {
        Car* nextCar = dequeue(head);
        nextCar->parking_time = time(NULL); // 记录进入停车场的时间
        push(parkingLot, nextCar);
        printf("便道上的车辆 %s 进入停车场\n", nextCar->license_plate);
    }


    if (!found) {
        int in;  // 查找便道需要离开的车辆
        in = deLink(head,find);
        if(in == 1)
        {
            printf("便道上的车辆 %s 离开，无收费\n", find);
        }
        if(in == 0)
        {
            printf("未找到车牌号为 %s 的车辆\n", find);
        }
    }
}

// 从便道中出队
Car* dequeue(CNode* head)
{
    if (isLinkEmpty(head))
    {
        return NULL;
    }
    CNode* firstNode = head->next;
    head->next = firstNode->next;
    Car* car = (Car*)malloc(sizeof(Car));
    *car = firstNode->car;
    free(firstNode);
    return car;
}

// 显示停车场和便道
void displayParkingLotAndRoadside(Stack* parkingLot, CNode* head)
{
    if(!isLinkEmpty(head))
    {
        printf("\n=================================================\n");
        printf("= 便道车辆: ");
        CNode *current = head->next;
        while (current != NULL)
        {
            printf(" %s --", current->car.license_plate);
            current = current->next;
        }
        printf("\n");
    }

    if (isStackEmpty(parkingLot))
    {
        printf("               目前停车场无车辆停放              \n");
    }
    printf("=================================================\n");
    printf("=                     停车场                     =\n");
    printf("=================================================\n");
    for (int i = MAX_CARS-1; i >= 0; i--)
    {
        if(i <= parkingLot->top)
        {
            int total_time = parkingLot->cars[i]->parking_time;
            int second = total_time % 60;
            int minute = total_time / 60 % 60;
            int hour = (total_time % 86400) / 3600 + 8;  // 北京时间是东八区，因此要加8小时
            printf("=车牌号: %10s = 进入停车场的北京时间: %02d:%02d:%02d =\n", parkingLot->cars[i]->license_plate,hour,minute, second);
        }
        else
        {
            printf("=                       空                      =\n");
        }
        printf("=================================================\n");
    }
}

// 释放便道上的全部车辆
void freeCars(CNode* head)
{
    CNode *p = head->next;
    while (p != NULL)
    {
        CNode *temp = p;
        p = p->next;
        free(temp);
    }
    free(head); // 释放头节点
}

// 计算停车费用
float calculateFee(time_t parking_time)
{
    time_t current_time = time(NULL);
    float seconds = difftime(current_time, parking_time);
    return seconds * 0.1; // 每秒0.1元
}

// 检查车牌是否为员工车辆
int isEmployeeCar(const char* license_plate) {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL)
    {
        printf("无法打开员工车牌号文件。\n");
        return 0;
    }

    char line[20];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0; // 去掉换行符
        if (strcmp(line, license_plate) == 0)
        {
            fclose(file);
            return 1; // 是员工车辆
        }
    }

    fclose(file);
    return 0; // 不是员工车辆
}

// 管理员工车辆
void manageEmployeeCars()
{
    int choice;
    printf("\n============================\n");
    printf("= 员工车辆管理               =\n");
    printf("============================\n");
    printf("= 1. 添加员工车牌号           =\n");
    printf("= 2. 显示员工车牌号           =\n");
    printf("= 3. 删除员工车牌号           =\n");
    printf("= 4. 退出                   =\n");
    printf("============================\n");
    printf("请选择操作: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
        case 1:
        {
            char license_plate[20];
            printf("请输入员工车牌号: ");
            scanf("%s", license_plate);
            FILE *file = fopen(EMPLOYEE_FILE, "a");
            if (file == NULL)
            {
                printf("无法打开员工车牌号文件。\n");
                return;
            }
            fprintf(file, "%s\n", license_plate);
            fclose(file);
            printf("员工车牌号 %s 已添加。\n", license_plate);
            break;
        }
        case 2:
        {
            FILE *file = fopen(EMPLOYEE_FILE, "r");
            if (file == NULL)
            {
                printf("无法打开员工车牌号文件。\n");
                return;
            }
            char line[20];
            printf("\n============================\n");
            printf("员工车牌号:\n");
            printf("============================\n");
            while (fgets(line, sizeof(line), file))
            {
                line[strcspn(line, "\n")] = 0;
                printf("=        %10s        =\n", line);
                printf("============================\n");
            }
            fclose(file);
            break;
        }
        case 3:
        {
            char license_plate[20];
            printf("请输入要删除的员工车牌号: ");
            scanf("%s", license_plate);

            // 读取所有员工车牌号并排除要删除的车牌号
            FILE *file = fopen(EMPLOYEE_FILE, "r");
            if (file == NULL) {
                printf("无法打开员工车牌号文件。\n");
                return;
            }

            FILE *temp_file = fopen("temp.txt", "w");
            if (temp_file == NULL) {
                printf("无法创建临时文件。\n");
                fclose(file);
                return;
            }

            char line[20];
            int found = 0;
            while (fgets(line, sizeof(line), file))
            {
                line[strcspn(line, "\n")] = 0;
                if (strcmp(line, license_plate) != 0)
                {
                    fprintf(temp_file, "%s\n", line);
                } else {
                    found = 1; // 找到要删除的车牌号
                }
            }

            fclose(file);
            fclose(temp_file);

            // 替换原文件
            remove(EMPLOYEE_FILE);
            rename("temp.txt", EMPLOYEE_FILE);

            if (found) {
                printf("员工车牌号 %s 已删除。\n", license_plate);
            } else {
                printf("未找到员工车牌号 %s。\n", license_plate);
            }
            break;
        }
        case 4:
            break;
        default:
            printf("无效的选择，请重试。\n");
            break;
    }
}