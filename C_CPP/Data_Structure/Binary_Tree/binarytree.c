#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

status CreateBiTree(BiTree *T){
    int data;
    scanf("%d",&data);
    if(data==-1)
        *T = NULL;
    else{
        if(!(*T = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        (*T)->elem = data;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
    return OK;
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTNode))
{
    if(T){
        (*visit)(*T);
        PreOrderTraverse(T->lchild,visit);
        PreOrderTraverse(T->rchild,visit);
    }
    return OK;
}

status InOrderTraverse(BiTree T,void (*visit)(BiTNode))
{
    if(T->lchild)
        InOrderTraverse(T->lchild,visit);
    (*visit)(*T);
    if(T->rchild)
        InOrderTraverse(T->rchild,visit);
    return OK;
}

status InOrderTraverse_no_recursive(BiTree T,void (*visit)(BiTNode))
{

    SqStack S;
    Init_sqstack(&S);
    BiTree bn = T;
    while(bn||!Isempty(S))
    {
        /*
        *此处，如果写成if(bn->lchild)的形式，会使最左边的bn变成没有入栈特例，无法与栈中的元素进行相同
        *操作(即，先pop()，再visit())。增加了程序的复杂性。
        */
        if(bn){
            Push(&S,bn);
            bn = bn->lchild;
        }
        else{
            void* bn_tmp;
            Pop(&S,&bn_tmp);
            bn = (BiTree)bn_tmp;
            (*visit)(*bn);
            bn = bn->rchild;
        }
    }
    return OK;
}


/*
*栈的代码
*/
//初始化线性顺序表
status Init_sqstack(SqStack *L)
{
    L->base = malloc(SQSTACK_INIT_SIZE*sizeof(StackElemtype));/* malloc函数的功能是按字节分配内存 */
    if(!L->base) exit(OVERFLOW);
    L->top = L->base;
    L->stacksize = SQSTACK_INIT_SIZE; //以元素的存储大小为单位，此处为sizeof(char*)
   // L->length = 0;
    return OK;
}

// 销毁线性表
status Destory_sqstack(SqStack *L)
{
    if(L->base){
        free(L->base);
        return OK;
    }
    return ERROR;
}

status Isempty(SqStack S)
{
    if(S.base == S.top)
        return true;
    else
        return false;
}

//获取栈顶元素
status Gettop(SqStack *S,StackElemtype *e)
{
    *e = *(S->top-1);
    return OK;
}

// 元素入栈
status Push(SqStack *S,StackElemtype e)
{
    if((S->top-S->base) >= S->stacksize )
    {
        S->base = realloc(S->base,(S->stacksize+SQSTACK_INCREMENT)*sizeof(StackElemtype));

        if(!S->base) exit(OVERFLOW);
    }

    *S->top++ = e; /* 此处要多加留意！！涉及到运算符的优先级。 */

    return OK;
}

// 元素出栈
status Pop(SqStack *S,StackElemtype *e)
{
    if(S->top == S->base) return ERROR;

    *e = *(--S->top);
    return OK;
}
