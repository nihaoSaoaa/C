#include<stdio.h>
#include<stdlib.h>


typedef struct PolyNode{
  int coef; // 系数
  int expon;  // 指数
  struct PolyNode* link;  // 下一个多项式结点
}PolyNode;
typedef PolyNode* Polynomial;

void AddUI();
void MultUI();
void Welcome();

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

// 打印多项式 
void PrintPoly(Polynomial P,const char* name)
{
  printf("%s(x) = ", name);
  if (P == NULL) {
    printf("0\n");
    return;
  }
  int flag = 0;
  while(P) {
    if(flag) printf(" + ");
    if(P->coef > 0) {
      if(P->coef != 1 || (P->coef == 1 && P->expon == 0)) {
        printf("%d", P->coef);
      }
    }else {
      printf("(%d)", P->coef);
    }
    if(P->expon > 1) {
      printf("x^%d", P->expon);
    }
    if(P->expon == 1) {
      printf("x");
    }
    if(P->expon < 0) {
      printf("x^(%d)", P->expon);
    }
    if(!flag) {
      flag = 1;
    }
    P = P->link;
  }
  printf("\n");
}

// 创建链表
Polynomial ReadPoly(const char* name)
{
  printf("请输入多项式%s: (格式：系数 指数；以 0 0 结束！；按照降幂输入！)\n", name);
  printf("-----------------------------------------------------------\n");
  int c, e;
  Polynomial P, t, Rear;
  P = (Polynomial)malloc(sizeof(PolyNode));
  P->link = NULL;
  Rear = P;
  int flag = 0;
  while(1) {
    if(flag == 0) 
      printf("请输入多项式%s的第一项: ", name);
    else {
      printf("请输入多项式%s的下一项: ", name);
    }
    scanf("%d %d", &c, &e);
    if(c == 0 && e == 0) break;
    if(abs(c) <= 1000 && abs(e) <= 1000)
      Attach(c, e, &Rear);
    if(!flag) flag = 1;
  };
  t = P;
  P = P->link;
  free(t);
  return P;
}

// 多项式相乘
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
        // 插入结点
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

// 多项式相加
Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
  Polynomial P,Rear,t;
  int sum;
  P = (Polynomial)malloc(sizeof(PolyNode)); // 带头结点的新链表
  P->link = NULL;
  Rear = P;
  while(P1 && P2) {
    // 复制指数较大的结点链接到新链表表尾
    if(P1->expon > P2->expon) { 
      Attach(P1->coef, P1->expon, &Rear);
      P1 = P1->link;
    }
    else if(P1->expon < P2->expon) {
      Attach(P2->coef, P2->expon, &Rear);
      P2 = P2->link;
    }
    // 若指数相同
    else {
      sum = P1->coef+P2->coef;
      // 系数相加不为 0 
      if(sum) Attach(sum, P1->expon, &Rear);
      P1 = P1->link;
      P2 = P2->link;
    }
  }
  // 剩余长度的结点
  while(P1) {
    Attach(P1->coef, P1->expon, &Rear);
    P1 = P1->link;
  }
  while(P2) {
    Attach(P2->coef, P2->expon, &Rear);
    P2 = P2->link;
  }
  // 删除头结点
  Rear->link = NULL;
  t = P;
  P = P->link;
  free(t);
  return P;
}

// 相加界面
void AddUI() {
  int x;
  Polynomial P1, P2, PA;
  const char *f = "f", *g = "g", *F = "F";
  printf("你选择的操作是多项式相加：\n");
  P1 = ReadPoly(f);
  printf("\n");
  PrintPoly(P1, f);
  printf("\n");
  P2 = ReadPoly(g);
  printf("\n");
  PrintPoly(P2, g);
  printf("\n");
  PA = PolyAdd(P1, P2);
  printf("\n多项式相加的结果为：\n");
  printf("*****************************\n");
  PrintPoly(PA, F);
  printf("*****************************\n");
  printf("是否继续操作？ 1. 继续；0. 返回   ");
  scanf("%d", &x);
  if(x == 1) {
    AddUI();
  }else {
    Welcome();
  }
}
// 相乘界面
void MultUI() {
  int x;
  Polynomial P1, P2, PM;
  const char *f = "f", *g = "g", *F = "F";
  printf("你选择的操作是多项式相乘：\n");
  P1 = ReadPoly(f);
  printf("\n");
  PrintPoly(P1, f);
  printf("\n");
  P2 = ReadPoly(g);
  printf("\n");
  PrintPoly(P2, g);
  printf("\n");
  PM = PolyMult(P1, P2);
  printf("\n多项式相乘的结果为：\n");
  printf("*****************************\n");
  PrintPoly(PM, F);
  printf("*****************************\n");
  printf("是否继续操作？ 1. 继续；0. 返回   ");
  scanf("%d", &x);
  if(x == 1) {
    MultUI();
  }else {
    Welcome();
  }
}
// 开始界面
void Welcome() {
  int x;
  printf("");
  printf("          任意两个多项式的相加/相乘  \n");
  printf("        ▇▇▇▇▇▇▇▇▇▇▇▇▇\n");
  printf("        ★                      ★\n");
  printf("        ★ 1. 两个多项式相加    ★\n");
  printf("        ★ 2. 两个多项式相乘    ★ \n");
  printf("        ★ 0. 退出              ★\n");
  printf("        ★                      ★ \n");
  printf("        ▇▇▇▇▇▇▇▇▇▇▇▇▇\n");
  printf("            你选择的操作是：");
  scanf("%d", &x);
  printf("\n\n");
  if(x == 0) {
    exit(0);
  }
  else if(x == 1) {
    AddUI();
  }
  else if(x == 2) {
    MultUI();
  }
  else {
    exit(0);
  }
}

int main()
{
  Welcome();
  return 0;
}
