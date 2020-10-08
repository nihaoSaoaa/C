#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

int N;
int Graph[MAXSIZE][MAXSIZE];
int Table[MAXSIZE];

struct HNode{
  int Size;
  int* Data;
};
typedef struct HNode *MinHeap;

void initGraph(int N)
{
  int i, j;
  for(i = 0; i < N; i++) {
    for(j = 0; j < N; j++) {
      Graph[i][j] = 0;
    }
  }
}

MinHeap createMinHeap(int N)
{
  MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
  H->Data = (int *)malloc(sizeof(int) * (N + 1));
  H->Size = 0;
  H->Data[0] = -2;
  return H;
}

void InsertHeap(MinHeap H ,int index)
{
  int i = ++H->Size;
  while( i / 2 > 0 && Table[H->Data[i / 2]] > Table[index]) {
    H->Data[i] = H->Data[i / 2];
    i = i / 2;
  }
  H->Data[i] = index;
}

int DeleteMin(MinHeap H)
{
  int min = H->Data[1];
  int tmp = H->Data[H->Size--];
  int parent = 1, children;
  while(parent * 2 <= H->Size) {
    children = parent * 2;
    if(children < H->Size && Table[H->Data[children + 1]] < Table[H->Data[children]]) {
      children ++;
    }
    if(Table[H->Data[children]] < Table[tmp]) {
      H->Data[parent] = H->Data[children];
    }else {
      break;
    }
    parent = children;
  }
  H->Data[parent] = tmp;
  return min;
}

int Hash(int Key, int N)
{
  return Key % N;
}



void TopSort()
{
  int Indgree[MAXSIZE], V;
  MinHeap H = createMinHeap(N);
  int i, j;
  for(i = 0; i < N; i++) {
    Indgree[i] = 0;
    for(j = 0; j < N; j++) {
      if(Graph[j][i]) {
        Indgree[i]++;
      };
    }
  }
  for(i = 0; i < N; i++) {
    if((Indgree[i] == 0) && (Table[i] > -1)) {
      InsertHeap(H, i);
    }
  }
  while(H->Size != 0) {
    V = DeleteMin(H);
    for(i = 0; i < N; i++) {
      if(Graph[V][i] == 1) {
        Indgree[i] --;
        if(Indgree[i] == 0) {
          InsertHeap(H, i);
        }
      }
    }
    printf("%d", Table[V]);
    if(H->Size != 0) {
      printf(" ");
    }else {
      printf("\n");
    }
  }
}

int main()
{
  int Key, i, j;
  
  scanf("%d", &N);
  for(i = 0; i < N; i++) {
    scanf("%d", &Key);
    Table[i] = Key;
  }
  initGraph(N);
  for(i = 0; i < N; i++) {
    if(Table[i] >= 0) {
      int ii = Hash(Table[i], N);
      while(ii != i) {
        Graph[ii][i] = 1;
        ii = (ii + 1)%N;
      }
    } 
  }
  TopSort();
  return 0;
}

