#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 5 // ͣ�����������

// �����ṹ��
typedef struct Car {
    char license_plate[20]; // ���ƺ�
    int parking_time; // ͣ��ʱ�䣨��λ���룩
} Car;

// ����������
typedef struct carNode {
    Car car;
    struct carNode *next; // �������һ������
} CNode;

// ͣ����ջ & �˳�ջ
typedef struct Stack {
    Car* cars[MAX_CARS];
    int top;
} Stack;

// ��ʼ���������
void initLink(CNode **head) {
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
void displayParkingLot(Stack* parkingLot);
void displayRoadside(CNode* head);
void freeCars(CNode* head);

int main() {
    Stack parkingLot;
    Stack exit;
    CNode *head;
    initLink(&head);  // ��ʼ�����Link
    initStack(&parkingLot); // ��ʼ��ͣ����Stack
    initStack(&exit); // ��ʼ���˳�ջStack

    int choice;
    while (1) {
        printf("\nͣ��������ϵͳ\n");
        printf("1. ͣ��\n");
        printf("2. �뿪\n");
        printf("3. ��ʾͣ����\n");
        printf("4. ��ʾ���\n");
        printf("5. �˳�\n");
        printf("��ѡ�����: ");
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
                printf("��Ч��ѡ�������ԡ�\n");
        }
        if(choice == 5)
            break;
    }
    return 0;
}

// ��ʼ��ͣ����ջ
void initStack(Stack* s) {
    s->top = -1;
}

// �ж�ջ�Ƿ���
int isStackFull(Stack* s) {
    return s->top == MAX_CARS - 1;
}

// �ж�ջ�Ƿ��
int isStackEmpty(Stack* s) {
    return s->top == -1;
}

// ��ջ
void push(Stack* s, Car* car) {
    if (!isStackFull(s)) {
        s->cars[++(s->top)] = car;
    } else {
        printf("ͣ�������������ڱ�����Ŷӵȴ���\n");
    }
}

// ��ջ
Car* pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->cars[(s->top)--];
    }
    return NULL;
}

// �жϱ�������Ƿ��
int isLinkEmpty(CNode *head) {
    return head->next == NULL;
}

// ����������
int enLink(CNode* head, Car* car) {
    CNode *newNode = (CNode*)malloc(sizeof(CNode));
    if (newNode == NULL) {
        printf("�����ڴ�ʧ��\n");
        return 0;
    }
    newNode->car = *car; // ���Ƴ�����Ϣ
    newNode->next = NULL;

    CNode *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
    return 1;
}

// ��ѯ������ӳ�������
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

// ɾ�����(ȡ���Ŷӣ�1��ʾɾ���ɹ���0��ʾɾ��ʧ��)
int deLink(CNode *head, char *license_plate) {
    int j = 0, len = LinkLen(head);
    CNode *p = head;
    CNode *q = NULL;

    // �����������ƥ��ĳ��ƺ�
    while (p != NULL && j <= len) {
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

// ͣ��
void parkCar(Stack* parkingLot, CNode* head) {
    Car* car = (Car*)malloc(sizeof(Car));
    printf("�����복�ƺ�: ");
    scanf("%s", car->license_plate);

    if (isStackFull(parkingLot)) {
        enLink(head, car);
        printf("ͣ��������������ͣ�ڱ���ϣ��ȴ�ͣ���������λ��\n");
    } else {
        push(parkingLot, car);
        printf("������ͣ��ͣ������\n");
    }
}

// �뿪
void leaveCar(Stack* parkingLot, Stack* exit, CNode* head) {
    if (isStackEmpty(parkingLot)) {
        printf("ͣ����Ϊ�գ�û�г��������뿪��\n");
        return;
    }

    char find[20]; // ���Ҹó�
    printf("�����복�ƺţ�");
    scanf("%s", find);

    // ����ͣ������Ҫ�뿪�ĳ���
    int found = 0;
    for (int i = parkingLot->top; i >= 0; i--) {
        if (strcmp(parkingLot->cars[i]->license_plate, find) == 0) {
            found = 1;

            // ������ĳ����ƶ����˳�ջ
            for (int j = parkingLot->top; j > i; j--) {
                push(exit, pop(parkingLot));
            }

            // �뿪����
            Car* leavingCar = pop(parkingLot);
            printf("���� %s �뿪ͣ������ͣ��ʱ��: %d �룬����: %d Ԫ\n",
                   leavingCar->license_plate, leavingCar->parking_time, leavingCar->parking_time * 5);
            free(leavingCar);

            // ���˳�ջ�еĳ�������ͣ����
            while (!isStackEmpty(exit)) {
                Car* carToReturn = pop(exit);
                push(parkingLot, carToReturn);
            }
            break;
        }
    }

    // ������Ƿ��г������Խ���ͣ����
    if (found ==1 && !isLinkEmpty(head)) {
        Car* nextCar = dequeue(head);
        push(parkingLot, nextCar);
        printf("����ϵĳ��� %s ����ͣ����\n", nextCar->license_plate);
    }


    if (!found) {
        int in;  // ���ұ����Ҫ�뿪�ĳ���
        in = deLink(head,find);
        if(in == 1)
        {
            printf("����ϵĳ��� %s �뿪\n", find);
        }
        if(in == 0)
        {
            printf("δ�ҵ����ƺ�Ϊ %s �ĳ���\n", find);
        }
    }
}

// �ӱ���г���
Car* dequeue(CNode* head) {
    if (isLinkEmpty(head)) {
        return NULL;
    }
    CNode* firstNode = head->next;
    head->next = firstNode->next;
    Car* car = (Car*)malloc(sizeof(Car));
    *car = firstNode->car; // ���Ƴ�����Ϣ
    free(firstNode);
    return car;
}

// ��ʾͣ����
void displayParkingLot(Stack* parkingLot) {
    if (isStackEmpty(parkingLot)) {
        printf("ͣ����Ϊ�ա�\n");
        return;
    }
    printf("ͣ��������:\n");
    for (int i = parkingLot->top; i >= 0; i--) {
        printf("���ƺ�: %s, ͣ��ʱ��: %d ��\n", parkingLot->cars[i]->license_plate, parkingLot->cars[i]->parking_time);
    }
}

// ��ʾ���
void displayRoadside(CNode* head) {
    if (isLinkEmpty(head)) {
        printf("���Ϊ�ա�\n");
        return;
    }
    printf("�������:\n");
    CNode *current = head->next;
    while (current != NULL) {
        printf("���ƺ�: %s\n", current->car.license_plate);
        current = current->next;
    }
}

// �ͷű���ϵ�ȫ������
void freeCars(CNode* head) {
    CNode *p = head->next;
    while (p != NULL) {
        CNode *temp = p;
        p = p->next;
        free(temp);
    }
    free(head); // �ͷ�ͷ�ڵ�
}