#include <stdio.h>
#include <stdlib.h>
#include "mystruct.h"

// 生成节点，将指针赋值给p
status MakeNode(Link *p,LinkListElemtype e)
{
    *p = (Link)malloc(sizeof(LinkNode));
    if(!p) return ERROR;
    (*p)->e = e;
    (*p)->next = NULL;
    return OK;
}

// 释放节点p
void FreeNode(Link p)
{
    free(p);
}

// 初始化链表
status Init_linklist(LinkList *P)
{
    Link head = (Link)malloc(sizeof(LinkNode));
    if(!head) return ERROR;
    head->next = NULL;
    P->head = head;
    P->tail = head;  //初始化时，一般将tail指向head。
    P->len = 0;
    return OK;
}

//销毁链表
status Destory_linklist(LinkList *L)
{
    if(!L) return ERROR;
    Link p = L->head->next;
    while(p)
    {
        Link q = p->next;
        FreeNode(p);
        p=q;
    }
    FreeNode(L->head);
    return OK;
}

//清空链表
status Clear_linklist(LinkList *L)
{
    Link p = L->head->next;
    while(p)
    {
        Link q = p->next;
        FreeNode(p);
        p=q;
    }
    L->len = 0;
    return OK;
}


/*...因为课本上的基本操作考虑不严密，故不再编写其他基本操作函数了。*/



//有序定位
status LocateElem(LinkList *L,LinkListElemtype e,Position *q,int (* compare)(LinkListElemtype, LinkListElemtype))
{
    Link node = L->head;
    while(node->next)
    {
        int res = (* compare)(node->next->e,e);
        if(res==0)
        {
            *q=node->next;
            return true;
        }
        else if(res >0)
        {
            *q=node;
            return false;
        }
        node = node->next;
    }
    *q = node;
    return false;
}

// 有序插入。其中compare(A,B) > 0时，A > B.
status Orderinsert(LinkList *L,LinkListElemtype e,int (* compare)(LinkListElemtype,LinkListElemtype))
{
        //使用LocateElem函数
    Position q=NULL;
    LocateElem(L,e,&q,compare);

    Link newnode=NULL;
    MakeNode(&newnode,e); //生成新节点
    if(!newnode) return ERROR;

    if(!q->next) L->tail = newnode;
    newnode->next = q->next;
    q->next = newnode;
    L->len +=1;
    return OK;
}
