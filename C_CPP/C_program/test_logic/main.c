#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a='\0';
    char *b="abcd";
    if((a!='\0')&&(a=*b));
    printf("%c\n",a);
    return 0;
}
