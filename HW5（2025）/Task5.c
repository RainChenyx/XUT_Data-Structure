/***************************************************************
 * �ļ����룺GBK
 * Task 5��
 * ���������ַ�������������
 * �ú�������һ����������Ķ��������У������еĿ�ָ����$���Ŵ���
 * ���û�����:+*+5$$3$$2$$+6$$3$$ʱ��������ʽ(5+3)*2+(6+3)�ļ�����
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct treenode {
    DataType data;
    struct treenode * leftChild;
    struct treenode * rightChild;
}TreeNode;

void MakeCharTree(TreeNode **bt) {
    char ch;
    ch = getchar();
    if (ch == '$')
        *bt = NULL;
    else {
        *bt = (TreeNode*)malloc(sizeof(TreeNode));
        (*bt)->data = ch;
        MakeCharTree(&((*bt)->leftChild));
        MakeCharTree(&((*bt)->rightChild));
    }
}

int RecPostOrder(TreeNode *bt)
{
    if (bt == NULL)
        return 0;
    int left = RecPostOrder(bt->leftChild);
    int right = RecPostOrder(bt->rightChild);
    switch (bt->data) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        default:
            return bt->data - '0'; // ���ַ�ת��Ϊ����
    }
}

int main()
{
    printf("���� 5 ��Task 5��\n\n");
    TreeNode *root = NULL;
    printf("��������ʽ������������У����п�ָ����'$'����");
    MakeCharTree(&root);
    int result = RecPostOrder(root);
    printf("���ʽ�ļ�����Ϊ��%d\n", result);
    return 0;
}