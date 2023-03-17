#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graph.h"

#define MAXNODE 100

//初始化图
status Init_graph(Graph *G,int vexnum)
{
    if(vexnum <= MAXNODE)
    {
        if((G->arc = (int**)malloc(vexnum*sizeof(int*))) == NULL)
            exit(OVERFLOW);
        for(int i=0; i<vexnum; i++)
        {
            *(G->arc+i) = (int*)malloc(vexnum*sizeof(int));
            if(*(G->arc+i) == NULL)
                exit(OVERFLOW);
        }

        if((G->path = (int**)malloc(vexnum*sizeof(int*))) == NULL)
            exit(OVERFLOW);
        for(int i=0; i<vexnum; i++)
        {
            *(G->path+i) = (int*)malloc(vexnum*sizeof(int));
            if(*(G->path+i) == NULL)
                exit(OVERFLOW);
        }

        if((G->vexlist = (Vertexlist)malloc(vexnum*\
                                            sizeof(Vertex))) == NULL)
            exit(OVERFLOW);
    }//if
    G->vexnum = vexnum;
    return OK;
}

//销毁图
void Destory_graph(Graph *G)
{
    for(int i=0; i<G->vexnum; i++)
        free(*(G->arc+i));
    free(G->arc);
}

//创建图
status Create_graph(Graph *G)
{
    int vexnum = G->vexnum;
    Vertex *vexlist = G->vexlist;

    for(int i=0; i<vexnum; i++)
    {
        printf("请输入第%d个顶点信息：\n",i);
        scanf("%s",(vexlist+i)->info);

        printf("请输入该顶点的邻接向量：\n");
        for(int j=0; j<vexnum; j++)
        {
            scanf("%d",(G->arc)[i]+j);
        }
    }

    return OK;
}



/*
********************
*Deep_Firest Search（此方法还没有完成，编译不通过）
********************
*/

int *visited;
void DFS(Graph G,Vertex u);


status DFS_Traver(Graph G,Vertex u,status (*visit)(Vertex))
{
    int vexnum = G.vexnum;
    if((visited=(int*)malloc(vexnum*sizeof(int))) == NULL)
        exit(OVERFLOW);

    for(int i=0;i<vexnum;i++)
        visited[i]=false;

    int index = Getindex(u);
    if((* visit)(u)) visited[index] = true;

    DFS(G,u);

    return OK;
}
/*
* 基本操作是：1.访问顶点 2.获取下一个邻接顶点 3.回到1
* 第一步应该是访问顶点，而不是获取。
*
* 所以，这种写法就不是很简洁了。颠倒了基本操作的顺序。比较好的写法详见课本。
*/
void DFS(Graph G,Vertex u)
{
    for(Vertex v=FirstNeighbour(G,u);i<next_vex_num(G,u);v=NextNeighbour(G,u))
    {
        int index = Getindex(v);
        if(!visited[index] && (* visit)(v))
        {
            visited[index] = true;
            DFS(G,v);
        }
    }
}

/*
****************
*Dijsktra start
****************
*/
//迪杰克斯拉算法计算v0到各顶点最短距离
status Dijsktra(Graph G,int v0,int *Dis,int INFINI)
{
    int vexnum = G.vexnum;
    int **arc = G.arc;
    int **Path = G.path;
    /*
    *原来这里用的是传入的Path[][]二维数组，但是因为二维数组作为形参必须确定长度，
    *故将path放入图结构体Graph中，使用动态二维数组来实现相同功能。
    */

    int *Vex_In_S = (int*)malloc(vexnum*sizeof(int));
    if(!Vex_In_S)
        exit(OVERFLOW);

    for(int i=0; i<vexnum; i++)
    {
        Vex_In_S[i] = false; //初始化S集合
        for(int j=0; j<vexnum; j++)
        {
            Path[i][j] = false; //初始化路径数组

            if(i==v0)
            {
                Dis[j] = arc[i][j]; //初始化距离数组
                if(Dis[j]<INFINI)
                {
                    Path[j][v0]=true;
                    Path[j][j]=true;
                }
            }
        }
    }
    Vex_In_S[v0]=true; //将v0加入S中

    for(int i=1; i<vexnum; i++)
    {
        int min=INFINI;
        int temp_min_vex;
        for(int j=0; j<vexnum; j++)
        {
            if(!Vex_In_S[j]&&Dis[j]<min)
            {
                //从所有的V-S集合中的顶点中找出路径最短的，设为临时基点
                //并将其加入S集合中

                min=Dis[j];
                temp_min_vex = j;
            }
        }
        Vex_In_S[temp_min_vex] = true;

        //计算下一步的所有路径
        for(int j=0; j<vexnum; j++)
        {
            if(!Vex_In_S[j]&&arc[temp_min_vex][j]+min<Dis[j])
            {
                //更新V-S中的顶点路径
                Dis[j] = arc[temp_min_vex][j]+min;

                //更新顶点路径，到达j顶点的路径前半部分与到达临时基点相同
                for(int v=0; v<vexnum; v++)
                    Path[j][v] = Path[temp_min_vex][v];

                //每个顶点自身必在路径上，但是必须是v0可以到达才能为true
                //所以，该句不能放到if外面
                Path[j][j]=true;
            }//if
        }//for
    }
    return OK;
}

/*
*Dijsktra end
*/



/*
*******************
*Prim start
*******************
*/

typedef struct closedge
{
    int u;
    int lowcost;
} closedge,*closedges;



int minimal(closedge *closedges,int len)
{
    int min=0,index=0;
    for(int i=0;i<len;i++)
        if(closedges[i].lowcost != 0){
            min = closedges[i].lowcost;
            index = i;
            break;
        }

    for(int i=0; i<len; i++)
        if(closedges[i].lowcost < min && closedges[i].lowcost >0)
        {
            min = closedges[i].lowcost;
            index = i;
        }
    return index;
}

//Prim算法求解最小生成树
status Prim(Graph G,int u0)
{
    int vexnum = G.vexnum;
    closedge *closedges;
    if((closedges = (closedge *)malloc(vexnum*sizeof(closedge))) == NULL)
        exit(OVERFLOW);

    for(int i=0; i<vexnum; i++){
        closedges[i].u = u0;
        closedges[i].lowcost = G.arc[u0][i];
    }
    closedges[u0].lowcost=0;

    for(int i=1; i<vexnum; i++)
    {
        int v=minimal(closedges,vexnum);
        printf("顶点1：v%d，顶点2：v%d，距离：%d\n",closedges[v].u+1,v+1,closedges[v].lowcost);

        closedges[v].lowcost=0;
        for(int j=0; j<vexnum; j++)
        {
            if(G.arc[v][j] < closedges[j].lowcost)
            {
                closedges[j].u = v;
                closedges[j].lowcost = G.arc[v][j];
            }
        }
    }
    return OK;
}
/*
*prim end
*/

