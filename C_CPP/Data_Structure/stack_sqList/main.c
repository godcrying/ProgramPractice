#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define SQSTACK_INIT_SIZE 100
#define SQSTACK_INCREMENT 10

typedef int status;

typedef char *Elemtype; /* 实现的字符串元素线性顺序表，因为要实现通用顺序表，
                    使用Elemtype代替元素类型。 */

typedef struct
{
    Elemtype *base;
    Elemtype *top;
    int stacksize;
    //int length;
} SqStack;

//初始化线性顺序表
status Init_sqstack(SqStack *L)
{
    L->base = malloc(SQSTACK_INIT_SIZE*sizeof(Elemtype));/* malloc函数的功能是按字节分配内存 */
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

//获取栈顶元素
status Gettop(SqStack *S,Elemtype *e)
{
    *e = *(S->top-1);
    return OK;
}

// 元素入栈
status Push(SqStack *S,Elemtype e)
{
    if((S->top-S->base) >= S->stacksize )
    {
        S->base = realloc(S->base,(S->stacksize+SQSTACK_INCREMENT)*sizeof(Elemtype));

        if(!S->base) exit(OVERFLOW);
    }

    *S->top++ = e; /* 此处要多加留意！！涉及到运算符的优先级。 */

    return OK;
}


// 元素出栈
status Pop(SqStack *S,Elemtype *e)
{
    if(S->top == S->base) return ERROR;

    *e = *(--S->top);
    return OK;
}

int main()
{
    SqStack S;
    char *s1="hello,world";
    char *s2="你好，世界";
    char *s3=NULL;

    if(Init_sqstack(&S))
        printf("初始化栈成功！！\n");
    else
        return ERROR;

    Push(&S,s1);
    Push(&S,s2);

    Gettop(&S,&s3);
    printf("栈顶元素为:%s\n",s3);

    while(Pop(&S,&s3))
        printf("%s\n",s3);

    if(Destory_sqstack(&S))
        printf("成功销毁栈！！\n");


    return 0;
}
