#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXTABLESIZE 100000 /* 允许开辟的最大散列表长度 */
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
{ /* 返回大于N且不超过MAXTABLESIZE的最小素数 */
  int i, p = (N%2)? N+2 : N+1; /*从大于N的下一个奇数开始 */

  while( p <= MAXTABLESIZE ) {
    for( i=(int)sqrt(p); i>2; i-- )
      if ( !(p%i) ) break; /* p不是素数 */
    if ( i==2 ) break; /* for正常结束，说明p是素数 */
    else  p += 2; /* 否则试探下一个奇数 */
  }
  return p;
}

HashTable CreateTable( int TableSize )
{
  int i;
  HashTable Tbl;
  Tbl = (HashTable)malloc(sizeof(struct TblNode));
  Tbl->TableSize = NextPrime(TableSize);
  Tbl->Cells = (Cell*)malloc(sizeof(Cell) * Tbl->TableSize);
  for(i = 0; i < Tbl->TableSize; i++) {
    Tbl->Cells[i].Info = Empty;
  }
  return Tbl;
}

Position Hash(ElementType Key, int TableSize)
{
  return Key % TableSize;
}

void Display(HashTable H) {
  printf("哈希表：");
  for (int i = 0; i < H->TableSize; i++)
  {
    if(H->Cells[i].Info == Legitimate) {
      printf("%d ", H->Cells[i].Data);
    }else
    {
      printf("X ");
    }
  }
  printf("\n");
}

// 平方探测法查找
Position Find(HashTable H, ElementType Key)
{
  Position CurrentPos, NewPos;
  int CNum = 0; // 冲突次数
  CurrentPos = NewPos = Hash(Key, H->TableSize);
  while(H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key) {
    // 奇数次冲突向右探查
    if(++CNum %2) {
      NewPos = CurrentPos + (CNum + 1)*(CNum + 1) / 4;
      if(NewPos > H->TableSize)
        NewPos %= H->TableSize;
    }else {
      NewPos = CurrentPos - CNum*CNum / 4;
      while(NewPos < 0) {
        NewPos += H->TableSize;
      } 
    }
  }
  return NewPos;
}

// 插入
bool Insert(HashTable H, ElementType key)
{
  Position P = Find(H, key);
  if(H->Cells[P].Info != Legitimate) {
    H->Cells[P].Data = key;
    H->Cells[P].Info = Legitimate;
    return true;
  }
  else {return false;}
}

// 删除
bool Delete(HashTable H, ElementType key)
{
  Position P = Find(H, key);
  if(H->Cells[P].Info == Legitimate) {
    H->Cells[P].Info = Deleted;
    return true;
  }
  else {return false;}
}

int main() {
  printf("创建一个长度为13的哈希表\n");
  HashTable H = CreateTable(11);
  printf("插入数据：13,28,6,26,39,17,29,39,32\n");
  Insert(H, 13);
  Insert(H, 28);
  Insert(H, 6);
  Insert(H, 26);
  Insert(H, 39);
  Insert(H, 17);
  Insert(H, 29);
  Insert(H, 39);
  Insert(H, 32);
  Display(H);
  printf("删除数据：6,26,39\n");
  Delete(H, 6);
  Delete(H, 26);
  Delete(H, 39);
  Display(H);
}