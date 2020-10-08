#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 101

// 测试插入排序
bool TestInsertSort(int A[], int T[], int N)
{
  int i, p;
  bool flag = false;
  for(i = 0; i < N && T[i + 1] > T[i]; i++);
  p = i + 1;
  for(i = p;i < N;i++) {
    if(A[i] != T[i]) {
      flag = true;
    }
  }
  if(flag) return false;
  else {
    printf("Insertion Sort\n");
    int tmp = T[p];
    for(i = p; i > 0; i-- ) {
      if(T[i - 1] > tmp) {
        T[i] = T[i - 1];
      }else {
        break;
      }
    }
    T[i] = tmp;
    for(i = 0; i < N; i++) {
      if(i == N - 1)
        printf("%d\n", T[i]);
      else
        printf("%d ", T[i]);    
    } 
    return true;
  }
}

// 测试归并排序
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

void TestMergeSort(int A[], int T[], int N)
{
  int i, p, len;
  int *tmpA = (int*)malloc(sizeof(int) * N); 
  for(len = 2; len <= N; len *= 2) {
    for(i = 0; i < N - 2*len; i+= 2*len) {
      if(T[i + len - 1] > T[i + len]) {
        break;
      }
    }
    if(N - i > len) {
      if(T[i + len - 1] > T[i + len]) {
        break;
      }
    }
  }
  Merge_pass(T, tmpA, N, len);
  printf("Merge Sort\n");
  for(i = 0; i < N; i++) {
    if(i == N - 1)
      printf("%d\n", tmpA[i]);
    else
      printf("%d ", tmpA[i]);    
  }
  free(tmpA);
}

// 测试堆排序
void Swap(int *a, int *b) 
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

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

void TestHeapSort(int A[], int T[],int N)
{
  int i;
  for(i = N / 2 - 1; i >= 0; i--) {
    PercDown(A, i, N);
  }
  for(i = N - 1; i > 0; i--) {
    Swap(&A[0], &A[i]);
    PercDown(A, 0, i);
    if(A[i] != T[i]) {
      break;
    }
  }
  printf("Heap Sort\n");
  for(i = 0; i < N; i++) {
    if(i == N - 1)
      printf("%d\n", A[i]);
    else
      printf("%d ", A[i]);   
  }
}

int main()
{
  int i, N; 
  int A[MAX];
  int T[MAX];
  scanf("%d", &N);
  for(i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  for(i = 0; i < N; i++) {
    scanf("%d", &T[i]);
  }
  if(N >= 4) {
    if(TestInsertSort(A, T, N) == false)
      TestHeapSort(A, T, N);
  }
  return 0;
}
