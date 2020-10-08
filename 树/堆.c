#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef int ElementType;

typedef struct HNode *Heap;
struct HNode {
  ElementType *Data;
  int Size;
  int Capacity;
};
typedef Heap MaxHeap;
typedef Heap MinHeap;

/* 该值应根据具体情况定义为大于堆中所有可能元素的值,存储在 0 位作为 ‘哨兵’元素 */
#define MAXDATA 1000

MaxHeap CreateHeap(int MaxSize)
{
  MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
  H->Data = (ElementType *)malloc((MaxSize +1) * sizeof(ElementType));
  H->Size = 0;
  H->Capacity = MaxSize;
  H->Data[0] = MAXDATA;
  return H;
}

bool isFull(MaxHeap H)
{
  return (H->Size == H->Capacity);
}

bool Insert(MaxHeap H, ElementType X)
{
  int i;
  // 判满
  if(isFull(H)) {
    printf("HEAP IS FULL!");
    return false;
  }
  // 个数加 1 并保存到 i
  i = ++H->Size;
  // 路径上比 x 小的值向下移动
  while(H->Data[i / 2] < X) {
    H->Data[i] = H->Data[i / 2];
    i = i / 2;
  }
  // 找到位置
  H->Data[i] = X;
  return true;
}

bool isEmpty(MaxHeap H)
{
  return (H->Size == 0);
}

ElementType DeleteMax(MaxHeap H)
{
  ElementType MaxData, temp;
  int Parent = 1, Child;
  // 判满
  if(isEmpty(H)) {
    printf("HEAP IS EMPTY!");
    return -1;
  }
  // 获取最大值和最后一个值，size - 1
  MaxData = H->Data[1];
  temp = H->Data[H->Size--];
  // 将子节点中最大的与 temp 比较，若前者大则往上提，否则跳出循环（tmp 满足比子节点大）
  // 循环的条件是有子节点
  while(Parent * 2 <= H->Size) {
    Child = Parent * 2;
    if(Child != H->Size && (H->Data[Child] < H->Data[Child + 1])){
      Child ++;
    }
    if(H->Data[Child] > temp) {
      H->Data[Parent] = H->Data[Child];
    }else {
      break;
    }
    Parent = Child;
  }
  H->Data[Parent] = temp;
  return MaxData;
}

void PerDown(MaxHeap H, int i)
{
  int Parent = i, Child;
  ElementType X = H->Data[i];
  while(Parent * 2 <= H->Size) {
    Child = Parent * 2;
    if(Child != H->Size && (H->Data[Child] < H->Data[Child + 1])) {
      Child ++;
    }
    if(H->Data[Child] > X) {
      H->Data[Parent] = H->Data[Child];
    }else {
      break;
    }
    Parent = Child;
  }
  H->Data[Parent] = X;
}

void buildHeap(MaxHeap H)
{
  int i;
  for(i = H->Size / 2; i > 0; i --) {
    PerDown(H, i);
  }
}

