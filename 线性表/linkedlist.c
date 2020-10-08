#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;

typedef struct LNode *PtrTolNode;
struct LNode {
  ElementType Data;
  PtrTolNode Next;
};
typedef PtrTolNode Position;
typedef PtrTolNode List;

/*查找*/
#define ERROR NULL;
Position Find(List L, ElementType x)
{
  Position p = L;
  while(p && p->Data != x) {
    p = p->Next;
  }
  if (p) return p;
  else return ERROR;
}

/*插入（在结点p前插入带x元素的结点）*/
bool Insert(List L, ElementType x, Position p)
{
  Position pre = L, tmp;
  while(pre && pre->Next != p) {
    pre = pre->Next;
  }
  if (pre == NULL) {
    printf("your position is error!\n");
    return false;
  }
  else {
    tmp = (Position)malloc(sizeof(struct LNode));
    tmp->Data = x;
    tmp->Next = p;
    pre->Next = tmp;
    return true;
  }
}

bool Delete(List L, Position p)
{
  Position pre = L;
  while(pre && pre->Next != p) {
    pre = pre->Next;
  }
  if (pre == NULL || p == NULL) {
    printf("your posiiton is error!");
    return false;
  }
  else {
    pre->Next = p->Next;
    free(p);
    return true;
  }
}