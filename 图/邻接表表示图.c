/* 图的邻接表表示法 */
#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100    /* 最大顶点数设为100 */
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode {
  Vertex v1, v2;
  WeightType Weight;
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
  Vertex AdjV;
  WeightType Weight;
  PtrToAdjVNode Next;
};

/* 顶点表头结点的定义 */
typedef struct VNode {
  PtrToAdjVNode FirstEdge;
  DataType Data;
}AdjList[MaxVertexNum]; 

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode {
  int Nv;
  int Ne;
  AdjList G;
};
typedef PtrToGNode LGraph;

/* 初始化一个有VertexNum个顶点但没有边的图 */
LGraph CreateGraph( int VertexNum )
{
  Vertex V;
  LGraph Graph;
  Graph = (LGraph)malloc(sizeof(struct GNode));
  Graph->Nv = VertexNum;
  Graph->Ne = 0;
  for(V = 0; V < VertexNum; V++) {
    Graph->G[V].FirstEdge = NULL;
  }
  return Graph;
}

void Insert( LGraph Graph, Edge E )
{
  PtrToAdjVNode NewNode;
  NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
  NewNode->AdjV = E->v2;
  NewNode->Weight = E->Weight;
  NewNode->Next = Graph->G[E->v1].FirstEdge;
  Graph->G[E->v1].FirstEdge = NewNode;
  // 若是无向图还要插入边 <v2, v1>
  NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
  NewNode->AdjV = E->v1;
  NewNode->Weight = E->Weight;
  NewNode->Next = Graph->G[E->v2].FirstEdge;
  Graph->G[E->v2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
  Edge E;
  LGraph Graph;
  Vertex V;
  int Nv, i;
  scanf("%d", &Nv);
  Graph = CreateGraph(Nv);
  scanf("%d", &Graph->Ne);
  if(Graph->Ne) {
    E = (Edge)malloc(sizeof(struct ENode));
    for(i = 0; i < Graph->Ne; i++) {
      scanf("%d %d %d", &E->v1, &E->v2, &E->Weight);
      Insert(Graph, E);
    }
  }
  for(V = 0;V < Graph->Nv; V++) {
    scanf(" %c", &(Graph->G[V].Data));
  }
  return Graph;
}

void printfGraph(LGraph Graph)
{
  int i;
  DataType Data;
  PtrToAdjVNode P;
  WeightType Weight;
  for(i = 0; i < Graph->Nv; i++) {
    Data = Graph->G[i].Data;
    P = Graph->G[i].FirstEdge;
    printf("%c -> ", Data);
    while(P) {
      Data = Graph->G[P->AdjV].Data;
      Weight = P->Weight;
      if(P->Next)
        printf("%c:%d -> ", Data, Weight);
      else
        printf("%c:%d\n", Data, Weight);
      P = P->Next;
    }
  }
}

int main()
{
  LGraph Graph;
  Graph = BuildGraph();
  printfGraph(Graph);
  return 0;
}