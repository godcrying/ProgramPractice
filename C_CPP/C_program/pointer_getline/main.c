#include <stdio.h>
#include <stdlib.h>

int main()
{
    void getline_p(char *);
    char s[100];
    getline_p(s);
    printf("The content of s is:%s\n",s);
    return 0;
}

void getline_p(char *s){
    /**
    *该程序有很大的缺点，可以对照书本上的原来的getline代码分析一下。
    */
    int c;
    while((c=getchar())!='\n')
        *s++=c;
    *s='\0';
}
