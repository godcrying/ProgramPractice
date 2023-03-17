/*
* 第7章 7.7节 例子
*/
#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE*,FILE*);

int main(int argc,char *argv[])
{
    FILE *fp;
    char *prog = argv[0];
    if(argc == 1)
        filecopy(stdin,stdout);
    while(--argc)
    {
        if((fp=fopen(*++argv,"r")) == NULL)
        {
            fprintf(stderr,"%s:can't open file:%s\n",\
                    prog,*argv);
            exit(1);
        }else{
            filecopy(fp,stdout);
            fclose(fp);
        }
    }
    if(ferror(stdout)){
        fprintf(stderr,"%s:problem when output\n",prog);
        exit(2);
    }
    exit(0);
}

void filecopy(FILE *ifp,FILE *ofp)
{
    int c;
    while((c=getc(ifp)) != EOF)
          putc(c,ofp);
}
