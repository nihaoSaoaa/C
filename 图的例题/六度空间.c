#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 1000
int Graph[MAXSIZE][MAXSIZE];
int Visited[MAXSIZE];
int N, M;


typedef struct Node* PtrToNode;
struct Node {
  int Data;
  PtrToNode Next;
};
struct QNode {
  PtrToNode Front,Rear;
};
typedef struct QNode* Queue;

Queue createQueue()
{
  Queue Q = (Queue)malloc(sizeof(struct QNode));
  Q->Front = NULL;
  Q->Rear = NULL;
  return Q;
}

bool IsEmpty(Queue Q)
{
  return (Q->Front == NULL);
}

bool AddQ(Queue Q, int x)
{
  PtrToNode TmpCell;
  TmpCell = (PtrToNode)malloc(sizeof(struct Node));
  TmpCell->Data = x;
  if (IsEmpty(Q)) {
    Q->Front = Q->Rear = TmpCell;
  }else {
    Q->Rear->Next = TmpCell;
    Q->Rear = TmpCell;
  }
  return true;
}

int DeleteQ(Queue Q)
{
  PtrToNode FrontCell;
  int FrontElem;
  if(IsEmpty(Q)) {
    return -1;
  }
  else {
    FrontCell = Q->Front;
    if (Q->Front == Q->Rear) {
      Q->Front = Q->Rear = NULL;
    }else {
      Q->Front = FrontCell->Next;
    }
    FrontElem = FrontCell->Data;
    free(FrontCell);
    return FrontElem;
  }
}

void InitVisit()
{
  int i;
  for(i = 0; i < N; i++) {
    Visited[i] = 0;
  }
}

void BFS(int i)
{
  int counter = 0, now = 0, next = 0, level = 0, x, j;
  float result;
  Queue Q = createQueue();
  Visited[i] = 1;
  AddQ(Q, i);
  now++;
  while(!IsEmpty(Q)) {
    x = DeleteQ(Q);
    if(!now && next) {
      now = next;
      next = 0;
      level++;
      if(level == 7) {
        break;
      }
    }
    counter++;
    now--;
    for(j = 0; j < N; j++) {
      if(Graph[x][j] == 1 && Visited[j] == 0) {
        AddQ(Q, j);
        Visited[x] = 1;
        next++;
      }
    }
  }
  result = (float)counter / N * 100;
  printf("%d: %.2f\%\n", i + 1, result);
  return;
}


void solve()
{
  int i;
  for(i = 0; i < N; i++) {
    InitVisit();
    BFS(i);
  }
}


int main()
{
  int i, j, v, w;
  scanf("%d %d", &N, &M);
  for(i = 0; i < N; i++) {
    for(j = 0; j < N; j++) {
      Graph[i][j] = 0;
    }   
  }
  for(i = 0; i < M; i++) {
    scanf("%d %d", &v, &w);
    Graph[v - 1][w - 1] = 1;
    Graph[w - 1][v - 1] = 1;
  }
  solve();
  return 0;
}
