#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode {
  ElementType Data;
  AVLTree Left,Right;
  int Height;
};

int Max(int a, int b)
{
  return (a > b) ? a : b;
}

int GetHeight(AVLTree T)
{
  if(T == NULL) {
    return 0;
  }
  return T->Height;
}

AVLTree LL(AVLTree T)
{
  AVLTree L = T->Left;
  T->Left = L->Right;
  L->Right = T;
  T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
  L->Height = Max(GetHeight(L->Left), GetHeight(L->Right)) + 1;
  return L;
}

AVLTree RR(AVLTree T)
{
  AVLTree R = T->Right;
  T->Right = R->Left;
  R->Left = T;
  T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
  R->Height = Max(GetHeight(R->Left), GetHeight(R->Right)) + 1;
  return R;
}

AVLTree LR(AVLTree T)
{
  T ->Left = RR(T->Left);
  return LL(T);
}

AVLTree RL(AVLTree T)
{
  T ->Right = LL(T->Right);
  return RR(T);
}

AVLTree Insert(AVLTree T, ElementType X)
{
  if(!T) {
    T = (AVLTree)malloc(sizeof(struct AVLNode));
    T->Data = X;
    T->Height = 0;
    T->Left = T->Right = NULL;
  }
  else if(X < T->Data) {
    T->Left = Insert(T->Left, X);
    if(GetHeight(T->Left) - GetHeight(T->Right) == 2) {
      if (X < T->Left->Data) {
        T= LL(T);
      }else {
        T = LR(T);
      }
    }
  }
  else if(X > T->Data) {
    T->Right = Insert(T->Right, X);
    if(GetHeight(T->Right) - GetHeight(T->Left) == 2) {
      if(X > T->Right->Data) {
        T = RR(T);
      }else {
        T = RL(T);
      }
    }
  }
  T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
  return T;
}

int main()
{
  int N, i, X;
  AVLTree T = NULL;
  scanf("%d", &N);
  for(i = 0; i < N; i++) {
    scanf("%d", &X);
    T = Insert(T, X);
  }
  printf("%d", T->Data);
  return 0;
}