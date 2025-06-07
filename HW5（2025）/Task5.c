/***************************************************************
 * 文件编码：GBK
 * Task 5：
 * 按照输入字符串创建二叉树
 * 该函数输入一个先序遍历的二叉树序列，序列中的空指针用$符号代替
 * 当用户输入:+*+5$$3$$2$$+6$$3$$时，输出表达式(5+3)*2+(6+3)的计算结果
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
            return bt->data - '0'; // 将字符转换为数字
    }
}

int main()
{
    printf("任务 5 （Task 5）\n\n");
    TreeNode *root = NULL;
    printf("请输入表达式的先序遍历序列（带有空指针标记'$'）：");
    MakeCharTree(&root);
    int result = RecPostOrder(root);
    printf("表达式的计算结果为：%d\n", result);
    return 0;
}