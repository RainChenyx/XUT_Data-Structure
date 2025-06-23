#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_CARS 5 // ͣ�����������
#define EMPLOYEE_FILE "employees.txt" // Ա�����ƺ��ļ�

// �����ṹ��
typedef struct Car
{
    char license_plate[20]; // ���ƺ�
    time_t parking_time; // ͣ��ʱ��
}Car;

// ����������
typedef struct carNode
{
    Car car;
    struct carNode *next; // �������һ������
}CNode;

// ͣ����ջ & �˳�ջ
typedef struct Stack
{
    Car* cars[MAX_CARS];
    int top;
    int size;
}Stack;

// ��ʼ���������
void initLink(CNode **head)
{
    *head = (CNode*)malloc(sizeof(CNode));
    (*head)->next = NULL;
}

// ��������
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
    initLink(&head);  // ��ʼ�����Link
    initStack(&parkingLot); // ��ʼ��ͣ����Stack
    initStack(&exit); // ��ʼ���˳�ջStack

    int choice;
    while (1)
    {
        printf("\n============================\n");
        printf("= ��ӭ������������ͣ��������ϵͳ =\n");
        printf("============================\n");
        printf("= 1. ����ͣ��                =\n");
        printf("= 2. �����뿪                =\n");
        printf("= 3. ��ʾͣ�����ͱ��ͣ�ų���   =\n");
        printf("= 4. Ա����������             =\n");
        printf("= 5. �˳�                   =\n");
        printf("============================\n");
        printf("��ѡ�����: ");
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
                printf("��Ч��ѡ�������ԡ�\n");
        }
        if(choice == 5)
            break;
    }
    return 0;
}

// ��ʼ��ͣ����ջ/�˳�ջ
void initStack(Stack* s)
{
    s->top = -1;
    s->size = 0;
}

// �ж�ջ�Ƿ���
int isStackFull(Stack* s)
{
    return s->top == MAX_CARS - 1;
}

// �ж�ջ�Ƿ��
int isStackEmpty(Stack* s)
{
    return s->top == -1;
}

// ��ջ
void push(Stack* s, Car* car)
{
    if (!isStackFull(s))
    {
        s->cars[++(s->top)] = car;
        s->size++;
    }
    else
    {
        printf("ͣ�������������ڱ�����Ŷӵȴ���\n");
    }
}

// ��ջ
Car* pop(Stack* s)
{
    if (!isStackEmpty(s))
    {
        return s->cars[(s->top)--];
    }
    return NULL;
}

// �жϱ�������Ƿ��
int isLinkEmpty(CNode *head)
{
    return head->next == NULL;
}

// ����������
int enLink(CNode* head, Car* car)
{
    CNode *newNode = (CNode*)malloc(sizeof(CNode));
    if (newNode == NULL)
    {
        printf("�����ڴ�ʧ��\n");
        return 0;
    }
    newNode->car = *car; // ���Ƴ�����Ϣ
    newNode->next = NULL;

    CNode *p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newNode;
    return 1;
}

// ��ѯ������ӳ�������
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

// ɾ�����(ȡ���Ŷӣ�1��ʾɾ���ɹ���0��ʾɾ��ʧ��)
int deLink(CNode *head, char *license_plate)
{
    int j = 0, len = LinkLen(head);
    CNode *p = head;
    CNode *q = NULL;

    // �����������ƥ��ĳ��ƺ�
    while (p != NULL && j <= len)
    {
        q = p; // ���浱ǰ�ڵ�
        p = p->next; // �ƶ�����һ���ڵ�

        // ����Ƿ��ҵ�ƥ��ĳ��ƺ�
        if (p != NULL && strcmp(p->car.license_plate, license_plate) == 0)
            break;

        j++;
    }

    // ���δ�ҵ�ƥ��Ľڵ������Ϊ��
    if (p == NULL)
        return 0;

    // ɾ���ҵ��Ľڵ�
    q->next = p->next; // ��ǰһ���ڵ��nextָ��ɾ���ڵ����һ���ڵ�
    free(p); // �ͷ�ɾ���ڵ���ڴ�

    return 1;
}

// ����ͣ��
void parkCar(Stack* parkingLot, CNode* head)
{
    Car* car = (Car*)malloc(sizeof(Car));
    printf("�����복�ƺ�: ");
    scanf("%s", car->license_plate);
    car->parking_time = time(NULL); // ��¼����ͣ������ʱ��

    if (isStackFull(parkingLot))
    {
        enLink(head, car);
        printf("ͣ��������������ͣ�ڱ���ϣ��ȴ�ͣ���������λ��\n");
    } else
    {
        push(parkingLot, car);
        printf("���� %s ��ͣ��ͣ������\n",car->license_plate);
    }
}

// �����뿪
void leaveCar(Stack* parkingLot, Stack* exit, CNode* head)
{
    if (isStackEmpty(parkingLot))
    {
        printf("ͣ����Ϊ�գ�û�г��������뿪��\n");
        return;
    }

    char find[20]; // ���Ҹó�
    printf("�����복�ƺţ�");
    scanf("%s", find);

    // ����ͣ������Ҫ�뿪�ĳ���
    int found = 0;
    for (int i = parkingLot->top; i >= 0; i--)
    {
        if (strcmp(parkingLot->cars[i]->license_plate, find) == 0)
        {
            found = 1;

            // ������ĳ����ƶ����˳�ջ
            for (int j = parkingLot->top; j > i; j--)
            {
                push(exit, pop(parkingLot));
            }

            // �뿪����
            Car* leavingCar = pop(parkingLot);
            float fee = calculateFee(leavingCar->parking_time);
            if (isEmployeeCar(leavingCar->license_plate))
            {
                fee = 0;
            }
            int second = fee * 10;
            printf("���� %s �뿪ͣ������ͣ��ʱ���� %d �룬ͣ������: %.2f Ԫ\n", leavingCar->license_plate, second, fee);
            free(leavingCar);

            // ���˳�ջ�еĳ�������ͣ����
            while (!isStackEmpty(exit))
            {
                Car* carToReturn = pop(exit);
                push(parkingLot, carToReturn);
            }
            break;
        }
    }

    // ������Ƿ��г������Խ���ͣ����
    if (found ==1 && !isLinkEmpty(head))
    {
        Car* nextCar = dequeue(head);
        nextCar->parking_time = time(NULL); // ��¼����ͣ������ʱ��
        push(parkingLot, nextCar);
        printf("����ϵĳ��� %s ����ͣ����\n", nextCar->license_plate);
    }


    if (!found) {
        int in;  // ���ұ����Ҫ�뿪�ĳ���
        in = deLink(head,find);
        if(in == 1)
        {
            printf("����ϵĳ��� %s �뿪�����շ�\n", find);
        }
        if(in == 0)
        {
            printf("δ�ҵ����ƺ�Ϊ %s �ĳ���\n", find);
        }
    }
}

// �ӱ���г���
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

// ��ʾͣ�����ͱ��
void displayParkingLotAndRoadside(Stack* parkingLot, CNode* head)
{
    if(!isLinkEmpty(head))
    {
        printf("\n=================================================\n");
        printf("= �������: ");
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
        printf("               Ŀǰͣ�����޳���ͣ��              \n");
    }
    printf("=================================================\n");
    printf("=                     ͣ����                     =\n");
    printf("=================================================\n");
    for (int i = MAX_CARS-1; i >= 0; i--)
    {
        if(i <= parkingLot->top)
        {
            int total_time = parkingLot->cars[i]->parking_time;
            int second = total_time % 60;
            int minute = total_time / 60 % 60;
            int hour = (total_time % 86400) / 3600 + 8;  // ����ʱ���Ƕ����������Ҫ��8Сʱ
            printf("=���ƺ�: %10s = ����ͣ�����ı���ʱ��: %02d:%02d:%02d =\n", parkingLot->cars[i]->license_plate,hour,minute, second);
        }
        else
        {
            printf("=                       ��                      =\n");
        }
        printf("=================================================\n");
    }
}

// �ͷű���ϵ�ȫ������
void freeCars(CNode* head)
{
    CNode *p = head->next;
    while (p != NULL)
    {
        CNode *temp = p;
        p = p->next;
        free(temp);
    }
    free(head); // �ͷ�ͷ�ڵ�
}

// ����ͣ������
float calculateFee(time_t parking_time)
{
    time_t current_time = time(NULL);
    float seconds = difftime(current_time, parking_time);
    return seconds * 0.1; // ÿ��0.1Ԫ
}

// ��鳵���Ƿ�ΪԱ������
int isEmployeeCar(const char* license_plate) {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL)
    {
        printf("�޷���Ա�����ƺ��ļ���\n");
        return 0;
    }

    char line[20];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0; // ȥ�����з�
        if (strcmp(line, license_plate) == 0)
        {
            fclose(file);
            return 1; // ��Ա������
        }
    }

    fclose(file);
    return 0; // ����Ա������
}

// ����Ա������
void manageEmployeeCars()
{
    int choice;
    printf("\n============================\n");
    printf("= Ա����������               =\n");
    printf("============================\n");
    printf("= 1. ���Ա�����ƺ�           =\n");
    printf("= 2. ��ʾԱ�����ƺ�           =\n");
    printf("= 3. ɾ��Ա�����ƺ�           =\n");
    printf("= 4. �˳�                   =\n");
    printf("============================\n");
    printf("��ѡ�����: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
        case 1:
        {
            char license_plate[20];
            printf("������Ա�����ƺ�: ");
            scanf("%s", license_plate);
            FILE *file = fopen(EMPLOYEE_FILE, "a");
            if (file == NULL)
            {
                printf("�޷���Ա�����ƺ��ļ���\n");
                return;
            }
            fprintf(file, "%s\n", license_plate);
            fclose(file);
            printf("Ա�����ƺ� %s ����ӡ�\n", license_plate);
            break;
        }
        case 2:
        {
            FILE *file = fopen(EMPLOYEE_FILE, "r");
            if (file == NULL)
            {
                printf("�޷���Ա�����ƺ��ļ���\n");
                return;
            }
            char line[20];
            printf("\n============================\n");
            printf("Ա�����ƺ�:\n");
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
            printf("������Ҫɾ����Ա�����ƺ�: ");
            scanf("%s", license_plate);

            // ��ȡ����Ա�����ƺŲ��ų�Ҫɾ���ĳ��ƺ�
            FILE *file = fopen(EMPLOYEE_FILE, "r");
            if (file == NULL) {
                printf("�޷���Ա�����ƺ��ļ���\n");
                return;
            }

            FILE *temp_file = fopen("temp.txt", "w");
            if (temp_file == NULL) {
                printf("�޷�������ʱ�ļ���\n");
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
                    found = 1; // �ҵ�Ҫɾ���ĳ��ƺ�
                }
            }

            fclose(file);
            fclose(temp_file);

            // �滻ԭ�ļ�
            remove(EMPLOYEE_FILE);
            rename("temp.txt", EMPLOYEE_FILE);

            if (found) {
                printf("Ա�����ƺ� %s ��ɾ����\n", license_plate);
            } else {
                printf("δ�ҵ�Ա�����ƺ� %s��\n", license_plate);
            }
            break;
        }
        case 4:
            break;
        default:
            printf("��Ч��ѡ�������ԡ�\n");
            break;
    }
}