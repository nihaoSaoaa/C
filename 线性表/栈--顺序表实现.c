#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define ERROR -1 

typedef int Position;
typedef int ElementType; 
typedef struct SNode {
  ElementType *Data;
  Position Top;
  int MaxSize;
}SNode;
typedef SNode *Stack;

// 创建一个空栈
Stack CreateStack(int MaxSize)
{
  Stack S = (Stack)malloc(sizeof(SNode));
  S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
  S->Top = -1;
  S->MaxSize = MaxSize;
  return S;
}

// 判断空栈
bool IsEmpty(Stack S)
{
  return (S->Top == -1); 
}

// 判断栈满
bool IsFull(Stack S)
{
  return (S->Top == S->MaxSize - 1); 
}

// 添加操作
bool Push(Stack S, ElementType x)
{
  if (IsFull(S)) {
    printf("stack is full!");
    return false;
  }else {
    S->Data[++(S->Top)] = x;
    return true;
  }
}

// 删除操作
bool Pop(Stack S)
{
  if (IsEmpty(S)) {
    printf("stack is empty!");
    return ERROR;
  }else {
    return (S->Data[(S->Top)--]);
  }
}

void output(Stack S)
{
  int i = 0;
  while(i <= (S->Top)) {
    printf("%d ",S->Data[i]);
    i++;
  }
  printf("\n");
}

int main()
{
  /*test code*/
  int max = 5, flag = 0, x;
  Stack s = CreateStack(max);
  while(flag != -1) {
    scanf("%d %d", &flag, &x);
    if (flag == 1) {
      Push(s, x);
    }else if (flag == 2) {
      Pop(s);
    }
    output(s);
  }
  return 0;
}