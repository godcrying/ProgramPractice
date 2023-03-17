#include <stdio.h>
#include <stdlib.h>
#include "mystruct.h"

//初始化线性顺序表
status Init_sqlist(SqList *L)
{
    L->elem = malloc(SQList_INIT_SIZE*sizeof(SqListElemtype));/* malloc函数的功能是按字节分配内存 */
    if(!L->elem) exit(OVERFLOW);
    L->listsize = SQList_INIT_SIZE; //以元素的存储大小为单位，此处为sizeof(char*)
    L->length = 0;
    return OK;
}

// 销毁线性表
status Destory_sqlist(SqList *L)
{
    if(L->elem){
        free(L->elem);
        return OK;
    }
    return ERROR;
}

// 获取指定位置的元素
status Getelem_sqlist(SqList *L,SqListElemtype *e,int i)
{
    if(i<1 || i>L->length + 1) return ERROR;

    *e = *(L->elem+i-1);
    return OK;
}

// 在指定位置之前插入元素
status Insert_sqlist(SqList *L,SqListElemtype e,int i)
{
    int len=L->length;
    if(i< 1 || i > L->length+1) return ERROR;
    if((len+1)*sizeof(e) > L->listsize){
        L->elem = realloc(L->elem, (L->listsize += SQLIST_INCREMENT)*sizeof(SqListElemtype));
        printf("After realloc\n");
    }

    if(!L->elem) exit(OVERFLOW);

    while(len >= i)
    {
        *(L->elem+len) = *(L->elem+len-1);
        len--;
    }
    *((L->elem)+i-1) = e;
    L->length++;
    return OK;
}

// 删除指定位置的元素
status Delete_sqlist(SqList *L,SqListElemtype *e,int i) // 这里需要修改字符串指针的值。所以需要用到二级指针。
{
    if(i < 1 || i > L->length) return ERROR;
    *e = *(L->elem+i-1);
    while(i<L->length)
    {
        *(L->elem+i-1) = *(L->elem+i);
        i++;
    }
    L->length--;
    return OK;
}
