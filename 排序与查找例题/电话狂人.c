#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define KEYLENGTH 11
#define MAXTABLESIZE 1000000

// 电话类型：11位字符串
typedef char ElemType[KEYLENGTH + 1];

typedef struct LNode *PtrToLNode;
struct LNode {
  ElemType Data;
  int Count;
  PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

struct TblNode {
  int TableSize;
  List Heads;
};
typedef struct TblNode *HashTable;


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
  HashTable H;
  int i;
  H = (HashTable)malloc(sizeof(struct TblNode));
    /* 保证散列表最大长度是素数，具体见代码5.3 */
  H->TableSize = NextPrime(TableSize * 2);
 
    /* 以下分配链表头结点数组 */
    H->Heads = (List)malloc(H->TableSize*sizeof(struct LNode));
    /* 初始化表头结点 */
    for( i=0; i<H->TableSize; i++ ) {
      H->Heads[i].Data[0] = '\0';
      H->Heads[i].Next = NULL;
      H->Heads[i].Count = 0;
  }
 
  return H;
}

int Hash( int Key, int TableSize )
{
  return Key%TableSize;
}

Position Find( HashTable H, ElemType Key )
{
    Position P;
    int Pos;
    Pos = Hash( atoi(Key + KEYLENGTH - 5), H->TableSize ); 
    P = H->Heads[Pos].Next; 
    while( P && strcmp(Key,P->Data) )
      P = P->Next;
 
    return P;
}
 
void Insert( HashTable H, ElemType Key )
{
    Position P, NewCell;
    int Pos;
     
    P = Find( H, Key );
    if ( !P ) { /* 关键词未找到，可以插入 */
      NewCell = (Position)malloc(sizeof(struct LNode));
      strcpy(NewCell->Data, Key);
      NewCell->Count = 1;
      Pos = Hash(atoi(Key + KEYLENGTH - 5), H->TableSize ); /* 初始散列位置 */
      NewCell->Next = H->Heads[Pos].Next;
      H->Heads[Pos].Next = NewCell; 
    }
    else { 
      P->Count++;
    }
}

void ScanandOutput(HashTable H)
{
  int PCount = 0, MaxCount = 0, i;
  ElemType MinPhone;
  List Ptr;
  MinPhone[0] = '\0';
  for(i = 0; i < H->TableSize; i++) {
    Ptr = H->Heads[i].Next;
    while(Ptr) {
      if(Ptr->Count > MaxCount) {
        MaxCount = Ptr->Count;
        PCount = 1;
        strcpy(MinPhone, Ptr->Data);
      }
      else if(Ptr->Count == MaxCount) {
        PCount++;
        if(strcmp(MinPhone, Ptr->Data) > 0)
          strcpy(MinPhone, Ptr->Data);
      }
      Ptr = Ptr->Next;
    }
  }
  if(PCount > 1) {
    printf("%s %d %d\n", MinPhone, MaxCount, PCount);
  }else {
    printf("%s %d\n", MinPhone, MaxCount);
  }
}


int main()
{
  int M, i;
  HashTable H;
  H = CreateTable(M);
  ElemType Key;
  scanf("%d", &M);
  for(i = 0; i < M; i++) {
    scanf(" %s",Key);
    Insert(H, Key);
    scanf(" %s",Key);
    Insert(H, Key);
  }
  ScanandOutput(H);
  return 0;
}


