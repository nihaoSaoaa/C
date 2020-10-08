#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define ERROR -1 

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

bool AddQ(Queue Q, ElementType x)
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

ElementType DeleteQ(Queue Q)
{
  PtrToNode FrontCell;
  ElementType FrontElem;
  if(IsEmpty(Q)) {
    return ERROR;
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

int main()
{
  Queue Q = createQueue();
  int flag = 1, x;

  while (flag != -1){
    scanf("%d", &flag);
    if(flag == 1) {
      scanf("%d", &x);
      AddQ(Q, x);
    }else {
      printf("%d\n", DeleteQ(Q));
    }
  };
  return 0;
}