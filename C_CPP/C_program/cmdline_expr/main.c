/**
*练习5-10
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 1000

/**
*注意，在命令行中输入参数时，*会自动展开为当前目录的文件列表。所以需要使用转义字符 \*。
*/
void push(double);
double pop(void);
int isnumber(char *);

int main(int argc, char *argv[])
{
    double temp;
    char c;
    for(++argv;--argc > 0;argv++){
        if(isnumber(*argv)){
            push(atof(*argv));
            continue;
        }
        switch(c = (*argv)[0]){
            case '+':
                push(pop()+pop());
                break;
            case '-':
                temp = pop();
                push(pop()-temp);
                break;
            case '*':
                push(pop()*pop());
                break;
            case '/':
                if ((temp = pop()) != 0)
                    push(pop() - temp);
                else
                    printf("Error: divide by zero!!\n");
                break;
            default:
                printf("%c is Invalid operator!!\n",c);
                break;
        }
    }
    printf("%g\n",pop());
    return 0;
}

int isnumber(char *s){
    /*(*s == '+' || *s == '-' && isdigit(*(s+1))) ||*/
    return ((*s == '+' || *s == '-') && isdigit(*(s+1))) || isdigit(*s);
}

double buff[MAXLINE];
int buffptr=0;

void push(double f){
    if(buffptr < MAXLINE)
        buff[buffptr++] = f;
    else
        printf("Error: stack is full!!\n");
}

double pop(void){
    if(buffptr > 0)
        return buff[--buffptr];
    else
        printf("Error: stack is empty!!\n");
    return -1;
}
