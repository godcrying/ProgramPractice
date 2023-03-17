#include <stdio.h>
#include <stdlib.h>
#include "mystruct.h"

void visit(BiTNode BN)
{
    printf("->%d",BN.elem);
}

int compare(BiTNode btn1,BiTNode btn2)
{
    if(btn1.key < btn2.key) return -1;
    if(btn1.key == btn2.key) return 0;
    return 1;
}

int main()
{
    BiTree T;
    BiTree Thr,bt;

    BiTNode BTN; //BTN为需要进行比较的节点
    BTN.key = BTN.elem = 5;
    BTN.lchild = BTN.rchild = NULL;

    if(CreateBiTree(&T)){
        printf("先序遍历：\n");
        PreOrderTraverse(T,visit);
        printf("\n中序遍历：\n");
        InOrderTraverse(T,visit);
        printf("\n非递归中序遍历：\n");
        InOrderTraverse_no_recursive(T,visit);

        printf("\n");
        if(SearchBSTree(T,BTN,&bt,compare))
            printf("找到元素！！\n");
        else if(InsertBSTree(T,&BTN,compare))
            printf("未找到，成功插入元素！！\n");
        //线索化遍历放在最后，因为线索化会改写叶子节点的数据
        printf("\n非递归线索化中序遍历：\n");
        InOrderThreading(&Thr,T);
        InOrderTraverse_Thr(Thr,visit);
        printf("\n");
    }
    return 0;
}
