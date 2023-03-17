/*
* 第7章 7.7节 练习7-6
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int filecmp(FILE*,FILE*);

int main(int argc,char *argv[])
{
    if(argc != 3){
        printf("Usage:cmd path1 path2\n");
        exit(1);
    }

    char *s1 = argv[1];
    char *s2 = argv[2];
    char *prog = argv[0];

    FILE *fp1,*fp2;
    fp1=fopen(s1,"r");
    fp2=fopen(s2,"r");

    if(fp1 == NULL || fp2 == NULL){
        fprintf(stderr,"%s:can't open file %s\n",\
                prog,(fp1==NULL ? s1:s2));
        exit(2);
    }else{
        if(filecmp(fp1,fp2) == 0)
            printf("These two files are the same.\n");
        else
            printf("These two files are not same.\n");
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

int filecmp(FILE *fp1,FILE *fp2)
{
    char s1[MAXLINE],s2[MAXLINE];
    //字符指针是不能直接当字符数组使用的。

    while(1)
    {
        char *r1 = fgets(s1,MAXLINE,fp1);
        char *r2 = fgets(s2,MAXLINE,fp2);
        if(strcmp(s1,s2) != 0)
        {
            printf("%s%s",s1,s2);
            return 1;
        }
        if(r1 == NULL)
            break;
    }

    return 0;
}
