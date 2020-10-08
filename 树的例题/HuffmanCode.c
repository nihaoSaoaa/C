#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 0
#define MAXSIZE 64

typedef struct character {
  char Sign;
  int Weight;
}ElemType;
ElemType elem[MAXSIZE];

typedef struct TNode *PtrToTNode;
struct TNode {
  int Weight;
  PtrToTNode Left, Right;
};
typedef PtrToTNode HuffmanTree;

struct HNode {
  PtrToTNode Data[MAXSIZE];
  int Size;
};
typedef struct HNode *MinHeap;

MinHeap CreateHeap()
{
  MinHeap H;
  PtrToTNode T = (PtrToTNode)malloc(sizeof(struct TNode));
  T->Weight = 0;
  T->Left = T->Right = NULL;
  H = (MinHeap)malloc(sizeof(struct HNode));
  H->Size = 0;
  H->Data[0] = T;
  return H;
}

void Insert(MinHeap H, PtrToTNode T)
{
  int i;
  i = ++H->Size;
  while(H->Data[i / 2]->Weight > T->Weight) {
    H->Data[i] = H->Data[i / 2];
    i = i / 2;
  }
  H->Data[i] = T;
}

PtrToTNode DeleteMin(MinHeap H)
{
  PtrToTNode min, temp;
  int i = 1, child;
  temp = H->Data[H->Size--];
  min = H->Data[i];
  while(i * 2 <= H->Size) {
    child = i * 2;
    if(child != H->Size && (H->Data[child + 1]->Weight < H->Data[child]->Weight)) {
      child++;
    }
    if(H->Data[child]->Weight < temp->Weight) {
      H->Data[i] = H->Data[child];
    }else {
      break;
    }
    i = child;
  }
  H->Data[i] = temp;
  return min;
}

HuffmanTree CreateHuffman(MinHeap H)
{
  HuffmanTree T;
  // 错误点：要把 size 保存，应为在删除会把size-1
  int i, N = H->Size;
  for(i = 1; i < N; i++) {
    T = (HuffmanTree)malloc(sizeof(struct TNode));
    T->Left = DeleteMin(H);
    T->Right = DeleteMin(H);
    T->Weight = T->Left->Weight + T->Right->Weight;
    Insert(H, T);
  }
  T = DeleteMin(H);
  return T;
}

int GetWPL(HuffmanTree T, int Depth)
{
  if(!T->Left && !T->Right) {
    return (Depth * T->Weight);
  }else {
    return (GetWPL(T->Left, Depth + 1)) + (GetWPL( T->Right, Depth + 1)) ;
  }
}

int IsPrefixCode(char *str1, char *str2)
{
  int flag = 0;
  if(strspn(str1, str2) - strlen(str2))
    flag = 1;
  return flag;
}

int main()
{
  MinHeap H;
  PtrToTNode PTN;
  HuffmanTree T;
  int N, M, codeLen; //节点数，构建比较的次数 平均路径长度
  int i, j;
  scanf("%d",&N);
  H = CreateHeap();
  for(i = 0; i < N; i++) {
    PTN = (PtrToTNode)malloc(sizeof(struct TNode));
    scanf(" %c %d",&elem[i].Sign, &(elem[i].Weight));
    PTN->Weight = elem[i].Weight;
    PTN->Left = PTN->Right = NULL;
    Insert(H, PTN);
  } 
  T = CreateHuffman(H);
  codeLen = GetWPL(T, 0);
  scanf("%d",&M);
  // 1. 比较WPL 2. 建树判断
  int tempWPL = 0;
  char name;
  char code[N][MAXSIZE];
  while(M--) {
    tempWPL = 0;
    // 输入所有点的编码，计算 WPL
    for(i = 0; i < N; i++) {
      scanf(" %c %s", &name, &code[i]);
      for(j = 0;j < N; j++) {
        if(elem[j].Sign == name) {
          break;
        }
      }
      // 不存在这个节点或编码过长
      if(j == N  || strlen(code[i]) > N - 1) {
        printf("No\n");
        break;
      }
      tempWPL += strlen(code[i]) * elem[j].Weight;
    }
    if(tempWPL != codeLen) {
      printf("%d\n", tempWPL);
      printf("No\n");
      continue;
    }
    // 检验前缀吗
    int flag = 0;
    for(i = 0; i < N; i++) {
      int len = strlen(code[i]);
      for(j = 0;j < N; j++) {
        if(i == j) continue;
        int tempLen = strlen(code[j]);
        if(len < tempLen && !IsPrefixCode(code[j], code[i])){
          flag = 1;
          break;
        }
      }
      if(flag) {
        break;
      }
    }
    if(flag) {
      printf("No\n");
    }else {
      printf("Yes\n");
    }
  }
  return 0;
}


