#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 100    /* 最大顶点数设为100 */
#define INFINITY 65535        /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

// 邻接矩阵 ADT
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

// 邻接表 ADT
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

void Insert( LGraph Graph, Edge E );

/* Prim 算法 */
#define ERROR -1
Vertex FindMinDist(MGraph Graph, WeightType dist[])
{
  WeightType MinDist = INFINITY;
  Vertex MinV, V;
  for(V = 0; V < Graph->Nv; V++) {
    if(dist[V] != 0 && dist[V] < MinDist) {
      MinDist = dist[V];
      MinV = V;
    }
  }
  if(MinDist < INFINITY) return MinV;
  else return ERROR;
}
// 将最小生成树保存为邻接表，返回最小权重
int Prim(MGraph Graph, LGraph MST)
{
  WeightType dist[MaxVertexNum], TotalWeight = 0;
  Vertex parent[MaxVertexNum], V, W;
  int VCount = 0;
  Edge E = (Edge)malloc(sizeof(struct ENode));
  // 初始化, 以 0 为初始点
  for(V = 0; V < Graph->Nv; V++) {
    dist[V] = Graph->G[0][V];
    parent[V] = 0;
  }
  // 收录 0
  dist[0] = 0;
  VCount++;
  parent[0] = -1;
  // 收录其他点并更新距离
  while(1) {
    V = FindMinDist(Graph, dist);
    if(!V) return ERROR;
    // 收录进MST
    E->V1 = parent[V];
    E->V2 = V;
    E->Weight = dist[V];
    TotalWeight += dist[V];
    Insert(MST, E);
    dist[V] = 0;
    VCount++;
    // 更新其邻接点的距离
    for(W = 0; W < Graph->Nv; W++) {
      if(dist[W] != 0 && dist[W] < INFINITY) {
        if(Graph->G[V][W] < dist[W]) {
          dist[W] = Graph->G[V][W];
          parent[W] = V;
        }
      }
    }
  }
  if(VCount < Graph->Nv) TotalWeight = ERROR;
  return TotalWeight;
}

/* 邻接表存储 - Kruskal最小生成树算法 */
/*-------------------- 顶点并查集定义 --------------------*/
typedef Vertex ElementType; /* 默认元素可以用非负整数表示 */
typedef Vertex SetName;     /* 默认用根结点的下标作为集合名称 */
typedef ElementType SetType[MaxVertexNum]; /* 假设集合元素下标从0开始 */

// 初始化并查集
void InitializeVSet(SetType S, int N)
{
  ElementType X;
  for(X=0; X<N; X++ ) {
    S[X] = -1;
  }
}

/* 这里默认Root1和Root2是不同集合的根结点 */
void Union( SetType S, SetName Root1, SetName Root2 )
{ 
  /* 保证小集合并入大集合 */
  if ( S[Root2] < S[Root1] ) { /* 如果集合2比较大 */
    S[Root2] += S[Root1];     /* 集合1并入集合2  */
    S[Root1] = Root2;
  }
  else {                         /* 如果集合1比较大 */
    S[Root1] += S[Root2];     /* 集合2并入集合1  */
    S[Root2] = Root1;
  }
}
/* 默认集合元素全部初始化为-1 */
SetName Find( SetType S, ElementType X )
{
  if ( S[X] < 0 ) /* 找到集合的根 */
    return X;
  else
    return S[X] = Find( S, S[X] ); /* 路径压缩 */
}

/* 检查连接V1和V2的边是否在现有的最小生成树子集中构成回路 */
bool  CheckCycle(SetType S, Vertex V1, Vertex V2)
{
  Vertex Root1, Root2;

  Root1 = Find( VSet, V1 ); /* 得到V1所属的连通集名称 */
  Root2 = Find( VSet, V2 ); /* 得到V2所属的连通集名称 */

  if( Root1==Root2 ) /* 若V1和V2已经连通，则该边不能要 */
    return false;
  else { /* 否则该边可以被收集，同时将V1和V2并入同一连通集 */
    Union( VSet, Root1, Root2 );
    return true;
  }
}

/* 将N个元素的边数组中以ESet[p]为根的子堆调整为关于Weight的最小堆 */
void PercDown( Edge ESet, int p, int N )
{
  int Parent, Child;
  struct ENode X;

  X = ESet[p]; /* 取出根结点存放的值 */
  for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
    Child = Parent * 2 + 1;
    if( (Child!=N-1) && (ESet[Child].Weight>ESet[Child+1].Weight) )
      Child++;  /* Child指向左右子结点的较小者 */
    if( X.Weight <= ESet[Child].Weight ) break; /* 找到了合适位置 */
    else  /* 下滤X */
      ESet[Parent] = ESet[Child];
  }
  ESet[Parent] = X;
}

/* 将图的边存入数组ESet，并且初始化为最小堆 */
void InitializeESet( LGraph Graph, Edge ESet )
{ 
  Vertex V;
  PtrToAdjVNode W;
  int ECount;

  /* 将图的边存入数组ESet */
  ECount = 0;
  for ( V=0; V<Graph->Nv; V++ )
    for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
      if ( V < W->AdjV ) { /* 避免重复录入无向图的边，只收V1<V2的边 */
        ESet[ECount].V1 = V;
        ESet[ECount].V2 = W->AdjV;
        ESet[ECount++].Weight = W->Weight;
      }
  /* 初始化为最小堆 */
  for ( ECount=Graph->Ne/2; ECount>=0; ECount-- )
    PercDown( ESet, ECount, Graph->Ne );
}

/* 给定当前堆的大小CurrentSize，将当前最小边位置弹出并调整堆 */
int GetEdge( Edge ESet, int CurrentSize )
{ 
  /* 将最小边与当前堆的最后一个位置的边交换 */
  Swap( &ESet[0], &ESet[CurrentSize-1]);
  /* 将剩下的边继续调整成最小堆 */
  PercDown( ESet, 0, CurrentSize-1 );

  return CurrentSize-1; /* 返回最小边所在位置 */
}

/* 将最小生成树保存为邻接表存储的图MST，返回最小权重和 */
int Kruskal( LGraph Graph, LGraph MST )
{ 
  WeightType TotalWeight;
  int ECount, NextEdge;
  SetType VSet; /* 顶点数组 */
  Edge ESet;    /* 边数组 */

  InitializeVSet( VSet, Graph->Nv ); /* 初始化顶点并查集 */
  ESet = (Edge)malloc( sizeof(struct ENode)*Graph->Ne );
  InitializeESet( Graph, ESet ); /* 初始化边的最小堆 */
  /* 创建包含所有顶点但没有边的图。注意用邻接表版本 */
  MST = CreateGraph(Graph->Nv);
  TotalWeight = 0; /* 初始化权重和     */
  ECount = 0;      /* 初始化收录的边数 */

  NextEdge = Graph->Ne; /* 原始边集的规模 */
  while ( ECount < Graph->Nv-1 ) {  /* 当收集的边不足以构成树时 */
    NextEdge = GetEdge( ESet, NextEdge ); /* 从边集中得到最小边的位置 */
    if (NextEdge < 0) /* 边集已空 */
      break;
    /* 如果该边的加入不构成回路，即两端结点不属于同一连通集 */
    if ( CheckCycle( VSet, ESet[NextEdge].V1, ESet[NextEdge].V2 )==true ) {
      /* 将该边插入MST */
      InsertEdge( MST, ESet+NextEdge );
      TotalWeight += ESet[NextEdge].Weight; /* 累计权重 */
      ECount++; /* 生成树中边数加1 */
    }
  }
  if ( ECount < Graph->Nv-1 )
    TotalWeight = -1; /* 设置错误标记，表示生成树不存在 */

  return TotalWeight;
}