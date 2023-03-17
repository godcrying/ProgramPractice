#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

#define VEXNUM 6

int main()
{
    Graph G;
    int Dis[VEXNUM];
    int v0=0;

    if(!Init_graph(&G,VEXNUM)) exit(ERROR);
    Create_graph(&G);

    printf("邻接矩阵：\n");
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++)
            printf("%d ",G.arc[i][j]);
        printf("\n");
    }

    printf("顶点向量：\n");
    for(int i=0;i<G.vexnum;i++)
        printf("%s,",(*(G.vexlist+i)).info);

    if(Dijsktra(G,v0,Dis,10)){
        printf("\nv0到各顶点的距离为：");
        for(int i=0;i<G.vexnum;i++)
            printf("%d ",Dis[i]);
    }
    printf("\n");

    if(Prim(G,4))
        printf("OK!\n");
    return 0;
}



