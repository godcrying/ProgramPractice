#include <stdio.h>
#include <stdlib.h>

int main()
{
    float f=0.00375;
    unsigned char a,b,c,d;
    a=*((unsigned char*)(&f)+3);
    b=*((unsigned char*)(&f)+2);
    c=*((unsigned char*)(&f)+1);
    d=*((unsigned char*)(&f));
   // j=*((unsigned char*)((unsigned long int)&f-));
    printf("float 字节数为：%lu\n",sizeof(float));
    printf("a:%x b:%x c:%x d:%x\n",a,b,c,d);
    //printf("阶码：%x",j);
    //linux中浮点数就是以IEEE 745标准表示的。
    return 0;
}
