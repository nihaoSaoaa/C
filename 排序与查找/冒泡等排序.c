#include <stdio.h>
#include <stdlib.h>
#define MAX 100000
/*
所有算法均为整数从大到小排序
*/

// 交换算法
void Swap(int *a, int *b) 
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

/* 冒泡排序 */
void BubbleSort(int A[], int N)
{
  int i, j;
  for(i = N - 1; i > 0; i--) {
    for(j = 0; j < i; j++) {
      if(A[j] > A[j + 1]) {
        Swap(&A[j], &A[j + 1]);
      }
    }
  }
}

/* 插入排序 */
void InsertionSort(int A[], int N)
{
  int i, j, tmp;
  for(i = 1; i < N; i++) {
    tmp = A[i];
    for(j = i; j > 0; j--) {
      if(A[j - 1] > tmp) {
        A[j] = A[j - 1];
      }else {
        break;
      }
      
    }
    A[j] = tmp;
  }
}

/* 插入排序升级 -- 希尔排序:用Sedgewick增量序列 */
void ShellSort(int A[], int N)
{ 
  int Si,D;
  int i, j, tmp;
  int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
  for(Si = 0; Sedgewick[Si] >= N; Si++);
  for(D = Sedgewick[Si]; D > 0; D = Sedgewick[Si++]) {// 插入
     for(i = 1; i < N; i++) {
      tmp = A[i];
      for(j = i; j > 0; j--) {
        if(A[j - 1] > tmp) {
          A[j] = A[j - 1];
        }else {
          break;
        }
        
      }
      A[j] = tmp;
    }
  }
}


/* 选择排序 */
int FindMinIndex(int A[], int S, int E) {
  int i, Min = A[S], MinIndex = S;
  for(i = S + 1; i <= E; i++) {
    if(A[i] < Min) {
      Min = A[i];
      MinIndex = i;
    }
  }
  return MinIndex;
}

void SelectionSort(int A[], int N)
{
  int i, MinPosition;
  for(i = 0; i < N - 1; i++) {
    MinPosition = FindMinIndex(A, i, N - 1);
    Swap(&A[i], &A[MinPosition]);
  }
}

/* 选择排序升级 -- 堆排序：对选出最小进行改造 */
void PercDown( int A[], int p, int N )
{ 
    int Parent, Child;
    int X;
 
    X = A[p]; /* 取出根结点存放的值 */
    for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
        Child = Parent * 2 + 1;
        if( (Child!=N-1) && (A[Child]<A[Child+1]) )
            Child++;  /* Child指向左右子结点的较大者 */
        if( X >= A[Child] ) break; /* 找到了合适位置 */
        else  /* 下滤X */
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void HeapSort(int A[], int N)
{
  int i;
  for(i = N / 2 - 1; i >= 0; i--) {
    PercDown(A, i, N);
  }
  for(i = N - 1; i > 0; i--) {
    Swap(&A[0], &A[i]);
    PercDown(A, 0, i);
  }
}

/* 归并排序 */
// 核心--归并算法
void Merge(int A[], int tmpA[], int Left, int Right, int RightEnd)
{
  int LeftEnd, NumElements, tmp;
  int i;
  tmp = Left;
  LeftEnd = Right - 1;
  NumElements = RightEnd - Left + 1;
  while(Left <= LeftEnd && Right <= RightEnd) {
    if(A[Left] <= A[Right]) {
      tmpA[tmp++] = A[Left++];
    }else {
      tmpA[tmp++] = A[Right++];
    }
  }
  while(Left <= LeftEnd) {
    tmpA[tmp++] = A[Left++];
  }
  while(Right <= RightEnd) {
    tmpA[tmp++] = A[Right++];
  }
  for(i = RightEnd; i > RightEnd - NumElements; i--) {
    A[i] = tmpA[i];
  }
}

// 递归
void MSort(int A[], int tmpA[], int Left, int RightEnd)
{
  int center;
  if(Left < RightEnd) {
    center = (Left + RightEnd) / 2;
    MSort(A, tmpA, Left, center);
    MSort(A, tmpA, center + 1, RightEnd);
    Merge(A, tmpA, Left, center + 1, RightEnd);
  }
}

void MergeSort1( int A[], int N )
{
  int *tmpA;
  tmpA = (int *)malloc(sizeof(int) * N);
  if(tmpA) {
    MSort(A, tmpA, 0, N - 1);
    free(tmpA);
  } 
  else printf("空间不足！");
}

// 循环 ,length 为 归并的子序列长度
void Merge_pass(int A[], int tmpA[], int N, int Length)
{
  int i, j;
  for(i = 0; i <= N - 2*Length; i += 2*Length) {
    Merge(A, tmpA, i, i + Length, i + 2*Length - 1);
  }
  if(N - i > Length) {
    Merge(A, tmpA, i, i + Length, N - 1);
  }
  else {
    for(j = i; j < N; j++) {
      tmpA[j] = A[j];
    }
  }
}

void MergeSort2( int A[], int N )
{
    int *tmpA;
    int Length = 1;
    tmpA = (int *)malloc(sizeof(int) * N);
    if(tmpA) {
      while(Length < N) {
        Merge_pass(A, tmpA, N, Length);
        Length *= 2;
        Merge_pass( tmpA, A, N, Length );
        Length *= 2;
      }
      free(tmpA);
    } 
    else printf("空间不足！");
}

int main()
{
  int i, N, A[MAX];
  scanf("%d", &N);
  for(i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  BubbleSort(A, N);
  for(i = 0; i < N; i++) {
    if(i == N - 1) printf("%d\n", A[i]);
    else printf("%d ", A[i]);
  }
  
  return 0;
}
