#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define true 1
#define false 0
#define OVERFLOW -2

typedef int status;

typedef char* Elemtype;

typedef struct LNode{
    Elemtype e;
    struct LNode* next;
} LNode,*Link;

typedef struct {
    Link head,rear;
} LinkQueue;

//初始化队列
status Init_LinkQueue(LinkQueue *Q)
{
    Q->head = Q->rear = (Link)malloc(sizeof(LNode));
    if(!Q->head) exit(OVERFLOW);

    Q->head->next = NULL;
    return OK;
}

//销毁队列
status Destory_LinkQueue(LinkQueue *Q)
{
    while(Q->head)
    {
        Q->rear = Q->head->next;
        free(Q->head);
        Q->head = Q->rear;
    }
    return OK;
}

//插入队尾
status Insert_LinkQueue(LinkQueue *Q,Elemtype e)
{
    //这里不用局部变量也可以，但是使用局部变量可以使代码更清晰。
    Link q = (Link)malloc(sizeof(LNode));
    if(!q) return ERROR;

    q->e = e;
    q->next = NULL;
    Q->rear->next = q;
    Q->rear = q;

    return OK;
}

//删除队头
status Delete_LinkQueue(LinkQueue *Q,Elemtype *e)
{
    if(Q->head == Q->rear) return ERROR;

    Link q = Q->head->next;
    *e = q->e;
    Q->head->next = q->next;

    if(Q->rear == q) Q->rear = Q->head;
    free(q);

    return OK;
}

//获取队头元素
status GetHead(LinkQueue *Q,Elemtype *e)
{
    if(Q->head == Q->rear) return ERROR;
    *e = Q->head->next->e;
    return OK;
}

int main()
{
    LinkQueue Q;
    char *s1="Hello，World";
    char *s2="你好，世界";
    char *s3=NULL;

    if(Init_LinkQueue(&Q))
        printf("初始化队列成功！！\n");
    else
        exit(ERROR);

    Insert_LinkQueue(&Q,s1);
    Insert_LinkQueue(&Q,s2);

    for(int i=0;i<(Q.rear-Q.head);i++)
    {
        Delete_LinkQueue(&Q,&s3);
        printf("%s\n",s3);
    }

    if(Destory_LinkQueue(&Q))
        printf("成功销毁队列！！");
    return 0;
}
