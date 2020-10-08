#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define ERROR -1 

typedef int ElementType;

typedef int Position;
struct QNode {
  ElementType *Data;
  Position Front,Rear;
  int MaxSize;
};
typedef struct QNode *Queue;

Queue createQueue(int MaxSize)
{
  Queue Q = (Queue)malloc(sizeof(struct QNode));
  Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
  Q->Front = Q->Rear = 0;
  Q->MaxSize = MaxSize;
  return Q;
}


bool IsFull(Queue Q)
{
  return ((Q->Rear + 1)%Q->MaxSize == Q->Front);
}

bool IsEmpty(Queue Q)
{
  return (Q->Front == Q->Rear);
}

bool AddQ(Queue Q,ElementType x)
{
  if(IsFull(Q)) {
    printf("queue is full!\n");
    return false;
  }
  Q->Rear = (Q->Rear + 1)% Q->MaxSize;
  Q->Data[Q->Rear] = x;
  return true;
}

ElementType DeleteQ(Queue Q)
{
  if(IsEmpty(Q)) {
    printf("queue is empty!\n");
    return ERROR;
  }
  Q->Front = (Q->Front + 1)% Q->MaxSize;
  return Q->Data[Q->Front];
}

int main()
{
  Queue Q = createQueue(5);
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
