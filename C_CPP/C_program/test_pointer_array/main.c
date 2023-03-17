#include <stdio.h>
#include <stdlib.h>

void foo(int **);
int main()
{
    int a[2][5]={{1,2,3,4,5},{6,7,8,9,10}};
    int b[2][3]={{1,2,3},{6,7,8}};
    int (*p)[];
    p=a;
    p=b;
    printf("%d\n",**p);
    printf("%d\n",**a);
    foo(a);
    return 0;
}

void foo(int **x)
{
    printf("%d",x[0][0]);
}
