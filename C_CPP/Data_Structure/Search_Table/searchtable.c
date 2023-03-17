#include <stdio.h>
#include <stdlib.h>
#include "searchtable.h"

//创建查询表
status Create(SStable *SST,int len)
{
    SElemType *base = (SElemType *)malloc((len+1)*sizeof(SElemType));
    if( base == NULL)
        exit(OVERFLOW);

    SST->base = base;
    SST->length = len;

    for(int i=1;i<len+1;i++){
        printf("请输入第%d个元素的内容：",i);
        scanf("%s",(base+i)->info);
        printf("请输入元素关键字（非负整数）：");
        scanf("%d",&((base+i)->key));
    }

    return OK;
}

//销毁查询表
status Destory(SStable *SST)
{
    free(SST->base);
    return OK;
}

//顺序查询，返回查询到的元素位置
int SeqSearch(SStable SST,Keytype key)
{
    int len = SST.length;

    SST.base[0].key = key;
    while(SST.base[len].key!=key) len--;

    return len;
}

//二分法查询（折半查询）
int BinarySearch(SStable SST,Keytype key)
{
    int low = 1,high = SST.length;
    while(low<=high){
        int mid = (low+high)/2;
        if(SST.base[mid].key == key)
            return mid;

        if(SST.base[mid].key < key)
            low = mid+1;
        if(SST.base[mid].key > key)
            high = mid-1;
    }
    return 0;
}
