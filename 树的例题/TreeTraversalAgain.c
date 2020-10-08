#include <stdio.h>
#include<string.h>

#define MAXSIZE 30

int Stack[MAXSIZE],pre[MAXSIZE], in[MAXSIZE], post[MAXSIZE];

void Push(int S[], int* p, int X)
{
  
  S[++(*p)] = X;
}

int Pop(int S[], int* p)
{
  return S[(*p)--];
}

void solve(int preL, int inL, int postL, int n)
{
  int i,L,R;
  int root = pre[preL];
  if(n == 0) return;
  if(n == 1) {
    post[postL] = pre[preL];
    return;
  };
  post[postL + n - 1] = root;
  for(i = 0; i < n; i++) {
    if(in[inL + i] == root) break;
  }
  L = i;R = n - L -1;
  solve(preL + 1, inL, postL, L);
  solve(preL + L + 1, inL + L + 1, postL + L, R);
}

int main()
{
  int p = -1, i = -1, j = -1;
  /* 字符串用数组的方式声明,可以进行修改
  / 字符指针指向字符串常量时，指向可以修改（可以 ++），但是指向的字符串是常量（不可变）；
  / 字符数组名是变量，不能修改指向（不可++），但是数组元素是变量（可以修改）
  */
  char str[5];
  int N, X;
  int preL = 0, inL = 0, postL = 0;
  scanf("%d", &N);
  while(N > j + 1) {
    scanf("%s", str);
    if(strcmp(str, "Push") == 0) {
      scanf("%d", &X);
      Push(Stack, &p, X);
      Push(pre, &i, X);
    }else if(strcmp(str, "Pop") == 0) {
      Push(in, &j, Pop(Stack, &p));
    }
  }
  solve(preL, inL, postL, N);
  for(i = 0; i < N; i++) {
    if(i == 0)
      printf("%d",post[i]);
    else
      printf(" %d",post[i]);
  }
  return 0;
}
