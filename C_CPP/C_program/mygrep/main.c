/*
* 第7章 7.7节 练习7-7
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000


int main(int argc,char *argv[])
{
    FILE *fp;
    char line[MAXLINE];

    if(argc < 2)
    {
        printf("Usage:mygrep mode [file1 [file2..]]\n");
        exit(1);
    }

    char *prog = argv[0];
    char *mode = argv[1];

    if(argc == 2)
    {
        while(fgets(line,MAXLINE,stdin) != NULL)
        {
            if(strstr(line,mode) != NULL)
                printf("%s",line);
        }
    }
    if(argc > 2)
    {
        --argc;
        ++argv;
        while(--argc)
        {
            if((fp=fopen(*++argv,"r")) == NULL)
            {
                fprintf(stderr,"%s:can't open file %s",\
                        prog,*argv);
            }
            else
            {
                printf("\n---------------\n");
                printf("%s",*argv);
                printf("\n---------------\n");
                while(fgets(line,MAXLINE,fp) != NULL)
                {
                    if(strstr(line,mode) != NULL)
                        printf("%s",line);
                }
            }

            if(fp != NULL)
                fclose(fp);
        }
    }
    return 0;
}
