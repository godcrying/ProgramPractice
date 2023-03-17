#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

int getline_m(char *,int);
int main(int argc, char *argv[])
{
    char line[MAXLINE];

    int found=0;

    if(argc !=2 )
        printf("Usage: finde pattern\n");
    else
        while(getline_m(line,MAXLINE) > 0){
            if(strstr(line,argv[1]))
                printf("%s",line);
            found++;
        }
    return found;
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
    *(s+count) = '\0';
    return count;
}
