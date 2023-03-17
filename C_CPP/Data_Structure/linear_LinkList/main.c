#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXLENTH 1000
#define true 1
#define false 0

typedef int status;

typedef struct {
    float xishu;
    int zhishu;
} Elemtype;

typedef struct LinkNode
{
    Elemtype e;
    struct LinkNode *next;
}LinkNode,*Link,*Position;

typedef struct LinkList
{
    Link head,tail; //此处的tail一般不会用到，只有实现栈的效果时配合push和pop来用。
    int len;
} LinkList;


// 生成节点，将指针赋值给p
status MakeNode(Link *p,Elemtype e)
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


/*
* 这里的InsFirst() DelFirst()函数无法更改链表的长度。
* 课本上也没有将链表传入函数中。
*/

//将s指向的结点插入到头节点之后
status InsFirst(Link h,Link s)
{
    s->next = h->next;
    h->next = s;
    return OK;
}

//删除头节点之后的节点
status DelFirst(Link h,Link *q)  //函数定义中不会出现&符号
{
    if(!h->next) return ERROR;

    *q = h->next;
    h->next = h->next->next;

    return OK;
}

/*...因为课本上的基本操作考虑不严密，故不再编写其他基本操作函数了。*/



//有序定位
status LocateElem(LinkList *L,Elemtype e,Position *q,int (* compare)(Elemtype, Elemtype))
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
status Orderinsert(LinkList *L,Elemtype e,int (* compare)(Elemtype,Elemtype))
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


//compare函数
int compare(Elemtype e1,Elemtype e2)
{
    return e1.zhishu > e2.zhishu ? 1 : (e1.zhishu < e2.zhishu ? -1 : 0);

}


typedef LinkList Polynomial;
// 创建多项式P
status Create_polyn(Polynomial *P,int len)
{
    int compare(Elemtype,Elemtype);

    float a;
    int b;

    if(!Init_linklist(P)) return ERROR;

    for (int i=0;i<len;i++)
    {
        scanf("%f%d",&a,&b);
        Elemtype e={a,b};

        if(!Orderinsert(P,e,compare)) return ERROR;
    }
    return OK;
}
/* 这次编程实验暴露几点不足：
* 1.结构体中typedef的用法不熟悉
* 2.对于函数参数到底应该传递地址还是值，很是不上心。该用地址传递的地方使用了值传递，导致程序运行异常。
* 3.对于编译过程中出现的警告信息不上心，导致调试过程浪费了很长的时间。
*/



int main()
{
    Polynomial P;
    if(Create_polyn(&P,5)) printf("创建多项式成功！！");

    printf("多项式长度为：%d\n",P.len);

    Link q = P.head;
    float xishu;
    int zhishu;

    while(q->next)
    {
        xishu = q->next->e.xishu;
        zhishu = q->next->e.zhishu;
        printf("%.2f x %d ",xishu,zhishu);
        q = q->next;
    }

    return 0;
}
