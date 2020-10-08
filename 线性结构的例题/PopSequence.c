#include <stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000

typedef struct SNode *Stack;
struct SNode {
  int Data[MAXSIZE];
  int Max, Now;
};

Stack CreateStack(Max) 
{
  Stack S;
  S = (Stack)malloc(sizeof(struct SNode));
  S->Max = Max;
  S->Now = -1;
  return S;
}

int isFull(Stack S) 
{
  if(S->Now == S->Max - 1) return 1;
  else return 0;
}

void push(Stack S, int X)
{
  S->Data[++S->Now] = X;
}

void pop(Stack S)
{
  S->Now--;
}

int GetTop(Stack S) 
{
  return S->Data[S->Now];
}

void Clear(Stack S)
{
  S->Now = -1;
}

int main()
{
  int M,N,K;
  int i,v,counter;
  int a;
  scanf("%d %d %d", &M, &N, &K);
  Stack S = CreateStack(M);
  for(i = 0; i < K; i++) {
    Clear(S);
    v = 1;counter = 0;
    push(S, v);
    scanf("%d", &a);
    while(counter < N) {
      if(GetTop(S) == a){
        pop(S);counter++;
        if(counter == N){
          break;
        } else {
          scanf("%d", &a);
        }
      }else {        
        if(isFull(S)) break;
        else {
          v++;
          push(S, v);
        }
      }
    }

    if(counter == N) {
      printf("YES\n");
    } else {
      while(N - counter > 1) {
        scanf("%d", &a);
        counter ++;
      }
      printf("NO\n"); 
    }
    
  }
  return 0;
}