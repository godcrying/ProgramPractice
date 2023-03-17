#include <stdio.h>
#include <stdlib.h>
#include "mystruct.h"

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
