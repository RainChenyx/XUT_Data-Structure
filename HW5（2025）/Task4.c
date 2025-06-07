/******************************************************
 * 文件编码：GBK
 * Task 4
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct treenode {
    DataType data;
    struct treenode * leftChild;
    struct treenode * rightChild;
}TreeNode;

void Initiate(TreeNode **root) {
    *root = (TreeNode *)malloc(sizeof(TreeNode));
    (*root)->leftChild = NULL;
    (*root)->rightChild = NULL;
}

/* curr指针所指结点的左孩子处插入新结点，以前的左孩子变成新节点的左孩子 */
TreeNode *InsertLeftNode(TreeNode *curr, DataType x) {
    TreeNode *s, *t;
    if (curr == NULL)  // 当前指针为空，没有指向有效结点
        return NULL;
    t = curr->leftChild;
    s = (TreeNode *)malloc(sizeof(TreeNode));
    s->data = x;
    s->leftChild = t;
    s->rightChild = NULL;
    curr->leftChild = s;
    return curr->leftChild;
}

/* curr指针所指结点的右孩子处插入新结点，以前的右孩子变成新节点的右孩子 */
TreeNode *InsertRightNode(TreeNode *curr, DataType x) {
    TreeNode *s, *t;
    if(curr == NULL)
        return NULL;
    t = curr->rightChild;
    s = (TreeNode *)malloc(sizeof(TreeNode));
    s->data = x;
    s->rightChild = t;
    s->leftChild = NULL;
    curr->rightChild = s;
    return curr->rightChild;
}

void PrintBiTree(TreeNode *bt, int n) {
    int i;
    if (bt == NULL) return;
    PrintBiTree(bt->rightChild, n+1);
    for (i = 0; i < n-1; i++) printf("   ");
    if (n > 0) {
        printf("---");
        printf("%c\n", bt->data);
    }
    PrintBiTree(bt->leftChild, n+1);
}

int TreeHight(TreeNode *bt)
{
    if (bt == NULL)
        return 0;
    int left = TreeHight(bt->leftChild);
    int right = TreeHight(bt->rightChild);
    return (left>right?left:right)+1;
}

int main()
{
    printf("任务 4 （Task 4）\n\n");
    int hight;
    TreeNode *root1, *n;
    Initiate(&root1);
    n = InsertLeftNode(root1, 'A');
    InsertLeftNode(n,'B');
    InsertRightNode(n, 'C');
    hight = TreeHight(root1->leftChild);
    PrintBiTree(root1->leftChild, 1);
    printf("root1 的二叉树高度为：%d\n\n",hight);

    TreeNode *root2, *m, *mm;
    Initiate(&root2);
    m = InsertLeftNode(root2, 'A');
    m = InsertLeftNode(m, 'B');
    mm = m;
    m = InsertLeftNode(m,'D');
    mm = InsertRightNode(mm, 'E');
    InsertLeftNode(mm, 'H');
    m = InsertRightNode(root2->leftChild, 'C');
    mm = m;
    m = InsertLeftNode(m, 'F');
    InsertRightNode(mm, 'G');
    InsertRightNode(m, 'I');
    hight = TreeHight(root2->leftChild);
    PrintBiTree(root2->leftChild, 1);
    printf("root2 的二叉树高度为：%d\n",hight);
    return 0;
}