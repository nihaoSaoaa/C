#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

#define MaxDigit 4 /* 最多关键字数 */ 
#define radix 10   /* 基数 */

/* 桶结点 */
typedef struct Node *PtrToNode;
struct Node {
  int key;
  PtrToNode next;
};


/* 桶头 */
struct HeadNode {
  PtrToNode head, tail;
};
typedef struct HeadNode Bucket[radix];

// 获取关键字
int GetDigit(int X, int D)
{
  int i, d;
  for(i = 1; i <= D; i++) {
    d = X % radix;
    X /= radix;
  }
  return d;
}

// 结点放入桶
void InsertBNode(Bucket B, PtrToNode P, int Di)
{
  if(B[Di].head == NULL) {
    B[Di].head = B[Di].tail = P;
  }else {
    B[Di].tail->next = P;
    B[Di].tail = P;
  }
}

// 桶结点一串出桶
void DeleteBNode(Bucket B, int Di, PtrToNode List)
{
  if(B[Di].head) {
    B[Di].tail->next = List;
    List = B[Di].head;
    B[Di].head = B[Di].tail = NULL;
  }
}

void LSDRadixSort(int A[], int N)
{
  int i, D, Di;
  PtrToNode List = NULL, tmp, p;
  Bucket B;
  // 1. 初始化桶，将序列逆序存入链表
  for(i = 0; i < radix; i++) {
    B[i].head = B[i].tail = NULL;
  }
  for(i = 0; i < N; i++) {
    tmp = (PtrToNode)malloc(sizeof(struct Node));
    tmp->key = A[i];
    tmp->next = List;
    List = tmp;
  }
  // 2. 开始排序
  for(D = 1; D <= MaxDigit; D++) {
    p = List;
    // 2.1 入桶
    while(p) {
      Di = GetDigit(p->key, D);
      tmp = p;p = p->next;tmp->next = NULL;
        if(B[Di].head == NULL) {
          B[Di].head = B[Di].tail = tmp;
        }else {
          B[Di].tail->next = tmp;
          B[Di].tail = tmp;
        }
    }
    
    // 2.2 收集(出桶)
    List = NULL;
    for(Di = radix - 1; Di >= 0; Di--) {
      if(B[Di].head) {
        B[Di].tail->next = List;
        List = B[Di].head;
        B[Di].head = B[Di].tail = NULL;
      }
    }
  }
  printf("----\n");
  for (i=0; i<N; i++) {
    tmp = List;
    List = List->next;
    A[i] = tmp->key;
    free(tmp);
  } 
}

int main()
{
  int i, N = 10, A[MAX] = {122, 4233, 23, 2341, 94, 250, 1111, 4396, 777, 9};

  LSDRadixSort(A, N);
  for(i = 0; i < N; i++) {
    if(i == N - 1) printf("%d\n", A[i]);
    else printf("%d ", A[i]);
  }
  
  return 0;
}
