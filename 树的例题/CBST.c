#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
int A[MAXSIZE], CBT[MAXSIZE];

int compare(const void *a,const void *b) 
{
  return *(int *)a - *(int *)b;
}

/**
 *算法核心： 
 * 根据完全二叉树的节点个数，获得其左子树的节点个数
 * 1. 计算除了最后一层外有树的层树 H = log（N + 1）
 * 2. 计算最后一层节点数X : 2^H - 1 + X = N
 * 3. 计算左子树可能的最大最后一层节点数 XMAX
 * 4. 计算左子树节点数 2^H - 1 + min{X, XMAX}
*/
int GetLeftLength(int N)
{
  int i;
  int n = N + 1, H = 0, sum = 1, X, LastN;
  int L;
  while(n > 1) {
    n /= 2;
    H++;
  }
  for(i = 0; i < H; i ++) {
    sum *= 2;
  }
  X = N + 1 - sum;
  LastN = (sum / 2 > X) ? X : sum / 2;
  L = sum / 2 - 1 + LastN;
  return L;
}

void solve(int ALeft, int ARight, int TRoot)
{
  int n,L;
  n = ARight - ALeft + 1;
  if(n == 0) return;
  L = GetLeftLength(n);
  CBT[TRoot] = A[ALeft + L];
  solve(ALeft, ALeft + L - 1, 2*TRoot + 1);
  solve(ALeft + L + 1, ARight, 2*TRoot + 2);
}

int main()
{
  int N, i;
  scanf("%d", &N);
  for(i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  qsort(A, N, sizeof(int), compare);
  solve(0, N - 1, 0);
  for(i = 0; i < N; i++) {
    if(i == 0)
      printf("%d", CBT[i]);
    else
      printf(" %d", CBT[i]);
  }
  return 0;
}