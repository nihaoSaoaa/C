#include<stdio.h>
#include<stdlib.h>

#define MaxSize 10
#define Null -1

typedef char ElementType;
typedef int Tree;
// 结构数组表示二叉树：静态链表
struct TreeNode {
  ElementType Element;
  Tree left;
  Tree right;
} T1[MaxSize], T2[MaxSize];

// 建树并返回根节点索引
Tree BuildTree(struct TreeNode T[] );

// 判断树的同构
int Isomorohic(Tree R1, Tree R2);

int main()
{
  Tree R1, R2;
  R1 = BuildTree(T1);
  R2 = BuildTree(T2);
  if(Isomorohic(R1, R2))
    printf("Yes\n");
  else
    printf("No\n");
  return 0;
}

Tree BuildTree(struct TreeNode T[] )
{
  int N, Root = Null, i;
  char el, er;
  int check[MaxSize];
  printf("print N:");
  scanf("%d", &N);
  if(N) {
    for(i = 0;i < N; i++) {
    check[i] = 0;
    }
    for(i = 0;i < N; i++) {
      scanf("\n%c %c %c",&T[i].Element, &el, &er);
      if(el == '-') {
        T[i].left = Null;
      }else {
        T[i].left = el - '0';
        check[T[i].left] = 1;
      }
      if(er == '-') {
        T[i].right = Null;
      }else {
        T[i].right = er - '0';
        check[T[i].right] = 1;
      }
    }
    for(i = 0;i < N; i++) {
      if(!check[i]) break;
    }
    Root = i;
    return Root;
  }
}

/**
 * 根节点均为空
 * 根节点一空一不空
 * 值不相同
 * 左子节点均为空:右子树同构
 * 左子节点的值均相等：左同构，右同构
 * 其他情况：翻转
 */
int Isomorohic(Tree R1, Tree R2)
{
  if(R1 == Null && R2 == Null) return 1;
  if((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null)) return 0;
  if(T1[R1].Element != T2[R2].Element) return 0;
  if(T1[R1].left == Null && T2[R2].left == Null)
    return Isomorohic(T1[R1].right, T2[R2].right);
  if(T1[R1].left != Null && T2[R2].left != Null && T1[T1[R1].left].Element == T2[T2[R2].left].Element)
    return (Isomorohic(T1[R1].left, T2[R2].left) && Isomorohic(T1[R1].right, T2[R2].right));
  else
    return (Isomorohic(T1[R1].left, T2[R2].right) && Isomorohic(T1[R1].right, T2[R2].left));
}
