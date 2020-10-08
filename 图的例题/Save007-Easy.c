#include <stdio.h>
#include <math.h>

#define MAXSIZE 100

typedef struct PNode {
  double x, y;
} PNode;
PNode PList[MAXSIZE];
int Visited[MAXSIZE];
int N;
double D;

double Dis(int a, int b)
{
  return sqrt(pow(PList[a].x - PList[b].x, 2) + pow(PList[a].y - PList[b].y, 2));
}

int FirstJump(int a)
{
  double dis = sqrt(pow(PList[a].x, 2) + pow(PList[a].y, 2));
  if( dis <= D + 7.5 )
    return 1;
  else
    return 0;
}

int Jump(int a, int b)
{
  if( Dis(a, b) < D )
    return 1;
  else
    return 0;
}

int Success(int a)
{
  if(fabs(PList[a].x) + D >= 50.0 || fabs(PList[a].y) + D >= 50.0)
    return 1;
  else 
    return 0;
}

int DFS(int a)
{
  int answer = 0, i;
  Visited[a] = 1;
  if(Success(a)) return 1;
  for(i = 0; i < N; i++) {
    if(!Visited[i] && Jump(a, i)) {
      answer = DFS(i);
      if(answer) break;
    }
  }
  return answer;
}

void save007()
{
  int i, answer = 0;
  for(i = 0; i < N; i++) {
    if(!Visited[i] && FirstJump(i)) {
      answer = DFS(i);
      if(answer) break;
    }
  }
  if(answer)
    printf("Yes\n");
  else
    printf("No\n");
}

int main()
{
  int i;
  scanf("%d %lf", &N, &D);
  for(i = 0; i < N; i++) {
    scanf("%lf %lf", &PList[i].x, &PList[i].y);
    Visited[i] = 0;
  }
  // 直接可以跳到对岸
  if(D >= 42.5) 
    printf("Yes\n");
  else
    save007();
  return 0;
}
