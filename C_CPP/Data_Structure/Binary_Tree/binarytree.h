#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXINFOLINE 10
#define true 1
#define false 0

#define SQSTACK_INIT_SIZE 100
#define SQSTACK_INCREMENT 10


typedef int status;

typedef int Elemtype;

typedef struct BiTNode{
    Elemtype elem;
    struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

typedef void* StackElemtype;

typedef struct
{
    StackElemtype *base;
    StackElemtype *top;
    int stacksize;
    //int length;
} SqStack;

status CreateBiTree(BiTree*);
status PreOrderTraverse(BiTree,void (*)(BiTNode));
status InOrderTraverse(BiTree,void (*)(BiTNode));
status InOrderTraverse_no_recursive(BiTree,void (*)(BiTNode));

status Init_sqstack(SqStack *L);
status Destory_sqstack(SqStack *L);
status Gettop(SqStack *S,StackElemtype *e);
status Push(SqStack *S,StackElemtype e);
status Pop(SqStack *S,StackElemtype *e);
status Isempty(SqStack S);

#endif // BINARYTREE_H_INCLUDED
