#include <stdio.h>
#include <stdlib.h>
#include "sortsqlist.h"

int main()
{
    SqList L;
    printf("-------插入排序-------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    InsertSort(&L);
    printf("排序后：\n");
    PrintSqlist(L);

    printf("\n\n\n---------拆分插入排序--------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    BiInsertSort(&L);
    printf("排序后：\n");
    PrintSqlist(L);

    printf("\n\n\n---------表插入排序--------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    TabInsertSort(&L);
    printf("排序后：\n");
    Arrange(&L); //进行表重排
    PrintSqlist(L);

    printf("\n\n\n---------希尔排序--------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    ShellSort(&L);
    printf("排序后：\n");
    PrintSqlist(L);

    printf("\n\n\n---------冒泡排序--------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    BubbleSort(&L);
    printf("排序后：\n");
    PrintSqlist(L);

    printf("\n\n\n---------快速排序--------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    QuickSort(&L);
    printf("排序后：\n");
    PrintSqlist(L);

    printf("\n\n\n---------简单选择排序--------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    SimpleSelectSort(&L);
    printf("排序后：\n");
    PrintSqlist(L);

    printf("\n\n\n---------堆排序--------\n");
    printf("创建伪随机序列：");
    CreateSqList(&L);
    printf("\n");

    PrintSqlist(L);
    printf("\n");

    HeapSort(&L);
    printf("排序后：\n");
    PrintSqlist(L);
    return 0;
}
