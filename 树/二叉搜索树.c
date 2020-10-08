#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
  ElementType Data;
  BinTree Left;
  BinTree Right;
};

// 先序遍历
void PreorderTraversal( BinTree BT )
{
  if(BT) {
    printf("%d ",BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
  }
}
// 中序遍历
void InorderTraversal( BinTree BT )
{
  if(BT) {
    InorderTraversal(BT->Left);
    printf("%d",BT->Data);
    InorderTraversal(BT->Right);
  }
}

Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );
BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );


int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

Position Find( BinTree BST, ElementType X )
{
  if(!BST) return NULL;
  if(BST->Data == X) return BST;
  else if(BST->Data > X) return Find(BST->Left, X);
  else return Find(BST->Right, X);
}

Position FindMin( BinTree BST )
{
  if(!BST) return NULL;
  if(!BST->Left) return BST;
  else return FindMin(BST->Left); 
}

Position FindMax( BinTree BST )
{
  if(!BST) return NULL;
  while(BST->Right) {
    BST = BST->Right;
  }
  return BST;
}

BinTree Insert( BinTree BST, ElementType X )
{
  if(!BST) {
    BST = (BinTree)malloc(sizeof(struct TNode));
    BST->Data = X;
    BST->Left = BST->Right = NULL;
  }
  else {
    if(BST->Data > X) {
      BST->Left = Insert(BST->Left, X);
    }else if(BST->Data < X) {
      BST->Right = Insert(BST->Right, X);
    }
  }
  return BST;
}

BinTree Delete( BinTree BST, ElementType X )
{
  Position Tmp;
  if(!BST) printf("Not Found\n");
  else {
    if(BST->Data > X) {
      BST->Left = Delete(BST->Left, X);
    }else if(BST->Data < X) {
      BST->Right = Delete(BST->Right, X);
    }else {
      if(BST->Left && BST->Right) {
        Tmp = FindMax(BST->Left);
        BST->Data = Tmp->Data;
        BST->Left = Delete(BST->Left, BST->Data);
      }else {
        Tmp = BST;
        if(!BST->Left) {
          BST = BST->Right;
        }else {
          BST = BST->Left;
        }
        free(Tmp);
      }
    }
  }
  return BST;
}