#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define true 1
#define false 0
#define OVERFLOW -2

//循环列表（队列）只能是固定长度，没有增量。
#define MAXLENGTH 100

typedef int status;

typedef char* Elemtype;

typedef struct {
    Elemtype *base;
    int head;
    int tail;
}SqQueue;

//初始化循环列表（队列）
status Init_SqQueue(SqQueue *Q)
{
    Q->base = (Elemtype *)malloc(MAXLENGTH * sizeof(Elemtype));
    if(!Q->base) exit(OVERFLOW);

    Q->head = 0;
    Q->tail = 0;

    return OK;
}

//销毁循环列表（队列）
status Destory_SqQueue(SqQueue *Q)
{
    free(Q->base);
    return OK;
}

//插入队列
status Insert_SqQueue(SqQueue *Q,Elemtype e)
{
    if((Q->tail+1)%MAXLENGTH == Q->head) return ERROR;

    *(Q->base+Q->tail) = e;
    Q->tail = (Q->tail+1)%MAXLENGTH;
    return OK;
}

//删除队列
status Delete_SqQueue(SqQueue *Q,Elemtype *e)
{
    if(Q->head == Q->tail) return ERROR;
    *e = *(Q->base+Q->head);
    Q->head = (Q->head+1) % MAXLENGTH;
    return OK;
}

//获取队列长度
int SqQueue_Length(SqQueue Q)
{
    //这里需要好好看一下，这是个数学问题。

    return (Q.tail-Q.head+MAXLENGTH) % MAXLENGTH;
}



int main()
{
    SqQueue Q;
    char *s1="Hello，World";
    char *s2="你好，世界";
    char *s3=NULL;

    if(Init_SqQueue(&Q))
        printf("初始化队列成功！！\n");
    else
        exit(ERROR);

    Insert_SqQueue(&Q,s1);
    Insert_SqQueue(&Q,s2);

    printf("队列长度为：%d\n",SqQueue_Length(Q));
    int len = SqQueue_Length(Q);
    for(int i=0;i<len;i++)
    {
        Delete_SqQueue(&Q,&s3);
        printf("%s\n",s3);
    }

    if(Destory_SqQueue(&Q))
        printf("成功销毁队列！！");
    return 0;
}
