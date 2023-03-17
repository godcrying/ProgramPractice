
/*
*第7章 7.1节 练习7-1
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char* argv[])
{
    char *tobasename(char*);
    char *name = tobasename(argv[0]);

    int flag=0,c;
    if(strcmp(name,"upper") == 0) flag=1;
    if(strcmp(name,"lower") == 0) flag=-1;

    while((c=getchar()) != EOF)
    {
        switch(flag){
        case 1:
            putchar(toupper(c));break;
        case -1:
            putchar(tolower(c));break;
        default:
            printf("unknown program name:%s\n",name);
            exit(-1);
        }
    }
    return 0;
}

char* tobasename(char* name)
{
    char *basename = strrchr(name,'/');
    return basename ? basename+1 : name;
}
