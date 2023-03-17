#ifndef SORTSQLIST_H_INCLUDED
#define SORTSQLIST_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXINFOLINE 10
#define true 1
#define false 0

#define MAXSIZE 20
typedef int status;
typedef int Keytype;

typedef struct {
    Keytype key;
    int next;
    char *info;
}RecType;

typedef struct {
    RecType rec[MAXSIZE+1];
    int length;
}SqList;

//构造列表
status CreateSqList(SqList*);

//输出列表
status PrintSqlist(SqList L);

//直接插入排序
status InsertSort(SqList*);
//折半插入排序
status BiInsertSort(SqList*);
//表插入排序
status TabInsertSort(SqList*);
//表插入重排
status Arrange(SqList*);
//希尔排序
status ShellSort(SqList*);

//冒泡排序
status BubbleSort(SqList*);
//快速排序
status QuickSort(SqList*);

//简单选择排序
status SimpleSelectSort(SqList*);
//堆排序
status HeapSort(SqList*);

#endif // SORTSQLIST_H_INCLUDED
