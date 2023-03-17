#include <stdio.h>
#include <stdlib.h>
#include "mystruct.h"

//创建二叉树
status CreateBiTree(BiTree *T){
    int data;
    scanf("%d",&data);
    if(data==-1)
        *T = NULL;
    else{
        if(!(*T = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        (*T)->elem = data;
        (*T)->key = data;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
    return OK;
}

//先序遍历
status PreOrderTraverse(BiTree T,void (*visit)(BiTNode))
{
    if(T){
        (*visit)(*T);
        PreOrderTraverse(T->lchild,visit);
        PreOrderTraverse(T->rchild,visit);
    }
    return OK;
}

//中序遍历
status InOrderTraverse(BiTree T,void (*visit)(BiTNode))
{
    if(T->lchild)
        InOrderTraverse(T->lchild,visit);
    (*visit)(*T);
    if(T->rchild)
        InOrderTraverse(T->rchild,visit);
    return OK;
}

//中序遍历，非递归
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

//中序遍历线索化
status InOrderThreading(BiTree *Thr,BiTree T)
{
    if(!(*Thr = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
    (*Thr)->lchild = T; (*Thr)->LTag = LinkTag; (*Thr)->rchild = *Thr;
    (*Thr)->RTag = LinkTag;

    BiTree pre = *Thr;
    SqStack S;
    Init_sqstack(&S);
    BiTree bn = T;
    while(bn||!Isempty(S))
    {
        if(bn){
            Push(&S,bn);
            bn = bn->lchild;
        }
        else{
            void* bn_tmp;
            Pop(&S,&bn_tmp);
            bn = (BiTree)bn_tmp;
            if(!bn->lchild){bn->lchild = pre;bn->LTag=ThreadTag;}
            if(!pre->rchild){pre->rchild = bn;pre->RTag = ThreadTag;}
            pre = bn;
            bn = bn->rchild;
        }
    }
    (*Thr)->rchild = pre;(*Thr)->RTag = ThreadTag;pre->rchild = *Thr;pre->RTag = ThreadTag;
    return OK;
}

//中序线索化遍历
status InOrderTraverse_Thr(BiTree T,void (*visit)(BiTNode))
{
    BiTree bn=T->lchild;
    while(bn!=T){
        if(bn->LTag == LinkTag)  //所有的bn都有lchild，所以此处不能使用if(bn->lchild)做判断条件
            bn = bn->lchild;
        else {
            (*visit)(*bn);
            if(bn->RTag == ThreadTag && bn->rchild !=T) //此处别忘了考虑最后一个节点的后继是头节点的情况。
            {
                bn = bn->rchild;
                (*visit)(*bn);
            }
            if(bn->RTag == LinkTag || bn->rchild == T)
                bn = bn->rchild;
        }
    }
    return OK;
}


/*
*二叉排序树无法使用线索二叉树，所以使用时务必不要线索化。
*/

#define EQ(a,b) ((*compare)(a,b) == 0)
#define LT(a,b) ((*compare)(a,b) < 0)
#define LQ(a,b) ((*compare)(a,b) <= 0)

//查询二叉排序树的元素
//先序遍历查询
status SearchBSTree(BiTree BST,BiTNode bn,BiTree *bt,int (*compare)(BiTNode,BiTNode))
{
    if(!BST) return false;
    //printf("当前比较的元素为：%d\n",BST->elem);
    *bt = BST;
    if(EQ(bn,*BST)) return true;

    if(LT(bn,*BST)){
        return SearchBSTree(BST->lchild,bn,bt,compare);
        //此处使用的是尾递归的形式。
        //作用：1.使最后一次递归调用的返回值成为真正的返回值
        //2.可以避免 stack overflow的错误。
    }else{
        return SearchBSTree(BST->rchild,bn,bt,compare);
    }
}

//元素插入二叉排序树
status InsertBSTree(BiTree BST,BiTNode* bn,int (*compare)(BiTNode,BiTNode))
{
    BiTree bn_tmp;
    if(SearchBSTree(BST,*bn,&bn_tmp,compare)){
        printf("该元素已存在！！\n");
        return ERROR;
    }

    if(LT(*bn,*bn_tmp))
        bn_tmp->lchild = bn;
    else
        bn_tmp->rchild = bn;

    return OK;
}

//元素以平衡方式插入二叉排序树


//删除二叉排序树某个节点


//删除某个二叉平衡树某个节点


//生成二叉排序树

//生成二叉平衡树
