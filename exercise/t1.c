#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXTABLESIZE 20000 /* 允许开辟的最大散列表长度 */
typedef int ElementType;    /* 关键词类型用整型 */
typedef int Index;          /* 散列地址类型 */
typedef Index Position;     /* 数据所在位置与散列地址是同一类型 */
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum { Legitimate, Empty, Deleted } EntryType;

// 散列表单元类型: 存放元素和数据状态
typedef struct HashEntry {
  ElementType Data;
  EntryType Info;
}Cell;

// 散列表：表的最大长度和表单元数组
typedef struct TblNode *HashTable; 
struct TblNode{
  int TableSize;
  Cell *Cells;
};

int NextPrime( int N )
{ 
  int i, p = (N%2)? N+2 : N+1; 

  while( p <= MAXTABLESIZE ) {
    for( i=(int)sqrt(p); i>2; i-- )
      if ( !(p%i) ) break;
    if ( i==2 ) break; 
    else  p += 2;
  }
  return p;
}

HashTable CreateTable( int TableSize )
{
  int i;
  HashTable H;
  H = (HashTable)malloc(sizeof(struct TblNode));
  H->TableSize = NextPrime(TableSize);
  H->Cells = (Cell *)malloc(sizeof(Cell) * H->TableSize);
  for(i = 0; i < H->TableSize; i++) {
    H->Cells[i].Info = Empty;
  }
  return H;
}

Position Hash(ElementType Key, int TableSize)
{
  return Key % TableSize;
}

Position Find(HashTable H, ElementType Key)
{
  Position CurrentPos, NewPos;
  int CNum = 0; // 冲突次数
  CurrentPos = NewPos = Hash(Key, H->TableSize);
  while(H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key) {
    CNum++;
    NewPos = (CurrentPos + CNum * CNum) % H->TableSize;
    if(CNum >= H->TableSize) {
      NewPos = -1;
      break;
    }
  }
  return NewPos;
}

// 插入
Position Insert(HashTable H, ElementType key)
{
  Position P = Find(H, key);
  if(P == -1) return P;
  if(H->Cells[P].Info != Legitimate) {
    H->Cells[P].Data = key;
    H->Cells[P].Info = Legitimate;
    return P;
  }
}

int main()
{
  int M, N;
  Position P, i;
  ElementType Key;
  HashTable H;
  scanf("%d %d", &M, &N);
  H = CreateTable(M);
  for(i = 0; i < N; i++) {
    scanf("%d", &Key);
    P = Insert(H, Key);
    if(P == -1) {
      printf("-");
    }else {
      printf("%d", P);
    }
    if(i == N - 1) {
      printf("\n");
    }else {
      printf(" ");
    }
  }
  return 0;
}


