#include <stdio.h>
#include <stdlib.h>

int main()
{
    void itoa(char *, int);
    char s[100];
    itoa(s,12345);
    printf("The int is:%s\n",s);
    return 0;
}

void itoa(char *s, int a){
    int static m=0,n=0;
    if(a/10 > 0){
        m++;
        n++;
        itoa(s,a/10);
    }
    *(s+n-m) = a%10 +'0';
    m--;
    if (m == 0)
        *(s+n+1) = '\0';
}
