#include <iostream>
#include<stdlib.h>
#include<stdbool.h>
using namespace std;

typedef int ElemType;
typedef struct SNode {
	ElemType *data;
	int top;
	int capacity;
}Stack;

bool initStack(Stack &st, int length) {
	st.data = (ElemType*)malloc(sizeof(ElemType) * length);
	st.top = -1;
	st.capacity = length;
	return true;
}

bool isEmpty(Stack st) {
	return st.top == -1;
}

bool isFull(Stack st) {
	return st.top == st.capacity - 1;
}

bool push(Stack &st, ElemType x) {
	if(isFull(st)) {
		cout << "当前栈已满!" << endl;
		return false;
	};
	st.data[++st.top] = x;
	return true;
}

bool pop(Stack &st, ElemType &x) {
	if(isEmpty(st)) {
		cout << "当前栈为空!" << endl;
		return false;
	};
	x = st.data[st.top--];
	return false;
}

void loadStack(Stack st) {
	int i = st.top;
	cout << "当前栈：" << endl;
	while(i != -1) {
		cout << "|" << st.data[i--] << "|" << endl;
	}
	cout << endl;
}

int main() {
	int flag;
	ElemType x;
	Stack st;
	initStack(st, 4);
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
			cout << "删除数据" << endl;
			pop(st, x);
			loadStack(st);
		}
		if(flag == 0) {
			break;
		}
	}
	return 0;
}


