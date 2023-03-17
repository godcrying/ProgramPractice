#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define SQList_INIT_SIZE 100
#define SQLIST_INCREMENT 10

typedef int status;

typedef char *Elemtype; /* 实现的字符串元素线性顺序表，因为要实现通用顺序表，
                    使用Elemtype代替元素类型。 */

typedef struct
{
    Elemtype *elem;
    int listsize;
    int length;
} SqList;

//初始化线性顺序表
status Init_sqlist(SqList *L)
{
    L->elem = malloc(SQList_INIT_SIZE*sizeof(Elemtype));/* malloc函数的功能是按字节分配内存 */
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
status Getelem_sqlist(SqList *L,Elemtype *e,int i)
{
    if(i<1 || i>L->length + 1) return ERROR;

    *e = *(L->elem+i-1);
    return OK;
}

// 在指定位置之前插入元素
status Insert_sqlist(SqList *L,Elemtype e,int i)
{
    int len=L->length;
    if(i< 1 || i > L->length+1) return ERROR;
    if((len+1)*sizeof(e) > L->listsize){
        L->elem = realloc(L->elem, (L->listsize += SQLIST_INCREMENT)*sizeof(Elemtype));
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
status Delete_sqlist(SqList *L,Elemtype *e,int i) // 这里需要修改字符串指针的值。所以需要用到二级指针。
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

int main()
{
    SqList L;
    char *s = "Hello, World";
    char *s1 ="你好，世界";
    char *s2 =0;

    if(Init_sqlist(&L)){
        printf("初始化线性表成功！！\n");
        printf("线性表初始化字节数为：%lu\n",sizeof(*L.elem)); //sizeof无法测定动态分配的内存大小
    }
    if(Insert_sqlist(&L,s,1) && Insert_sqlist(&L,s1,2)){
        printf("成功插入字符串\n");
        for(int i=0;i<L.length;i++)
        {
            printf("%s\n",*(L.elem+i));
        }
    }
    if(Delete_sqlist(&L,&s2,2)) // 此处需要改变指针所s2的值，所以需要向函数传递变量地址。
    {
        printf("成功删除字符串\n");
        printf("已删除字符串：%s\n",s2);
        for(int i=0;i<L.length;i++)
        {
            printf("剩余字符串：%s\n",*(L.elem+i));
        }
    }
    if(Destory_sqlist(&L))
        printf("成功销毁线性表！！\n");

    return 0;
}
