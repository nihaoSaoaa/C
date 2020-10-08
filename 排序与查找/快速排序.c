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


/* 快速排序 */
// 找主元
int Median3(int A[], int Left, int Right)
{
  int Center = (Left + Right) / 2;
  if(A[Left] > A[Center]) {
    Swap(&A[Left], &A[Center]);
  }
  if(A[Left] > A[Right]) {
    Swap(&A[Left], &A[Right]);
  }
  if(A[Center] > A[Right]) {
    Swap(&A[Center], &A[Right]);
  }
  Swap(&A[Center], &A[Right - 1]);
  return A[Right - 1];
}

// 核心算法
void Qsort(int A[], int Left, int Right)
{
  // 元素较少时进入插入排序
  int Pivot, CutOff = 100, Low, High;
  if(CutOff <= Right - Left) {
    Pivot = Median3(A, Left, Right);
    Low = Left;
    High = Right - 1;
    while(1) {
      while(A[++Low] < Pivot);
      while(A[++High] > Pivot);
      if(Low < High) {
        Swap(&A[Low], &A[High]);
      }else {
        break;
      }
    }
    Swap(&A[Low], &A[Right - 1]);
    Qsort(A, Left, Low - 1);
    Qsort(A, Low + 1, Right);
  }
  else InsertionSort(A + Left, Right - Left + 1);
}

void QuickSort(int A[], int N)
{
  Qsort(A, 0, N - 1);
}



int main()
{
  int i, N = 10, A[MAX] = {5, 1, 8, 7, 10, 6, 2, 3, 4, 9};

  QuickSort(A, N);
  for(i = 0; i < N; i++) {
    if(i == N - 1) printf("%d\n", A[i]);
    else printf("%d ", A[i]);
  }
  
  return 0;
}
