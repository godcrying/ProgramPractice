
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXINFOLINE 10
#define true 1
#define false 0


typedef int status;

typedef struct Vertex
{
    int id; //顶点唯一编号
    char info[MAXINFOLINE]; //顶点信息

}Vertex,*Vertexlist;

typedef struct Graph
{
    int **arc; //邻接矩阵
    int **path; //最小路径矩阵
    Vertexlist vexlist;//顶点向量
    int vexnum; //顶点个数
}Graph;

status Init_graph(Graph*,int);

void Destory_graph(Graph*);

status Create_graph(Graph*);

status DFS_Traver(Graph,Vertex,status (*)(Vertex))

status Prim(Graph G,int u); //此处先用序号代替顶点编号

status Dijsktra(Graph G,int v0,int *Dis,int INFINI);

int Getindex(Vertex);
