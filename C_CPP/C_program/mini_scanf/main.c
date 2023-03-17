/*
*第7章 7.4节 练习7-4
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void miniscanf(char* fmt,...);

int main()
{
    printf("Hello world!\n");
    int a;double b;char c;
    miniscanf("asdf%d/%f/%c",&a,&b,&c);
    printf("The value of a,b,c is:%d,%lf,%c\n",a,b,c);
    return 0;
}

void miniscanf(char *fmt,...)
{
    va_list ap;
    int *ival;
    double *dval;
    char *p,*cval;

    va_start(ap,fmt);
    for(p=fmt;*p;p++)
    {
        if(*p != '%')
        {
            getchar();
            continue;
        }

        switch(*++p){
        case 'd':
            ival = va_arg(ap,int*);
            scanf("%d",ival);
            break;
        case 'f':
            dval = va_arg(ap,double*);
            scanf("%lf",dval);
            break;
        case 'c':
            cval = va_arg(ap,char*);
            scanf("%c",cval);
            break;
        default:
            printf("unknown format:%c",*p);
            exit(-1);
        }
    }
    va_end(ap);
}
