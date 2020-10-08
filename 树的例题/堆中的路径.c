#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

#define MINDATA -10001

typedef int ElementType;
typedef int Position;

typedef struct HNode *PtrToHNode;
struct HNode {
  ElementType *Data;
  int Size;
  int Capacity;
};
typedef PtrToHNode MinHeap;

MinHeap CreateHeap(int MaxSize)
{
  MinHeap H;
  H = (MinHeap)malloc(sizeof(struct HNode));
  H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
  H->Size = 0;
  H->Capacity = MaxSize;
  H->Data[0] = MINDATA;
  return H;
}

bool isFull(MinHeap H)
{
  return (H->Size == H->Capacity);
}

void Insert(MinHeap H, ElementType X)
{
  int i;
  if(isFull(H)) {
    printf("HEAP IS FULL!");
    return;
  }
  i = ++H->Size;
  while(H->Data[i / 2] > X) {
    H->Data[i] = H->Data[i / 2];
    i = i / 2;
  }
  H->Data[i] = X;
}

void PrintfHPath(MinHeap H, Position P)
{
  Position i;
  i = P;
  while(i > 0) {
    if(i == 1) {
      printf("%d\n", H->Data[i]);
    }else {
      printf("%d ",H->Data[i]);
    }
    i /= 2;
  }
}

int main()
{
  int N, M, i;
  ElementType Data;
  Position P;
  MinHeap H;
  scanf("%d %d", &N, &M);
  H = CreateHeap(N);
  if(N) {
    for(i = 0; i < N; i++) {
      scanf("%d", &Data);
      Insert(H, Data);
    }
  }
  if(M) {
    for(i = 0; i < M; i++) {
      scanf("%d", &P);
      PrintfHPath(H,P);
    }
  }
  return 0;
}
