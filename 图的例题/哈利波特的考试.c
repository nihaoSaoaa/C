#include <stdio.h>
#include <stdbool.h>

#define MaxVertexNum 100  
#define INFINITY 65535       
typedef int Vertex;         
typedef int WeightType; 

Vertex V, M;
WeightType Graph[MaxVertexNum][MaxVertexNum];
WeightType D[MaxVertexNum][MaxVertexNum];

bool Floyd()
{
  Vertex i, j, k;
  for(i = 0; i < V; i++) {
    for(j = 0; j < V; j++) {
      D[i][j] = Graph[i][j];
      if(i == j) {
        D[i][j] = 0;
      }
    }
  }
  for(k = 0; k < V; k++) {
    for(i = 0; i < V; i++) {
      for(j = 0; j < V; j++) {
        if(D[i][j] > D[i][k] + D[k][j]) {
          D[i][j] = D[i][k] + D[k][j];
          if(i == j && D[i][j] < 0) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

WeightType FindMaxDist(Vertex i)
{
  Vertex j;
  WeightType MaxDist = 0;
  for(j = 0; j < V; j++) {
    if( i != j && D[i][j] > MaxDist)
      MaxDist = D[i][j];
  }
  return MaxDist;
}

void FindAnimal()
{
  Vertex Animal, i;
  WeightType MinDist = INFINITY, dist;
  for(i = 0; i < V; i++) {
    dist = FindMaxDist(i);
    if(dist == INFINITY) {
      printf("0\n");
      return;
    }
    if(dist < MinDist){
      MinDist = dist;
      Animal = i + 1;
    } 
  }
  printf("%d %d\n",Animal, MinDist);
}

int main()
{
  Vertex X, Y;
  WeightType W;
  Vertex i, j;
  scanf("%d %d",&V, &M);
  // 初始化临接矩阵
  for(i = 0; i < V; i++) {
     for(j = 0; j < V; j++) {
      Graph[i][j] = INFINITY;
    }
  }
  for(i = 0; i < M; i++) {
    scanf("%d %d %d", &X, &Y, &W);
    Graph[X - 1][Y - 1] = W;
    Graph[Y - 1][X - 1] = W;
  }
  // 弗洛伊德算法
  if(Floyd()) {
    FindAnimal();
  } 
  return 0;
}