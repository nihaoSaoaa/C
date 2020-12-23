#include <iostream>
#include<stdlib.h>
#include<stdbool.h>
using namespace std;

typedef int ElemType;
typedef struct SNode *PtrToSNode;
typedef struct SNode {
	ElemType data;
	PtrToSNode next;
}SNode;
typedef PtrToSNode Stack;

bool initStack(Stack &st) {
	st = (Stack)malloc(sizeof(SNode));
	st->next = NULL;
	return true;
}

bool isEmpty(Stack st) {
	return st->next == NULL;
}

bool push(Stack st, ElemType x) {
	PtrToSNode p;
	p = (Stack)malloc(sizeof(SNode));
	p->data = x;
	p->next = st->next;
	st->next = p;
	return true;
}

bool pop(Stack st, ElemType &x) {
	if(isEmpty(st)) return false;
	PtrToSNode p;
	p = st->next;
	st->next = p->next;
	x = p->data;
	free(p);
	return true;
}

void loadStack(Stack st) {
	PtrToSNode p;
	p = st->next;
	cout << "当前栈：" << endl;
	while(p) {
		cout << "|" << p->data << "|" << endl;
		p = p->next;
	}
	cout << endl;
}

int main() {
	int flag;
	ElemType x;
	Stack st;
	initStack(st);
	cout << "------\n栈操作：\n插入1\n删除2\n推出0\n------\n";
	while(1) {
		cout << "输入操作：";
		cin >> flag;
		if(flag == 1) {
			cout << "插入数据：";
			cin >> x;
			push(st, x);
			loadStack(st);
		}
		if(flag == 2) {
			cout << "删除数据：";
			pop(st, x);
			cout << x << endl;
			loadStack(st);
		}
		if(flag == 0) {
			break;
		}
	}
	return 0;
}