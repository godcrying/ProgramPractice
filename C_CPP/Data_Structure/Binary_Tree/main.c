#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"


void visit(BiTNode BN)
{
    printf("%d->",BN.elem);
}

int main()
{
    BiTree T;
    if(CreateBiTree(&T)){
        printf("先序遍历：\n");
        PreOrderTraverse(T,visit);
        printf("\n中序遍历：\n");
        InOrderTraverse(T,visit);
        printf("\n非递归中序遍历：\n");
        InOrderTraverse_no_recursive(T,visit);
    }
    return 0;
}
