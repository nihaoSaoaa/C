#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int ElemType;   // 链表结点数据类型
typedef struct LNode* PtrToLNode; 
typedef struct LNode {  // 链表结点结构
    ElemType data;
    PtrToLNode next;
} LNode;
typedef PtrToLNode List;

// 初始化一个空的链表
void InitList(List &L) {
    L = (List)malloc(sizeof(LNode));
    L->data = -1;
    L->next = NULL;
}

// 初始化有N个结点的链表
void InitList(List &L, int N) {
    PtrToLNode rear, tmp;
    ElemType x;
    InitList(L);
    rear = L;
    for (int i = 0; i < N; i++) {
        cin >> x;
        tmp = (List)malloc(sizeof(LNode));
        tmp->data = x;
        rear->next = tmp;
        rear = rear->next; 
    }
    rear->next = NULL;
}

// 插入结点
int Insert(List L, int p, ElemType x) {
    PtrToLNode pre = L, tmp;    // pre指向插入位置的前一个结点，tmp指向要创建的结点
    while(pre && --p) {
        pre = pre->next;
    }   
    // 前一个结点不存在
    if(!pre) {
        cout << "插入的位置不正确！" << endl;
        return 0;
    }
    // 创建结点
    tmp = (List)malloc(sizeof(struct LNode));
    tmp->data = x;
    tmp->next = pre->next;
    pre->next = tmp;
    return 1;
}

// 删除结点
int Delete(List L, int p) {
    PtrToLNode pre = L, tmp;    // pre指向插入删除的前一个结点，tmp指向要删除的结点
    while(pre && pre->next && --p) {
        pre = pre->next;
    }  
    tmp = pre->next;    
    if(!tmp) {  // 结点不存在
        cout << "删除的位置不正确" << endl;
        return 0;
    } 
    pre->next = tmp->next;  // 指向删除结点的下一个结点
    free(tmp);  // 释放内存
    return 1;
}

void LoadList(List L) {
    PtrToLNode p = L->next;
    cout << "当前链表：";
    while(p) {
        cout << " -> " << p->data;
        p = p->next;
    }
    cout << endl;
}

void MergeList(List L1, List L2, List &L) {
    PtrToLNode p1 = L1->next, p2 = L2->next, rear;
    L = rear = L1;
    while(p1 && p2) {
        if(p1->data <= p2->data) {
            rear->next = p1;
            rear = rear->next;
            p1 = p1->next;
        }else {
            rear->next = p2;
            rear = rear->next;
            p2 = p2->next;
        }
    }
    if(p1) rear->next = p1;
    if(p2) rear->next = p2;
}

int test() {
    List L;
    int n, p;
    ElemType x;
    cout << "输入数字以初始化链表" << endl;
    cout << "初始化链表大小：";
    cin >> n;
    cout << "输入" << n << "个数字: ";
    InitList(L, n);
    LoadList(L);
    cout << "输入一个新元素和插入位置，插入链表: ";
    cin >> x >> p;
    Insert(L, p, x);
    LoadList(L);
    cout << "输入一个删除位置，从链表中删除这个位置上的元素: ";
    cin >> p;
    Delete(L, p);
    LoadList(L);
    return 0;
}

int merge() {
    List L1, L2, L;
    int n;
    cout  << "初始化第一个链表" << endl;
    cout << "请输入链表的结点数：";
    cin >> n;
    cout << "请输入" << n << "个数：";
    InitList(L1, n);
    cout  << "初始化第二个链表" << endl;
    cout << "请输入链表的结点数：";
    cin >> n;
    cout << "请输入" << n << "个数：";
    InitList(L2, n);
    MergeList(L1, L2, L);
    LoadList(L);
    return 0;
}

int main() {
    merge();
    return 0;
}
