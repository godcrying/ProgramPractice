#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "sortsqlist.h"

//创建列表
status CreateSqList(SqList *L)
{
    for(int i=1;i<=MAXSIZE;i++){
        (L->rec+i)->key = rand()%20+1;
        //此处使用L->rec[i].key调用的话，不能真正改变其值。
        //printf("%d ",L->rec[i].key);
    }
    L->length=MAXSIZE;
    return OK;
}
//输出列表
status PrintSqlist(SqList L)
{
    //printf("该序列为：\n");
    for(int i=1;i<=L.length;i++)
        printf("%d ",L.rec[i].key);
    return OK;
}


//直接插入排序
status InsertSort(SqList *L)
{
    for(int i=2;i<=L->length;i++)
    {
        int j=i-1;
        L->rec[0] = L->rec[i];

        //注意，此处rec[i]会被覆盖掉，不能使用rec[i]进行比较
        //这里每次比较之后都会进行移动，也可以在找到位置之后一起进行移动
        while(L->rec[j].key > L->rec[0].key)
        {
            L->rec[j+1] = L->rec[j];
            j--;
        }

        L->rec[j+1] = L->rec[0];
    }
    return OK;
}

//折半插入排序
status BiInsertSort(SqList *L)
{
    int low=1,high,mid;
    for(int i=2;i<=L->length;i++)
    {
        //每次循环low和high都被修改了，需要重新赋值。
        low=1;
        high=i-1;
        L->rec[0] = L->rec[i];
        while(low <= high)
        {
            mid = (low+high)/2;
            if(L->rec[mid].key > L->rec[0].key) high = mid -1;
            else if(L->rec[mid].key < L->rec[0].key) low = mid +1;
            else break;
        }
        //判断mid值是大于还是小于
        mid = (L->rec[mid].key > L->rec[0].key)?mid-1:mid;

        for(int j=i-1;j>mid;j--)
            L->rec[j+1] = L->rec[j];

        L->rec[mid+1] = L->rec[0];
    }
    return OK;
}

//表插入排序
status TabInsertSort(SqList *L)
{
    L->rec->key = INT_MIN;
    L->rec->next = 1;
    (L->rec+1)->next = 0;

    for(int i=2;i<=L->length;i++)
    {
        int next=L->rec[0].next;
        int old_next=0;
        while(L->rec[next].key < L->rec[i].key&&next!=0)
        {
            old_next = next;
            next = L->rec[next].next;
        }
        (L->rec+old_next)->next = i;
        (L->rec+i)->next = next;
    }
    return 0;
}

//表插入重排
status Arrange(SqList *L)
{
    //printf("out of for!!");
    for(int i=1,next=0;i<=L->length;i++)
    {
        int place=next;
        //printf("place:%d,next:%d",place,next);
        while(place < i)
            place = L->rec[place].next;
        next = L->rec[place].next;

        //互换
        L->rec[0] = L->rec[place];
        L->rec[place] = L->rec[i];
        L->rec[i] = L->rec[0];

        (L->rec+i)->next = place;
    }

    return 0;
}

//希尔排序
status ShellSort(SqList *L)
{
    //注意，最后一次必须是step=1
    for(int step=5;step>0;step-=2)
    {
        for(int i=1;i<=L->length;i+=step)
        {
            int j=i-step;
            L->rec[0] = L->rec[i];
            while(j>0&&L->rec[j].key > L->rec[0].key){
                L->rec[j+step] = L->rec[j];
                j-=step;
            }

            L->rec[j+step] = L->rec[0];
        }
    }
    return OK;
}

//冒泡排序
status BubbleSort(SqList *L)
{
    for(int i=1;i<L->length;i++) //进行n-1次排序
        for(int j=1;j<=L->length-i;j++) //每次进行n-i次对比
            if(L->rec[j].key > L->rec[j+1].key)
            {
                L->rec[0] = L->rec[j];
                L->rec[j] = L->rec[j+1];
                L->rec[j+1] = L->rec[0];
            }

    return OK;
}

/*
快速排序---重点
*/

//快排的定位函数
status Place(SqList *L,int low,int high)
{
    //当某个元素排序完成时，此时的位置就是元素的最终位置。
    int place=low;
    L->rec[0] = L->rec[place];

    int old_low=low,old_high=high;

    if(low >= high)
        return ERROR;

    while(low < high)
    {
        while(low < high && L->rec[high].key > L->rec[0].key) high--;

        L->rec[place] = L->rec[high];
        place = high;
        //不要忘记key相等的情况，否则会造成死循环。
        while(low < high && L->rec[low].key <= L->rec[0].key) low++;

        L->rec[place] = L->rec[low];
        place = low;

    }
    L->rec[place] = L->rec[0];

    //printf("Place is %d",place);
    Place(L,old_low,place-1);
    Place(L,place+1,old_high);

    return OK;
}
//快速排序
status QuickSort(SqList *L)
{
    int high=L->length;
    int low=1;
    Place(L,low,high);
    return OK;
}


//简单选择排序
status SimpleSelectSort(SqList *L)
{
    for(int i=1;i<=L->length;i++)
    {
        int min = i;
        for(int j=i;j<=L->length;j++)
        {
            if(L->rec[min].key > L->rec[j].key)
                min = j;
        }

        L->rec[0] = L->rec[min];
        L->rec[min] = L->rec[i];
        L->rec[i] = L->rec[0];
    }
    return OK;
}

//建立大顶堆
status HeapCreate(SqList *L,int start,int end)
{
    while(start <= end){
        int max = start;
        //注意三个数选最大值的算法
        if(2*start<=end&&L->rec[2*start].key > L->rec[start].key)
        {

            max = 2*start;
        }
        if((2*start+1)<=end && L->rec[2*start+1].key > L->rec[start].key)
        {
            if(L->rec[2*start+1].key>L->rec[2*start].key)
                max=2*start+1;
        }

        if(max == start)
            break;

        L->rec[0]=L->rec[start];
        L->rec[start] = L->rec[max];
        L->rec[max] = L->rec[0];
        start = max;
    }
    return OK;
}


//堆排序
status HeapSort(SqList *L)
{
    int len = L->length;
    for(int i=len/2;i>0;i--)
        HeapCreate(L,i,len);

    while(len>0){
       // PrintSqlist(*L);
       // printf("\n");
        L->rec[0]=L->rec[len];
        L->rec[len] = L->rec[1];
        L->rec[1] = L->rec[0];
        len--;
        HeapCreate(L,1,len);
    }
    return OK;
}
