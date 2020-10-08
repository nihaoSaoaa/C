#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 100    /* 最大顶点数设为100 */
#define INFINITY 65535        /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

/* 边的定义: 有向边<V1, V2>; 权重 */
typedef struct ENode *PtrToENode;
struct ENode {
  Vertex V1, V2;
  WeightType Weight;
};
typedef PtrToENode Edge;

 /* 图结点的定义: 顶点数；边数；邻接矩阵；顶点数据数组 */
typedef struct GNode *PtrToGNode;
struct GNode {
  int Nv;
  int Ne;
  WeightType G[MaxVertexNum][MaxVertexNum];
  DataType Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;

/* 初始化一个有VertexNum个顶点但没有边的图 */
MGraph CreateGraph( int VertexNum )
{
  int V,W;
  MGraph G = (MGraph)malloc(sizeof(struct GNode));
  G->Nv = VertexNum;
  G->Ne = 0;
  for (V=0; V<G->Nv; V++)
    for (W=0; W<G->Nv; W++)  
      G->G[V][W] = INFINITY;
  return G;
}

/* 插入边 <V1, V2> */
void InsertEdge(MGraph G, Edge E)
{
  G->G[E->V1][E->V2] = E->Weight;
  G->G[E->V2][E->V1] = E->Weight;// 无向图还要插入<V1, V2>
}




MGraph BuildGraph()
{
  MGraph G;
  Edge E;
  Vertex V;
  int Nv, i;
  scanf("%d", &Nv);
  G = CreateGraph(Nv);
  scanf("%d", &G->Ne);
  if(G->Ne) {
    E = (Edge)malloc(sizeof(struct ENode));
    for(i = 0; i < G->Ne; i++) {
      scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
      InsertEdge(G, E);
    }
  }
  for (V=0; V<G->Nv; V++) 
    scanf(" %c", &(G->Data[V]));
  return G;
}

void printfGraph(MGraph G)
{
  int i, j;
  WeightType X;
  printf("  ");
  for(i = 0; i < G->Nv; i++) {
    printf("%c ", G->Data[i]);
  }
  printf("\n");
  for(i = 0; i < G->Nv; i++) {
    printf("%c ", G->Data[i]);
    for(j = 0; j < G->Nv; j++) {
      if(G->G[i][j] == INFINITY) X = 0;
      else X = G->G[i][j];
      printf("%d ", X);
    }
    printf("\n");
  }
}

int main()
{
  MGraph G;
  G = BuildGraph();
  printfGraph(G);
  return 0;
}