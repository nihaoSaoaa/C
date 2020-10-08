#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 10
#define ERROR -1


typedef int Position;
typedef int ElementType;

typedef struct LNode {
  ElementType Data[MAXSIZE];
  Position Last;
}LNode, *List;

// 创建一个空表
List MakeEmpty() 
{
  List L;
  L = (List)malloc(sizeof(LNode));
  L->Last = -1;
  return L;
}

// 查找
Position Find(List L, ElementType x)
{
  Position i = 0;
  while(L->Data[i] != x && i <= L->Last)
    i ++;
  if (i > L->Last) return ERROR;
  else return i;
}

// 插入
bool Insert(List L, ElementType x, Position p)
{
  Position i;
  // 1.检查表是否已满
  if (L->Last == MAXSIZE - 1) {
    printf("List is full!\n");
    return false;
  }
  // 2. 检查插入位置的合法性
  if (p < 0 || p > L->Last + 1) {
    printf("Position is not available!\n");
    return false;
  }
  // 3. 将插入位置以后的元素向后移动
  for (i = L->Last; i >= p; i--)
    L->Data[i+1] = L->Data[i];
  L->Data[p] = x;
  L->Last++;
  return true;
}

// 删除
bool Delete(List L, Position p) 
{
  Position i;
  if (p < 0 || p > L->Last) {
    printf("Position is not available!\n");
    return false;
  }
  for(i = p; i <= L->Last - 1; i ++) 
    L->Data[i] = L->Data[i + 1];
  L->Last--;
  return true;
}

void output(List L)
{
  Position i;
  for(i = 0; i <= L->Last; i ++)
    printf("%d\n", L->Data[i]);
}

int main() 
{
  List L;
  ElementType x;
  Position p;
  L = MakeEmpty();
  while(L->Last < 5) {
    scanf("%d %d", &x, &p);
    Insert(L,x,p);
  }
  output(L);
  
  return 0;
}
