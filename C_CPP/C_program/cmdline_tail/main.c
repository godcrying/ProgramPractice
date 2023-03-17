#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXALLOCBUFF 10000
#define MAXLINE 1000

char *alloc(int);
int getline_m(char *,int);

int main(int argc, char *argv[])
{
    int n=10,length,nlines=0;
    char *lineptr[MAXLINE];
    char line[MAXLINE];
    char *p;
    // printf("start!!\n");

    if(argc > 3)
    {
        printf("Usage:cmdline_tail [-n NUM]\n");
        return 1;
    }
    // printf("after argc > 3\n");

    if(argc == 3 && (*(argv+1))[0] == '-' && (*(argv+1))[1] == 'n' )
    {
        argc--;
        if (argv[2])
        {
            n = atof(*(argv+2));
            argc--;
        }
        else
        {
            printf("Usage:cmdline_tail [-n NUM]\n");
            return 1;
        }
    }
   // printf("after argc <= 3\n");
    if(argc != 1)
    {
        printf("Usage:cmdline_tail [-n NUM]\n");
        return 1;
    }
   // printf("after argc != 1\n");
    while((length = getline_m(line,MAXLINE)) > 0)
    {
        if(nlines >= MAXLINE || (p = alloc(length)) == NULL)
        {
            /**
            *此处alloc分配的内存为p到p+length-1，一共length个单元。
            *而line的实际长度（包括'\0'）为length+1。
            *所以，如果要真正以字符串方式存储每一行，需要将'\n'换为'\0'
            */
            printf("No enough mem!!\n");
            return 1;
        }
        line[length-1]='\0'; /**将'\n'换为'\0'*/
        strcpy(p,line);
        lineptr[nlines++] = p;
    }

    nlines -= n;
    for(int i=0;i<n;i++,nlines++)
        printf("%s\n",lineptr[nlines]);

    return 0;
}

static char allocbuff[MAXALLOCBUFF];
static char *allocptr=allocbuff;
char *alloc(int len){
    if((allocptr+=len) > allocbuff + MAXALLOCBUFF)
        return 0;
    return allocptr - len;
}
void afree(char *p){
    if(p >=allocbuff && p<= allocbuff + MAXALLOCBUFF)
        allocptr = p;
}

int getline_m(char *s,int maxline){
    /**
    *根据书本上的相关代码改的，基本上就只是将数组表示换成了指针表示。其他没变。
    */
    int c,count;
    for(count =0; count < maxline - 1 && (c = getchar()) != '\n' && c != EOF ; count++){
        *(s+count) = c;
    }
    if(c == '\n'){
        *(s+count) = c;
        count++;
    }
    /**
    *count不包括'\0'，*(s+count-1) = '\n'。从0到count-1一共有count个数。
    */
    *(s+count) = '\0';
    return count;
}
