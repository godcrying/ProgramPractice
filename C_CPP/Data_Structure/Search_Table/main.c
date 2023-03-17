#include <stdio.h>
#include <stdlib.h>
#include "searchtable.h"

int main()
{
    SStable SST;
    if(!Create(&SST,11))
        exit(ERROR);
//    printf("Selemlist:\n");
//    for(int i=1;i<SST.length+1;i++)
//        printf("%d ",SST.base[i].key);

    //使用顺序查询
    int index;
    if(!(index=SeqSearch(SST,21)))
        printf("can't find this element!!\n");
    else
        printf("The elem index is:%d\n",index);

    //使用二分法查询
    if(!(index = BinarySearch(SST,64)))
        printf("can't find this elem!!\n");
    else
        printf("The elem index is:%d\n",index);
    return 0;
}
