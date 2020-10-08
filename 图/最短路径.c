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

/* 邻接矩阵存储 - 有权图的单源最短路算法 */
#define ERROR -1
Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    int MinDist = INFINITY;
 
    for (V=0; V<Graph->Nv; V++) {
        if ( collected[V]==false && dist[V]<MinDist) {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}
 
bool Dijkstra( MGraph Graph, int dist[], int path[], Vertex S )
{
  int collected[MaxVertexNum];
  Vertex V, W;

  /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
  for ( V=0; V<Graph->Nv; V++ ) {
    dist[V] = Graph->G[S][V];
    if ( dist[V]<INFINITY )
      path[V] = S;
    else
      path[V] = -1;
    collected[V] = false;
  }
  /* 先将起点收入集合 */
  dist[S] = 0;
  collected[S] = true;
 
  while (1) {
    /* V = 未被收录顶点中dist最小者 */
    V = FindMinDist( Graph, dist, collected );
    if ( V==ERROR ) /* 若这样的V不存在 */
      break;      /* 算法结束 */
    collected[V] = true;  /* 收录V */
    for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
      /* 若W是V的邻接点并且未被收录 */
      if ( collected[W]==false && Graph->G[V][W]<INFINITY ) {
        if ( Graph->G[V][W]<0 ) /* 若有负边 */
          return false; /* 不能正确解决，返回错误标记 */
        /* 若收录V使得dist[W]变小 */
        if ( dist[V]+Graph->G[V][W] < dist[W] ) {
          dist[W] = dist[V]+Graph->G[V][W]; /* 更新dist[W] */
          path[W] = V; /* 更新S到W的路径 */
        }
      }
  } /* while结束*/
    return true; /* 算法执行完毕，返回正确标记 */
}

/* 邻接矩阵存储 - 多源最短路算法 */
 
bool Floyd( MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum] )
{
    Vertex i, j, k;
 
    /* 初始化 */
    for ( i=0; i<Graph->Nv; i++ )
      for( j=0; j<Graph->Nv; j++ ) {
        D[i][j] = Graph->G[i][j];
        path[i][j] = -1;
      }

    for( k=0; k<Graph->Nv; k++ )
      for( i=0; i<Graph->Nv; i++ )
        for( j=0; j<Graph->Nv; j++ )
            if( D[i][k] + D[k][j] < D[i][j] ) {
              D[i][j] = D[i][k] + D[k][j];
              if ( i==j && D[i][j]<0 ) /* 若发现负值圈 */
                return false; /* 不能正确解决，返回错误标记 */
              path[i][j] = k;
            }
    return true; /* 算法执行完毕，返回正确标记 */
}




