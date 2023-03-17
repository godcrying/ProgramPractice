/*
* 第7章 7.4节 练习7-5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_STACK_SIZE 1000
#define STACK_INCREMENT 10
#define OK 1
#define ERROR 0

typedef double Elemtype;

typedef struct{
    Elemtype *base;
    Elemtype *top;
    int length;
}Stack;

int Init_stack(Stack *S)
{
    if(!(S->base = (Elemtype *)malloc(\
        INIT_STACK_SIZE*sizeof(Elemtype)))) return ERROR;
    S->top = S->base;
    S->length = INIT_STACK_SIZE;
    return OK;
}

void Destroy_stack(Stack *S)
{
    free(S->base);
}

int Push(Stack *S,Elemtype e)
{
    if(S->top - S->base > S->length -1)
    {
        if(!(S->base = (Elemtype *)realloc(S->base,\
        (S->length+STACK_INCREMENT)*sizeof(Elemtype))))
            return ERROR;
    }
    *S->top++ = e;
    S->length += STACK_INCREMENT;
    return OK;
}

Elemtype Pop(Stack *S)
{
    if(S->top == S->base){
        printf("The Stack is empty!!\n");
        return ERROR;
    }
    return *(--S->top);
}


int main(int argc,char *argv[])
{
    Stack S;
    if(!Init_stack(&S)){
        printf("Unknown Error！！\n");
        exit(-1);
    }
    double tmp_f;
    while(--argc)
    {
        if(sscanf(*(++argv),"%lf",&tmp_f)){
            Push(&S,tmp_f);
            continue;
        }

        switch(**argv)
        {
        case '+':
            Push(&S,(Pop(&S) + Pop(&S)));
            break;
        case '-':
            tmp_f = Pop(&S);
            Push(&S,(Pop(&S) - tmp_f));
            break;
        case '*':
            Push(&S,(Pop(&S) * Pop(&S)));
            break;
        case '/':
            tmp_f = Pop(&S);
            if(tmp_f == 0){
                printf("Couldn't divided by zero!!\n");
                exit(-1);
            }
            Push(&S,(Pop(&S)/tmp_f));
            break;
        default:
            printf("Unknown operator!!\n");
            break;
        }
    }
    printf("The answer is:%lf\n",Pop(&S));
    return 0;
}
