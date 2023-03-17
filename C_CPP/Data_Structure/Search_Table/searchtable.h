#ifndef SEARCHTABLE_H_INCLUDED
#define SEARCHTABLE_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define true 1
#define false 0
#define MAXINFO 10
typedef int status;

typedef int Keytype;

typedef struct {
    Keytype key;
    char info[10]; //注意，此处要是使用指针，必须初始化。否则scanf无法输入。
}SElemType,item;

typedef struct {
    SElemType *base;
    int length;
}SStable;

status Create(SStable *,int);
status Destory(SStable *);
int SeqSearch(SStable,Keytype);
int BinarySearch(SStable,Keytype);
#endif // SEARCHTABLE_H_INCLUDED
