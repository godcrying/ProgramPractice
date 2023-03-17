#ifndef MYSTRUCT_H_INCLUDED
#define MYSTRUCT_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXINFOLINE 10
#define true 1
#define false 0

typedef int status;

/*
*线性顺序表结构
*/
#define SQList_INIT_SIZE 100
#define SQLIST_INCREMENT 10

typedef char *SqListElemtype; /* 实现的字符串元素线性顺序表，因为要实现通用顺序表，
                         使用Elemtype代替元素类型。 */
typedef struct
{
    SqListElemtype *elem;
    int listsize;
    int length;
} SqList;

status Init_sqlist(SqList *L);
status Destory_sqlist(SqList *L);
status Getelem_sqlist(SqList *L,SqListElemtype *e,int i);
status Insert_sqlist(SqList *L,SqListElemtype e,int i);
status Delete_sqlist(SqList *L,SqListElemtype *e,int i);

/*
*线性链表结构
*/

typedef struct {
    float xishu;
    int zhishu;
} LinkListElemtype;

typedef struct LinkNode
{
    LinkListElemtype e;
    struct LinkNode *next;
}LinkNode,*Link,*Position;

typedef struct LinkList
{
    Link head,tail; //此处的tail一般不会用到，只有实现栈的效果时配合push和pop来用。
    int len;
} LinkList;

status MakeNode(Link *p,LinkListElemtype e);
void FreeNode(Link p);
status Init_linklist(LinkList *P);
status Destory_linklist(LinkList *L);
status Clear_linklist(LinkList *L);
status LocateElem(LinkList *L,LinkListElemtype e,Position *q,int (* compare)(LinkListElemtype, LinkListElemtype));
status Orderinsert(LinkList *L,LinkListElemtype e,int (* compare)(LinkListElemtype,LinkListElemtype));

/*
*队列
*/
typedef char* LqElemtype;

typedef struct LqNode{
    LqElemtype e;
    struct LqNode* next;
} LqNode,*LqLink;

typedef struct {
    LqLink head,rear;
} LinkQueue;


/*
*栈结构
*/
#define SQSTACK_INIT_SIZE 100
#define SQSTACK_INCREMENT 10
typedef void* StackElemtype;

typedef struct
{
    StackElemtype *base;
    StackElemtype *top;
    int stacksize;
    //int length;
} SqStack;

status Init_sqstack(SqStack *L);
status Destory_sqstack(SqStack *L);
status Gettop(SqStack *S,StackElemtype *e);
status Push(SqStack *S,StackElemtype e);
status Pop(SqStack *S,StackElemtype *e);
status Isempty(SqStack S);

/*
*二叉树结构
*/

typedef enum{LinkTag=0,ThreadTag=1} PointTag;

typedef int BiTreeElemtype;
typedef int Keytype;
typedef struct BiTNode{
    Keytype key;
    BiTreeElemtype elem;
    struct BiTNode *lchild, *rchild;
    PointTag LTag,RTag;//线索化所需的标签
}BiTNode,*BiTree;

status CreateBiTree(BiTree*);

status PreOrderTraverse(BiTree,void (*)(BiTNode));
status InOrderTraverse(BiTree,void (*)(BiTNode));
status InOrderTraverse_no_recursive(BiTree,void (*)(BiTNode));

//生成线索二叉树
status InOrderThreading(BiTree*,BiTree);
//中序遍历线索二叉树
status InOrderTraverse_Thr(BiTree,void (*)(BiTNode));

//生成二叉排序树
status CreateBSTree(BiTree*);

//查询二叉排序树的元素
status SearchBSTree(BiTree,BiTNode,BiTree*,int (*compare)(BiTNode,BiTNode));

//元素插入二叉排序树
status InsertBSTree(BiTree,BiTNode*,int (*compare)(BiTNode,BiTNode));

//图

#endif // MYSTRUCT_H_INCLUDED
