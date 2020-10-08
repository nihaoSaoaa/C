#include<stdio.h>
#include<stdlib.h>


typedef struct PolyNode{
  int coef;
  int expon;
  struct PolyNode* link;
}PolyNode;
typedef PolyNode* Polynomial;

/*在函数内部修改传入指针的指向需要传入指针的指针*/
void Attach(int c, int e, Polynomial* rear)
{
  Polynomial P = (Polynomial)malloc(sizeof(PolyNode));
  P->coef = c;
  P->expon = e;
  P->link = NULL;
  (*rear)->link = P;
  *rear = P;
}

Polynomial ReadPoly()
{
  int c, e, N;
  Polynomial P, t, Rear;
  scanf("%d", &N);
  P = (Polynomial)malloc(sizeof(PolyNode));
  P->link = NULL;
  Rear = P;
  while(N--) {
    scanf("%d %d", &c, &e);
    if(abs(c) <= 1000 && abs(e) <= 1000)
      Attach(c, e, &Rear);
  }
  t = P;
  P = P->link;
  free(t);
  return P;
}

Polynomial PolyMult(Polynomial P1, Polynomial P2)
{
  Polynomial P,Rear,t1,t2,t;
  int c,e;
  if(!P1 || !P2) return NULL;
  // 1. 动态指针指向完成，P 初始化
  t1 = P1;t2 = P2;  
  P = (Polynomial)malloc(sizeof(PolyNode));
  Rear = P;
  // 2. 改变 t2，先创建一部分多项式
  while(t2) {
    Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
    t2 = t2->link;
  }
  // 3. 改变t1，t2指针，不断的插入多项式结点
  t1 = t1->link;
  while(t1) {
    // 回归指针
    t2 = P2;Rear = P;
    while(t2) {
      c = t1->coef*t2->coef;
      e = t1->expon+t2->expon;
      // 通过比较指数的大小确定如何操作
      while(Rear->link && Rear->link->expon > e) {
        Rear = Rear->link;
      }
      // 如果指数相等：系数=0删除结点，否则系数相加
      if(Rear->link && Rear->link->expon == e) {
        if (Rear->link->coef + c) {
          Rear->link->coef +=c;
        }else {
          t = Rear->link;
          Rear->link = t->link;
          free(t);
        }
      }else {
        t = (Polynomial)malloc(sizeof(PolyNode));
        t->coef = c;
        t->expon = e;
        t->link = Rear->link;
        Rear->link = t;
        Rear = Rear->link;
      }
      t2 = t2->link;
    }
    t1 = t1->link;
  }
  t = P;P = P->link;free(t);
  return P;
}

Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
  Polynomial P,Rear,t;
  int sum;
  P = (Polynomial)malloc(sizeof(PolyNode));
  P->link = NULL;
  Rear = P;
  while(P1 && P2) {
    if(P1->expon > P2->expon) {
      Attach(P1->coef, P1->expon, &Rear);
      P1 = P1->link;
    }
    else if(P1->expon < P2->expon) {
      Attach(P2->coef, P2->expon, &Rear);
      P2 = P2->link;
    }
    else {
      sum = P1->coef+P2->coef;
      if(sum) Attach(sum, P1->expon, &Rear);
      P1 = P1->link;
      P2 = P2->link;
    }
  }
  while(P1) {
    Attach(P1->coef, P1->expon, &Rear);
    P1 = P1->link;
  }
  while(P2) {
    Attach(P2->coef, P2->expon, &Rear);
    P2 = P2->link;
  }
  Rear->link = NULL;
  t = P;
  P = P->link;
  free(t);
  return P;
}

void PrintPoly(Polynomial P)
{
  int flag = 0;
  if (P == NULL) {
    printf("0 0\n");
    return;
  }
  while(P) {
    if(!flag)
      flag = 1;
    else
      printf(" ");
    printf("%d %d", P->coef, P->expon);
    P = P->link;
  }
  printf("\n");
}

int main()
{
  Polynomial P1, P2, PP, PS;
  P1 = ReadPoly();
  P2 = ReadPoly();
  PP = PolyMult(P1, P2);
  PrintPoly(PP);
  PS = PolyAdd(P1, P2);
  PrintPoly(PS);
  return 0;
}
