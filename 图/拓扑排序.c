#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 图的 ADT
#define MaxVertexNum 100    /* 最大顶点数设为100 */
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

typedef struct ENode *PtrToENode;
struct ENode {
  Vertex v1, v2;
  WeightType Weight;
};
typedef PtrToENode Edge;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
  Vertex AdjV;
  WeightType Weight;
  PtrToAdjVNode Next;
};
typedef struct VNode {
  PtrToAdjVNode FirstEdge;
  DataType Data;
}AdjList[MaxVertexNum]; 
typedef struct GNode *PtrToGNode;
struct GNode {
  int Nv;
  int Ne;
  AdjList G;
};
typedef PtrToGNode LGraph;

// 队列的 ADT
typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node {
  ElementType Data;
  PtrToNode Next;
};
struct QNode {
  PtrToNode Front,Rear;
};
typedef struct QNode* Queue;
Queue createQueue();
bool IsEmpty(Queue Q);
bool AddQ(Queue Q, ElementType x);
ElementType DeleteQ(Queue Q);
// 拓扑排序
/*
1. 初始化结点的入度数组 Indgree[]
2. 将入度为 0 的结点加入队列
3. 开始拓扑排序（队列不为空）
  3.1 取出队列的一个结点加入排序数组 TopOrder[]
  3.2 邻接结点的入度 -1并判断他们的入度是否 == 0
  3.3 入度 == 0 则加入队列
4. 判断所有结点是否都排序
*/
bool TopSort(LGraph Graph, Vertex TopOrder[])
{
  int Indgree[MaxVertexNum], cnt = 0;
  Vertex V;
  PtrToAdjVNode W;
  Queue Q = createQueue();
  for(V = 0; V < Graph->Nv; V++) {
    Indgree[V] = 0;
  }
  for(V = 0; V < Graph->Nv; V++) {
    W = Graph->G[V].FirstEdge;
    while(W) {
      Indgree[W->AdjV]++;
      W = W->Next;
    }
  }
  for(V = 0; V < Graph->Nv; V++) {
    if(Indgree[V] == 0) {
      AddQ(Q, V);
    }
  }
  while(!IsEmpty(Q)) {
    V = DeleteQ(Q);
    TopOrder[cnt++] = V;
    for(W = Graph->G[V].FirstEdge; W ; W = W->Next) {
      if(--Indgree[W->AdjV] == 0) {
        AddQ(Q, W->AdjV);
      }
    }
  }
  if(cnt == Graph->Nv) return true;
  else return false;
}