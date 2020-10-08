#include<stdio.h>
#include<stdlib.h>


typedef int ElementType;
typedef struct TNode *Position;
typedef Position BST;
struct TNode {
  ElementType Data;
  BST Left,Right;
  int Flag;
};

/*
算法描述：
1. 构建比较树
2. 所有结点顺序比较，若经过flag = 0 的点且值不相同，则不是同一棵树
3. 每判断完flag归零，全部判断完free树
*/
BST MakeTNode(ElementType X)
{
  BST T;
  T = (BST)malloc(sizeof(struct TNode));
  T->Data = X;
  T->Left = T->Right = NULL;
  T->flag = 0;
  return T;
}

BST Insert(BST T, ElementType X)
{
  if(!T){
    T = MakeTNode(X);
    return T;
  }else {
    if(T->Data > X) {
      T->Left = Insert(T->Left, X);
    }else {
      T->Right = Insert(T->Right, X);
    }
  }
  return T;
}

BST MakeTree(int N)
{
  int i;
  ElementType X;
  BST T;
  scanf("%d", &X);
  T = MakeTNode(X);
  for(i = 1; i < N; i++) {
    scanf("%d", &X);
    T = Insert(T, X);
  }
  return T;
}

int Check(BST T, ElementType X)
{
  if(T) {
    if(T->Flag == 1) {
      if(T->Data > X) return Check(T->Left, X);
      if(T->Data < X) return Check(T->Right, X);
    }else {
      if(T->Data == X) 
        T->Flag = 1;
        return 1;
      else 
        return 0;
    }
  }
  return 0;
}

int Judge(BST T, int N)
{
  int i,flag = 0;
  ElementType X;
  for(i = 0;i < N; i++) {
    scanf("%d", &X);
    if((!flag) && (!Check(T, X))) flag = 1;
  }
  if(flag) return 0;
  else return 1;
}

void Reset(BST T)
{
  if(T) {
    Reset(T->Left);
    Reset(T->Right);
    T->Flag = 0;
  }
}

void FreeTree(BST T)
{
  if(T) {
    FreeTree(T->Left);
    FreeTree(T->Right);
    free(T);
  }
}


int main()
{
  int N,L,i;
  BST T;
  scanf("%d", &N);
  while(N) {
    scanf("%d", &L);
    T = MakeTree(N);
    for(i = 0; i < L;i ++) {
      if(Judge(T, N)) printf("Yes\n");
      else printf("No\n");
      Reset(T);
    }
    FreeTree(T);
    scanf("%d", & N);
  }
}