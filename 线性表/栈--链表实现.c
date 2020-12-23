#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define ERROR -1 

typedef int ElementType; 
typedef struct SNode *PtrToSNode;
typedef struct SNode {
  ElementType Data;
  PtrToSNode Next;
}SNode;

typedef PtrToSNode Stack;

Stack CreateStack()
{
  Stack S = (Stack)malloc(sizeof(SNode));
  S->Next = NULL;
  return S; 
}

bool IsEmpty(Stack S)
{
  return (S->Next == NULL);
}

bool Push(Stack S, ElementType x)
{
  PtrToSNode TmpCell;
  TmpCell = (PtrToSNode)malloc(sizeof(SNode));
  TmpCell->Data = x;
  TmpCell->Next = S->Next;
  S->Next = TmpCell;
  return true;
}

/*删除并返回要删除的值 */
ElementType Pop(Stack S)
{
  PtrToSNode FirstCell;
  ElementType TopElem;
  if (IsEmpty(S)) {
    printf("stack is empty!\n");
    return ERROR;
  }else {
    FirstCell = S->Next;
    TopElem = FirstCell->Data;
    S->Next = FirstCell->Next;
    free(FirstCell);
    return TopElem;
  }
}

void output(Stack S) {
  PtrToSNode p = S->Next;
  printf("Stack:");
  while(p) {
    printf("%d ",p->Data);
    p = p->Next;
  }
  printf("\n");
}

int main()
{
  /*test code*/
  int flag = 1, x;
  Stack s = CreateStack();
  while(flag == 1 || flag == 2) {
    scanf("%d %d", &flag, &x);
    if (flag == 1) {
      Push(s, x);
    }else if (flag == 2) {
      Pop(s);
    }
    output(s);
  }
  return 0;
}